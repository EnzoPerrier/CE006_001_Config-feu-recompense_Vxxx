/**
  ******************************************************************************
  * @author  Enzo Perrier
  * @file    usb_cdc_driver.h
  * @brief   Driver applicatif au-dessus de la classe USBX CDC-ACM.
  *          Fait le pont entre les callbacks generes par CubeMX
  *          (ux_device_cdc_acm.c) et le reste du firmware.
  *
  * @note    Contrat d'API : ce module encapsule toutes les dependances
  *          USBX/ThreadX. L'appelant ne doit jamais manipuler directement
  *          les types UX_*TX_* : seuls les types et codes definis dans
  *          ce header font foi.
  ******************************************************************************
  */
#ifndef __USB_CDC_DRIVER_H__
#define __USB_CDC_DRIVER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ux_api.h"
#include "tx_api.h"

/* Exported constants --------------------------------------------------------*/

/** @brief Timeout "infini" pour les appels bloquants (attente indefinie). */
#define USB_CDC_WAIT_FOREVER   TX_WAIT_FOREVER

/** @brief Timeout nul : appel non-bloquant (retour immediat si non disponible). */
#define USB_CDC_NO_WAIT         TX_NO_WAIT

/* Exported types --------------------------------------------------------------*/

/**
 * @brief Codes de retour du driver USB CDC.
 * @note  Volontairement independants des codes UX_*TX_* internes,
 *        pour ne pas exposer l'implementation sous-jacente a l'appelant.
 */
typedef enum
{
    USB_CDC_OK = 0,                 /*!< Operation reussie */
    USB_CDC_ERROR_NOT_CONNECTED,    /*!< Aucun hote USB actif (port ferme) */
    USB_CDC_ERROR_INVALID_PARAM,    /*!< Parametre d'entree invalide (NULL, taille 0...) */
    USB_CDC_ERROR_TIMEOUT,          /*!< Timeout atteint avant completion */
    USB_CDC_ERROR_NOT_INITIALIZED,  /*!< usb_cdc_driver_init() non appelee ou echouee */
    USB_CDC_ERROR_INTERNAL          /*!< Erreur interne USBX/ThreadX (voir logs) */
} usb_cdc_status_t;

/* Exported functions prototypes ---------------------------------------------*/

/**
 * @brief   Initialise l'etat interne du driver (mutex, flags...).
 * @note    A appeler une seule fois, avant toute utilisation de
 *          usb_cdc_driver_write()/read(). Doit etre appelee avant que
 *          MX_USBX_Device_Init() ne puisse declencher usb_cdc_driver_on_activate().
 * @retval  USB_CDC_OK si l'initialisation a reussi.
 * @retval  USB_CDC_ERROR_INTERNAL si la creation d'une ressource ThreadX
 *          (mutex...) a echoue.
 */
usb_cdc_status_t usb_cdc_driver_init(VOID);

/**
 * @brief   A appeler depuis USBD_CDC_ACM_Activate() (ux_device_cdc_acm.c).
 * @param   cdc_instance Pointeur d'instance fourni par USBX. Ne doit pas etre NULL.
 * @note    Contexte d'appel : callback USBX (a documenter precisement une
 *          fois verifie : thread USBX interne, contexte non-bloquant a priori).
 */
VOID usb_cdc_driver_on_activate(VOID *cdc_instance);

/**
 * @brief   A appeler depuis USBD_CDC_ACM_Deactivate().
 * @param   cdc_instance Pointeur d'instance fourni par USBX.
 */
VOID usb_cdc_driver_on_deactivate(VOID *cdc_instance);

/**
 * @brief   A appeler depuis USBD_CDC_ACM_ParameterChange().
 * @param   cdc_instance Pointeur d'instance fourni par USBX.
 */
VOID usb_cdc_driver_on_parameter_change(VOID *cdc_instance);

/**
 * @brief   Envoie des donnees sur le port COM virtuel. Thread-safe.
 * @param   data           Buffer a envoyer. Ne doit pas etre NULL.
 * @param   length         Nombre d'octets a envoyer. Doit etre > 0.
 * @param   timeout_ticks  Delai d'attente ThreadX (ticks). USB_CDC_WAIT_FOREVER
 *                         pour bloquer indefiniment, USB_CDC_NO_WAIT pour
 *                         un appel non-bloquant.
 * @param   actual_length  [out] Nombre d'octets reellement envoyes.
 *                         Ne doit pas etre NULL.
 * @retval  USB_CDC_OK, ou un code d'erreur usb_cdc_status_t.
 */
usb_cdc_status_t usb_cdc_driver_write(const UCHAR *data, ULONG length,
                                       ULONG timeout_ticks, ULONG *actual_length);

/**
 * @brief   Recoit des donnees depuis le port COM virtuel (appel bloquant).
 * @warning Ne doit etre appelee que par UN SEUL thread "consommateur"
 *          dans le firmware. Voir @note dans usb_cdc_driver.c pour la
 *          justification de cette contrainte.
 * @param   buffer         Buffer de reception fourni par l'appelant. Ne doit
 *                         pas etre NULL.
 * @param   buffer_size    Taille max du buffer. Doit etre > 0.
 * @param   actual_length  [out] Nombre d'octets reellement recus.
 *                         Ne doit pas etre NULL.
 * @param   timeout_ticks  Delai d'attente ThreadX (ticks).
 * @retval  USB_CDC_OK, ou un code d'erreur usb_cdc_status_t.
 */
usb_cdc_status_t usb_cdc_driver_read(UCHAR *buffer, ULONG buffer_size,
                                      ULONG *actual_length, ULONG timeout_ticks);

/**
 * @brief   Indique si un hote (PC) a actuellement ouvert le port COM virtuel.
 * @retval  UX_TRUE si connecte, UX_FALSE sinon.
 */
UINT usb_cdc_driver_is_connected(VOID);

#ifdef __cplusplus
}
#endif
#endif /* __USB_CDC_DRIVER_H__ */
