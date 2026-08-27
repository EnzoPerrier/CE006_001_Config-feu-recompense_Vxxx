/**
 ******************************************************************************
 * @author  Enzo Perrier
 * @file    ui_thread.h
 * @brief   Thread applicatif "UI" : encodeur, bouton de l'encodeur, écran/menu.
 *
 * Ce thread attend les événements liés à l'interaction utilisateur (rotation
 * de l'encodeur, appui du bouton) via le groupe d'event flags ui_events_group
 * (créé dans app_threadx.c), puis appelle les drivers concernés
 * (encoder_driver, futur ecran_driver) pour réagir en conséquence.
 ******************************************************************************
 */

#ifndef UI_THREAD_H
#define UI_THREAD_H

/* Includes ------------------------------------------------------------------*/
#include "tx_api.h"

/* Exported constants ---------------------------------------------------------*/

/*
 * Bits du groupe d'event flags ui_events_group (défini dans app_threadx.c).
 * Exposés ici (et non dans app_threadx.c) car ce sont d'autres modules,
 * comme encoder_driver.c, qui doivent lever ces flags (tx_event_flags_set)
 * depuis leurs callbacks d'interruption.
 */
#define UI_EVENT_BUTTON_PRESSED   (1 << 0)   // bit 0 : appui sur le bouton de l'encodeur
#define UI_EVENT_ENCODER_MOVED    (1 << 1)   // bit 1 : rotation de l'encodeur détectée

/* Exported functions prototypes ----------------------------------------------*/

/**
 * @brief  Point d'entrée du thread UI.
 * @note   Signature imposée par ThreadX (VOID (*)(ULONG)) pour tx_thread_create.
 * @param  initial_input Non utilisé (imposé par la signature ThreadX).
 * @retval None
 */
void UI_Thread_Entry(ULONG initial_input);

#endif /* UI_THREAD_H */
