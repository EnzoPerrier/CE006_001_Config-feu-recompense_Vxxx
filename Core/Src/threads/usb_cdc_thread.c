/**
  ******************************************************************************
  * @author  Enzo Perrier
  * @file    usb_cdc_thread.c
  * @brief   Thread ThreadX consommateur du CDC-ACM USB.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "threads/usb_cdc_thread.h"
#include "drivers/usb_cdc_driver.h"
#include <string.h>
#include <stdio.h>

/* Private define --------------------------------------------------------------*/

/**
 * @brief Taille du buffer de lecture "brut" par appel a usb_cdc_driver_read().
 * @note  Fixee a 64 octets : c'est la taille maximale de paquet (Max Packet
 *        Size) d'un endpoint bulk USB Full-Speed, qui est la vitesse du
 *        STM32U073 sur son peripherique USB. Lire par blocs de cette taille
 *        est suffisant pour absorber un paquet USB complet en un seul appel
 *        ux_device_class_cdc_acm_read(), sans sur-dimensionner la pile pour
 *        un cas qui ne se presentera pas (une commande utilisateur fait au
 *        plus USB_CDC_THREAD_LINE_MAX_LEN = 128 caracteres, mais elle arrive
 *        typiquement en plusieurs paquets de 64 octets maximum).
 */
#define USB_CDC_THREAD_RX_CHUNK_SIZE       64U

/**
 * @brief Taille du buffer de sortie local pour usb_cdc_thread_send_line().
 * @note  USB_CDC_THREAD_LINE_MAX_LEN pour le contenu + 2 pour "\r\n" + 1
 *        pour le '\0' terminal. Une reponse plus longue que
 *        USB_CDC_THREAD_LINE_MAX_LEN est refusee (cf usb_cdc_thread_send_line),
 *        par coherence avec la longueur max acceptee en reception.
 */
#define USB_CDC_THREAD_TX_BUFFER_SIZE      (USB_CDC_THREAD_LINE_MAX_LEN + 3U)

/** @brief Duree d'attente (ticks) avant nouvelle tentative si non connecte. */
#define USB_CDC_THREAD_RETRY_DELAY_TICKS   50U

/** @brief Timeout d'ecriture utilise par usb_cdc_thread_send_line(). */
#define USB_CDC_THREAD_SEND_TIMEOUT_TICKS  USB_CDC_WAIT_FOREVER

/* Private variables ------------------------------------------------------------*/

static TX_THREAD usb_cdc_rx_thread;

/** @brief Handler courant, UX_NULL si aucun n'est enregistre. */
static usb_cdc_command_handler_t usb_cdc_active_handler = UX_NULL;

/** @brief Buffer d'accumulation de la ligne de commande en cours. */
static CHAR usb_cdc_line_buffer[USB_CDC_THREAD_LINE_MAX_LEN + 1U]; /* +1 pour '\0' */

/** @brief Index d'ecriture courant dans usb_cdc_line_buffer. */
static ULONG usb_cdc_line_index = 0U;

/**
 * @brief UX_TRUE si la ligne en cours a depasse USB_CDC_THREAD_LINE_MAX_LEN.
 * @note  Une fois ce flag leve, tous les caracteres suivants sont ignores
 *        jusqu'au prochain CR/LF : on n'accumule jamais une commande
 *        tronquee, pour ne pas risquer de la dispatcher avec un sens
 *        different de ce que l'utilisateur a tape.
 */
static volatile UINT usb_cdc_line_overflow = UX_FALSE;

/* Private function prototypes -----------------------------------------------*/

static VOID usb_cdc_thread_entry(ULONG thread_input);
static VOID usb_cdc_thread_process_byte(UCHAR byte);
static VOID usb_cdc_thread_reset_line_buffer(VOID);

/* Exported functions ----------------------------------------------------------*/

UINT usb_cdc_thread_init(TX_BYTE_POOL *byte_pool)
{
    UINT tx_status;
    VOID *stack_pointer = UX_NULL;

    if (byte_pool == UX_NULL)
    {
        return TX_PTR_ERROR;
    }

    tx_status = tx_byte_allocate(byte_pool, &stack_pointer,
                                  USB_CDC_THREAD_STACK_SIZE, TX_NO_WAIT);

    if (tx_status != TX_SUCCESS)
    {
        return tx_status;
    }

    /* Etat initial explicite plutot que de compter sur les valeurs
     * statiques par defaut du C, meme si elles sont deja correctes ici. */
    usb_cdc_thread_reset_line_buffer();

    tx_status = tx_thread_create(&usb_cdc_rx_thread,
                                  USB_CDC_THREAD_NAME,
                                  usb_cdc_thread_entry,
                                  0U,
                                  stack_pointer,
                                  USB_CDC_THREAD_STACK_SIZE,
                                  USB_CDC_THREAD_PRIORITY,
                                  USB_CDC_THREAD_PREEMPTION_THRESHOLD,
                                  USB_CDC_THREAD_TIME_SLICE,
                                  TX_AUTO_START);

    return tx_status;
}

VOID usb_cdc_thread_register_command_handler(usb_cdc_command_handler_t handler)
{
    usb_cdc_active_handler = handler;
}

