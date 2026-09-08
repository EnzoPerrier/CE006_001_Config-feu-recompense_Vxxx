/**
  ******************************************************************************
  * @autohr Enzo Perrier
  * @file    usb_cdc_driver.c
  * @brief   Driver applicatif au-dessus de la classe USBX CDC-ACM.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "drivers/usb_cdc_driver.h"
#include "ux_device_class_cdc_acm.h"

/* Private define ----------------------------------------------------------*/

/** @brief Nom du mutex, utile en debug (visible via un debogueur ThreadX-aware). */
#define USB_CDC_MUTEX_NAME    "usb_cdc_write_mutex"

/* Private variables ----------------------------------------------------------*/

/**
 * @brief Pointeur vers l'instance CDC-ACM fournie par USBX a l'activation.
 * @note  UX_NULL tant que usb_cdc_driver_on_activate() n'a pas ete appelee,
 *        ou apres une deconnexion (cf usb_cdc_driver_on_deactivate()).
 *        Type conforme au prototype de ux_device_class_cdc_acm_read()/_write()
 *        (cf ux_device_class_cdc_acm.h : UX_SLAVE_CLASS_CDC_ACM*).
 */
static UX_SLAVE_CLASS_CDC_ACM *usb_cdc_instance = UX_NULL;

/** @brief Mutex protegeant les ecritures concurrentes (plusieurs threads emetteurs). */
static TX_MUTEX usb_cdc_write_mutex;

/** @brief UX_TRUE si un hote a ouvert le port COM virtuel, UX_FALSE sinon. */
static volatile UINT usb_cdc_connected = UX_FALSE;

/** @brief UX_TRUE une fois usb_cdc_driver_init() executee avec succes. */
static volatile UINT usb_cdc_initialized = UX_FALSE;

/* Exported functions ----------------------------------------------------------*/

usb_cdc_status_t usb_cdc_driver_init(VOID)
{
    UINT tx_status;

    /* Le mutex protege usb_cdc_driver_write() contre les acces concurrents
     * de plusieurs threads. TX_NO_INHERIT est retenu ici car aucun
     * scenario d'inversion de priorite n'a ete identifie sur cette
     * ressource a ce stade (les threads emetteurs potentiels sont a des
     * priorites proches). A reevaluer vers TX_INHERIT si un thread
     * haute priorite venait a etre bloque par un thread basse priorite
     * detenant ce mutex. */
    tx_status = tx_mutex_create(&usb_cdc_write_mutex, USB_CDC_MUTEX_NAME, TX_NO_INHERIT);

    if (tx_status != TX_SUCCESS)
    {
        /* usb_cdc_initialized reste a UX_FALSE : toute tentative d'usage
         * ulterieure de write()/read() est bloquee par le garde-fou
         * USB_CDC_ERROR_NOT_INITIALIZED, plutot que d'utiliser un mutex
         * qui n'existe pas (comportement indefini sinon). */
        return USB_CDC_ERROR_INTERNAL;
    }

    usb_cdc_instance     = UX_NULL;
    usb_cdc_connected    = UX_FALSE;
    usb_cdc_initialized  = UX_TRUE;

    return USB_CDC_OK;
}

VOID usb_cdc_driver_on_activate(VOID *cdc_instance)
{
    /* Defense en profondeur : meme si USBX est cense toujours fournir
     * une instance valide a l'activation, on ne fait pas confiance
     * implicitement a un pointeur externe. Si NULL, on abandonne sans
     * modifier l'etat courant : le driver reste "non connecte" plutot
     * que de risquer un usage ulterieur d'un pointeur invalide. */
    if (cdc_instance == UX_NULL)
    {
        return;
    }

    usb_cdc_instance  = (UX_SLAVE_CLASS_CDC_ACM *)cdc_instance;
    usb_cdc_connected = UX_TRUE;
}

VOID usb_cdc_driver_on_deactivate(VOID *cdc_instance)
{
    UX_PARAMETER_NOT_USED(cdc_instance);

    /* Ordre important : usb_cdc_driver_write()/read() verifient
     * usb_cdc_connected AVANT de dereferencer usb_cdc_instance. En
     * invalidant la connexion avant le pointeur, on garantit qu'aucun
     * appel concurrent ne peut lire usb_cdc_instance apres qu'il ait
     * ete efface mais avant que usb_cdc_connected ne reflete l'etat
     * reel de deconnexion. */
    usb_cdc_connected = UX_FALSE;
    usb_cdc_instance  = UX_NULL;

    /* @note Choix assume : un thread actuellement bloque dans un appel
     * read()/write() au moment de cette deconnexion n'est pas reveille
     * explicitement ici. USBX reinitialise le endpoint lors de la
     * deconnexion, ce qui fait normalement ressortir l'appel bloquant
     * en erreur. Comportement documente mais NON VERIFIE
     * experimentalement a ce stade.
     * TODO validation banc de test : debrancher le cable USB pendant
     * un read() bloquant et confirmer que le thread se debloque bien. */
}

VOID usb_cdc_driver_on_parameter_change(VOID *cdc_instance)
{
    /* Choix assume : aucune action. Ce CDC virtuel n'a pas d'USART
     * physique en face dont les parametres devraient etre repercutes.
     * Si ce driver doit un jour piloter un pont USB <-> USART physique,
     * lire ici UX_SLAVE_CLASS_CDC_ACM_LINE_CODING_PARAMETER via
     * ux_device_class_cdc_acm_ioctl() et repercuter sur l'USART visee. */
    UX_PARAMETER_NOT_USED(cdc_instance);
}

