/**
  ******************************************************************************
  * @author Enzo Perrier
  * @file    usb_cdc_thread.h
  * @brief   Thread ThreadX consommateur du CDC-ACM USB : reception, decoupage
  *          en lignes de commande (CR/LF), dispatch vers un handler externe.
  *
  * @note    Ce module est l'UNIQUE consommateur autorise de
  *          usb_cdc_driver_read() (contrainte documentee dans usb_cdc_driver.h).
  ******************************************************************************
  */
#ifndef __USB_CDC_THREAD_H__
#define __USB_CDC_THREAD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "tx_api.h"
#include "drivers/usb_cdc_driver.h"

/* Exported constants ----------------------------------------------------------*/

/** @brief Taille max d'une ligne de commande (hors CR/LF), en octets. */
#define USB_CDC_THREAD_LINE_MAX_LEN        128U

/** @brief Taille de pile allouee au thread (en octets). */
#define USB_CDC_THREAD_STACK_SIZE          1024U

/**
 * @brief Priorite ThreadX du thread (0 = plus haute priorite).
 * @note  Valeur provisoire. A ajuster selon la cartographie globale des
 *        priorites du projet une fois celle-ci definie (ce thread traite
 *        des commandes utilisateur : il n'a pas besoin d'une priorite
 *        aussi haute que les threads internes USBX qui gerent le
 *        transfert USB temps reel, cf UX_DEVICE_APP_THREAD_PRIO = 10
 *        dans app_usbx_device.h). Documenter ici la decision finale et
 *        sa justification une fois tranchee.
 */
#define USB_CDC_THREAD_PRIORITY            15U
#define USB_CDC_THREAD_PREEMPTION_THRESHOLD USB_CDC_THREAD_PRIORITY
#define USB_CDC_THREAD_TIME_SLICE          TX_NO_TIME_SLICE
#define USB_CDC_THREAD_NAME                "usb_cdc_thread"

/* Exported types ----------------------------------------------------------------*/

/**
 * @brief Prototype du handler de commande, a fournir par le module qui
 *        implemente la semantique des commandes (parsing, execution).
 * @param command_line  Chaine terminee par '\0', SANS le CR/LF. Duree de
 *                       vie limitee a l'appel : le handler doit copier
 *                       ce qu'il souhaite conserver au-dela.
 * @note  Appelee dans le contexte du thread usb_cdc_thread : ne doit pas
 *        bloquer indefiniment, sous peine de ne plus pouvoir recevoir de
 *        nouvelles donnees USB pendant ce temps.
 */
typedef VOID (*usb_cdc_command_handler_t)(const CHAR *command_line);

/* Exported functions prototypes ---------------------------------------------*/

/**
 * @brief   Cree et demarre le thread de reception/dispatch des commandes.
 * @param   byte_pool  Pool memoire ThreadX utilise pour allouer la pile du
 *                      thread (meme convention que MX_USBX_Device_Init()).
 * @note    A appeler apres usb_cdc_driver_init(), le thread appelant
 *          usb_cdc_driver_read() en boucle des son demarrage.
 * @retval  TX_SUCCESS si la creation a reussi, code d'erreur ThreadX sinon.
 */
UINT usb_cdc_thread_init(TX_BYTE_POOL *byte_pool);

/**
 * @brief   Enregistre le handler appele a chaque commande complete recue.
 * @param   handler  Fonction a appeler. UX_NULL pour desenregistrer
 *                     (les commandes recues seront alors silencieusement
 *                     ignorees - comportement a documenter comme assume,
 *                     pas comme un defaut cache).
 * @note    Non thread-safe par conception : a appeler une seule fois,
 *          typiquement a l'initialisation, avant que le thread ne
 *          traite de commandes.
 */
VOID usb_cdc_thread_register_command_handler(usb_cdc_command_handler_t handler);

/**
 * @brief   Envoie une reponse texte, en ajoutant automatiquement CR/LF.
 * @param   response  Chaine terminee par '\0' a envoyer (sans CR/LF).
 * @retval  USB_CDC_OK ou un code d'erreur usb_cdc_status_t (cf usb_cdc_driver.h).
 * @note    Fonction utilitaire pour garder une convention de reponse
 *          coherente (tous les handlers repondent de la meme facon).
 */
usb_cdc_status_t usb_cdc_thread_send_line(const CHAR *response);

#ifdef __cplusplus
}
#endif
#endif /* __USB_CDC_THREAD_H__ */
