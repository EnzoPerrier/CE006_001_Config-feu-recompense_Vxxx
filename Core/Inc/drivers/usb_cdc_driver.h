/**
  ******************************************************************************
  * @author  Enzo Perrier
  * @file    usb_cdc_driver.h
  * @brief   Driver applicatif au-dessus de la classe USBX CDC-ACM.
  *          Fait le pont entre les callbacks generes par CubeMX
  *          (ux_device_cdc_acm.c) et le reste du firmware.
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

/* Timeout "infini" pratique pour les appels bloquants (attend indefiniment) */
#define USB_CDC_WAIT_FOREVER   TX_WAIT_FOREVER

/* Exported functions prototypes ---------------------------------------------*/

/**
 * @brief  Initialise l'etat interne du driver (mutex, flags...).
 *         A appeler une seule fois, avant MX_USBX_Device_Init()
 *         ou juste apres, mais avant toute utilisation de write/read.
 * @retval TX_SUCCESS si l'init a reussi, code d'erreur ThreadX sinon.
 */
UINT usb_cdc_driver_init(VOID);

/**
 * @brief  A appeler depuis USBD_CDC_ACM_Activate() (ux_device_cdc_acm.c).
 *         Capture le pointeur d'instance CDC-ACM et marque la liaison
 *         comme "connectee" (l'hote a ouvert le port COM virtuel).
 * @param  cdc_instance: pointeur fourni par USBX (UX_SLAVE_CLASS_CDC_ACM*)
 */
VOID usb_cdc_driver_on_activate(VOID *cdc_instance);

/**
 * @brief  A appeler depuis USBD_CDC_ACM_Deactivate().
 *         Marque la liaison comme "deconnectee".
 * @param  cdc_instance: pointeur fourni par USBX
 */
VOID usb_cdc_driver_on_deactivate(VOID *cdc_instance);

/**
 * @brief  A appeler depuis USBD_CDC_ACM_ParameterChange().
 *         Hook disponible si tu veux reagir a un changement de line coding.
 * @param  cdc_instance: pointeur fourni par USBX
 */
VOID usb_cdc_driver_on_parameter_change(VOID *cdc_instance);

/**
 * @brief  Envoie des donnees sur le port COM virtuel. Thread-safe :
 *         peut etre appelee depuis plusieurs threads simultanement.
 * @param  data: buffer a envoyer
 * @param  length: nombre d'octets a envoyer
 * @param  timeout_ticks: delai d'attente ThreadX (en ticks) si le mutex
 *         ou l'envoi USB est occupe. Utiliser USB_CDC_WAIT_FOREVER
 *         pour bloquer indefiniment.
 * @retval UX_SUCCESS si l'envoi a reussi, code d'erreur USBX/ThreadX sinon.
 */
UINT usb_cdc_driver_write(const UCHAR *data, ULONG length, ULONG timeout_ticks);

/**
 * @brief  Recoit des donnees depuis le port COM virtuel (appel bloquant).
 *         IMPORTANT : ne doit etre appelee que par UN SEUL thread
 *         "consommateur" dans le firmware (ex: le thread console USB).
 * @param  buffer: buffer de reception fourni par l'appelant
 * @param  buffer_size: taille max du buffer
 * @param  actual_length: [out] nombre d'octets reellement recus
 * @param  timeout_ticks: delai d'attente ThreadX (en ticks)
 * @retval UX_SUCCESS si des donnees ont ete recues, code d'erreur sinon.
 */
UINT usb_cdc_driver_read(UCHAR *buffer, ULONG buffer_size,
                          ULONG *actual_length, ULONG timeout_ticks);

/**
 * @brief  Indique si un hote (PC) a actuellement ouvert le port COM virtuel.
 *         Utile pour eviter d'appeler write() en pure perte (timeout inutile)
 *         quand rien n'est branche.
 * @retval UX_TRUE si connecte, UX_FALSE sinon.
 */
UINT usb_cdc_driver_is_connected(VOID);

#ifdef __cplusplus
}
#endif
#endif /* __USB_CDC_DRIVER_H__ */