usb_cdc_status_t usb_cdc_driver_write(const UCHAR *data, ULONG length,
                                       ULONG timeout_ticks, ULONG *actual_length)
{
    UINT tx_status;
    UINT ux_status;
    UINT mutex_taken = UX_FALSE;
    ULONG bytes_written_this_call = 0;
    usb_cdc_status_t ret = USB_CDC_OK;

    /* --- Validation des parametres --- */
    if (actual_length != UX_NULL)
    {
        *actual_length = 0;
    }

    if ((data == UX_NULL) || (length == 0) || (actual_length == UX_NULL))
    {
        return USB_CDC_ERROR_INVALID_PARAM;
    }

    if (usb_cdc_initialized == UX_FALSE)
    {
        return USB_CDC_ERROR_NOT_INITIALIZED;
    }

    if (usb_cdc_connected == UX_FALSE)
    {
        return USB_CDC_ERROR_NOT_CONNECTED;
    }

    /* --- Acquisition du mutex --- */
    tx_status = tx_mutex_get(&usb_cdc_write_mutex, timeout_ticks);

    if (tx_status == TX_SUCCESS)
    {
        mutex_taken = UX_TRUE;
    }
    else if (tx_status == TX_NOT_AVAILABLE)
    {
        /* TX_NOT_AVAILABLE : le delai (y compris TX_NO_WAIT) a expire
         * sans obtenir le mutex. */
        return USB_CDC_ERROR_TIMEOUT;
    }
    else
    {
        return USB_CDC_ERROR_INTERNAL;
    }

    /* --- Re-verification post-acquisition ---
     * Le mutex a pu etre attendu longtemps (timeout_ticks eleve) :
     * l'hote a pu se deconnecter entre-temps. On revalide l'etat pour
     * eviter un appel USBX sur une instance devenue invalide. */
    if (usb_cdc_connected == UX_FALSE)
    {
        ret = USB_CDC_ERROR_NOT_CONNECTED;
    }
    else
    {
        /* --- Transfert USB ---
         * @note ux_device_class_cdc_acm_write() est bloquant cote USBX :
         * son delai interne d'attente de disponibilite de l'endpoint IN
         * n'est PAS pilote par notre parametre timeout_ticks, qui ne
         * s'applique qu'a l'acquisition du mutex ci-dessus. Limitation
         * connue et assumee, documentee pour l'audit : le nom du
         * parametre pourrait laisser croire a un timeout de bout en
         * bout, ce qui n'est pas le cas en l'etat. */
        ux_status = ux_device_class_cdc_acm_write(usb_cdc_instance,
                                                    (UCHAR *)data,
                                                    length,
                                                    &bytes_written_this_call);

        *actual_length = bytes_written_this_call;

        if (ux_status != UX_SUCCESS)
        {
            ret = USB_CDC_ERROR_INTERNAL;
        }
        else if (bytes_written_this_call != length)
        {
            /* Ecriture partielle observee. Remontee comme erreur plutot
             * que masquee par une boucle silencieuse : a ce stade, ce
             * comportement n'a pas ete caracterise experimentalement.
             * Si l'ecriture partielle s'avere normale (paquets > MPS),
             * remplacer ce bloc par une boucle qui renvoie le reste. */
            ret = USB_CDC_ERROR_INTERNAL;
        }
    }

    /* --- Liberation du mutex ---
     * Executee dans tous les cas ou il a ete pris, quel que soit le
     * resultat du transfert ci-dessus. */
    if (mutex_taken == UX_TRUE)
    {
        (VOID)tx_mutex_put(&usb_cdc_write_mutex);
    }

    return ret;
}

usb_cdc_status_t usb_cdc_driver_read(UCHAR *buffer, ULONG buffer_size,
                                      ULONG *actual_length, ULONG timeout_ticks)
{
    UINT ux_status;
    ULONG bytes_read = 0;

    UX_PARAMETER_NOT_USED(timeout_ticks);

    /* --- Validation des parametres --- */
    if (actual_length != UX_NULL)
    {
        *actual_length = 0;
    }

    if ((buffer == UX_NULL) || (buffer_size == 0) || (actual_length == UX_NULL))
    {
        return USB_CDC_ERROR_INVALID_PARAM;
    }

    if (usb_cdc_initialized == UX_FALSE)
    {
        return USB_CDC_ERROR_NOT_INITIALIZED;
    }

    if (usb_cdc_connected == UX_FALSE)
    {
        return USB_CDC_ERROR_NOT_CONNECTED;
    }

    /* @warning Cette fonction ne doit etre appelee que par UN SEUL
     * thread "consommateur" du firmware. ux_device_class_cdc_acm_read()
     * bloque le thread appelant jusqu'a reception de donnees ou erreur
     * de transfert ; il n'existe pas de mecanisme de distribution vers
     * plusieurs lecteurs simultanes dans cette implementation.
     *
     * @note Comme pour usb_cdc_driver_write(), timeout_ticks n'est PAS
     * honore ici : USBX ne fournit pas de parametre de timeout a
     * ux_device_class_cdc_acm_read(). Le parametre est conserve dans
     * le prototype pour ne pas casser le contrat d'interface si une
     * solution de timeout (thread de supervision + abort de transfert)
     * est implementee plus tard.
     * TODO : lever cette limitation si un besoin de timeout reel sur
     * la reception est confirme. */
    ux_status = ux_device_class_cdc_acm_read(usb_cdc_instance,
                                               buffer,
                                               buffer_size,
                                               &bytes_read);

    *actual_length = bytes_read;

    if (ux_status != UX_SUCCESS)
    {
        return USB_CDC_ERROR_INTERNAL;
    }

    return USB_CDC_OK;
}

UINT usb_cdc_driver_is_connected(VOID)
{
    return usb_cdc_connected;
}