usb_cdc_status_t usb_cdc_thread_send_line(const CHAR *response)
{
    CHAR tx_buffer[USB_CDC_THREAD_TX_BUFFER_SIZE];
    ULONG response_len;
    ULONG actual_length = 0U;
    INT printed;

    if (response == UX_NULL)
    {
        return USB_CDC_ERROR_INVALID_PARAM;
    }

    response_len = (ULONG)strlen(response);

    /* Refus explicite plutot que troncature silencieuse : une reponse
     * tronquee pourrait etre mal interpretee par l'outil cote PC. */
    if (response_len > USB_CDC_THREAD_LINE_MAX_LEN)
    {
        return USB_CDC_ERROR_INVALID_PARAM;
    }

    printed = snprintf(tx_buffer, sizeof(tx_buffer), "%s\r\n", response);

    /* snprintf retourne le nombre de caracteres qui AURAIENT ete ecrits :
     * une valeur negative ou superieure a la taille du buffer indique une
     * troncature ou une erreur d'encodage, a traiter comme une erreur
     * interne plutot que d'envoyer un contenu partiel/corrompu. */
    if ((printed < 0) || ((ULONG)printed >= sizeof(tx_buffer)))
    {
        return USB_CDC_ERROR_INTERNAL;
    }

    return usb_cdc_driver_write((const UCHAR *)tx_buffer, (ULONG)printed,
                                 USB_CDC_THREAD_SEND_TIMEOUT_TICKS,
                                 &actual_length);
}

/* Private functions -------------------------------------------------------------*/

static VOID usb_cdc_thread_entry(ULONG thread_input)
{
    UCHAR rx_chunk[USB_CDC_THREAD_RX_CHUNK_SIZE];
    ULONG actual_length;
    usb_cdc_status_t status;
    ULONG i;

    TX_PARAMETER_NOT_USED(thread_input);

    for (;;)
    {
        status = usb_cdc_driver_read(rx_chunk, sizeof(rx_chunk),
                                      &actual_length, USB_CDC_WAIT_FOREVER);

        if (status == USB_CDC_OK)
        {
            for (i = 0U; i < actual_length; i++)
            {
                usb_cdc_thread_process_byte(rx_chunk[i]);
            }
        }
        else if (status == USB_CDC_ERROR_NOT_CONNECTED)
        {
            /* Pas d'hote actif : une boucle active (busy loop) gaspillerait
             * du CPU/energie pour rien (carte alimentee sur batterie,
             * cf BAT_CHG/BAT_PGOOD). On retente apres une courte pause
             * plutot que de reessayer immediatement en boucle serree. */
            (VOID)tx_thread_sleep(USB_CDC_THREAD_RETRY_DELAY_TICKS);
        }
        else
        {
            /* USB_CDC_ERROR_NOT_INITIALIZED, INTERNAL, INVALID_PARAM :
             * ne devraient pas survenir ici en usage normal (les
             * parametres passes a usb_cdc_driver_read sont constants et
             * valides, et ce thread n'est demarre qu'apres
             * usb_cdc_driver_init()). Meme pause de securite pour ne pas
             * tourner en boucle serree si un cas non anticipe survient.
             * TODO: brancher ici un mecanisme de log/trace d'erreur une
             * fois celui-ci disponible dans le projet, pour rendre ce
             * cas visible plutot que silencieux. */
            (VOID)tx_thread_sleep(USB_CDC_THREAD_RETRY_DELAY_TICKS);
        }
    }
}

static VOID usb_cdc_thread_process_byte(UCHAR byte)
{
    if ((byte == (UCHAR)'\r') || (byte == (UCHAR)'\n'))
    {
        if (usb_cdc_line_overflow == UX_TRUE)
        {
            /* Fin de la ligne trop longue : on informe l'utilisateur
             * plutot que d'ignorer silencieusement son erreur de saisie. */
            (VOID)usb_cdc_thread_send_line("!ERROR LINE_TOO_LONG");
            usb_cdc_thread_reset_line_buffer();
        }
        else if (usb_cdc_line_index == 0U)
        {
            /* Ligne vide (CR seul, LF seul, ou CRLF splitte en deux appels) :
             * comportement normal des terminaux serie, ignore silencieusement. */
        }
        else
        {
            usb_cdc_line_buffer[usb_cdc_line_index] = '\0';

            if (usb_cdc_active_handler != UX_NULL)
            {
                usb_cdc_active_handler(usb_cdc_line_buffer);
            }
            /* @note Choix assume : si aucun handler n'est enregistre, la
             * commande recue est silencieusement ignoree (pas de reponse
             * d'erreur, car ce cas ne correspond pas a une erreur de
             * l'utilisateur mais a un etat d'initialisation du firmware). */

            usb_cdc_thread_reset_line_buffer();
        }
    }
    else
    {
        if (usb_cdc_line_overflow == UX_TRUE)
        {
            /* Deja en depassement pour cette ligne : on continue a ignorer
             * les caracteres jusqu'au prochain CR/LF (traite ci-dessus). */
        }
        else if (usb_cdc_line_index < USB_CDC_THREAD_LINE_MAX_LEN)
        {
            usb_cdc_line_buffer[usb_cdc_line_index] = (CHAR)byte;
            usb_cdc_line_index++;
        }
        else
        {
            /* Buffer plein sans CR/LF recu : on leve le flag d'overflow.
             * Aucune ecriture supplementaire dans usb_cdc_line_buffer tant
             * que ce flag est actif (protection contre le debordement). */
            usb_cdc_line_overflow = UX_TRUE;
        }
    }
}

static VOID usb_cdc_thread_reset_line_buffer(VOID)
{
    usb_cdc_line_index = 0U;
    usb_cdc_line_buffer[0] = '\0';
    usb_cdc_line_overflow = UX_FALSE;
}
