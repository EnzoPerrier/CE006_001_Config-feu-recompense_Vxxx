/**
 ******************************************************************************
 * @author  Enzo Perrier
 * @file    ui_thread.c
 * @brief   Thread applicatif "UI" : encodeur, bouton de l'encodeur, écran/menu.
 *
 * Ce thread attend les événements liés à l'interaction utilisateur (rotation
 * de l'encodeur, appui du bouton) via le groupe d'event flags ui_events_group
 * (créé dans app_threadx.c), puis appelle les drivers concernés
 * (encoder_driver, futur ecran_driver) pour réagir en conséquence.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "threads/ui_thread.h"

/* Private includes ----------------------------------------------------------*/

/* Extern variables ---------------------------------------------------------*/

// Groupe d'event flags créé et initialisé dans app_threadx.c (App_ThreadX_Init)
extern TX_EVENT_FLAGS_GROUP ui_events_group;

/* Private constants ---------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static int debug_count = 0;

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/**
 * @brief  Point d'entrée du thread UI.
 * @note   Signature imposée par ThreadX (VOID (*)(ULONG)) pour tx_thread_create.
 * @param  initial_input Non utilisé (imposé par la signature ThreadX).
 * @retval None
 */
void UI_Thread_Entry(ULONG initial_input)
{
	ULONG flags_recus;

	(void)initial_input; // Pour supprimer le warning paramètre non utilisé

	while(1)
	{
		// Attente bloquante (le thread ne consomme pas de CPU pendant l'attente)
		// jusqu'à ce qu'au moins un des flags demandés soit levé.
		// TX_OR_CLEAR : réveil sur n'importe quel flag demandé, et remise à zéro
		// automatique des flags lus (pour ne pas re-traiter le même événement).
		tx_event_flags_get(&ui_events_group,
							UI_EVENT_BUTTON_PRESSED | UI_EVENT_ENCODER_MOVED,
							TX_OR_CLEAR,
							&flags_recus,
							TX_WAIT_FOREVER);

		/* TODO: traiter le(s) flag(s) reçu(s) (voir flags_recus), une fois
		 * les drivers bouton et écran/menu disponibles :
		 *  - if (flags_recus & UI_EVENT_BUTTON_PRESSED) { ... }
		 *  - if (flags_recus & UI_EVENT_ENCODER_MOVED)  { ... }
		 */

		if(flags_recus & UI_EVENT_BUTTON_PRESSED){
			// Action à exécuter en cas de détection d'appui sur BP
			debug_count++;
		}

		/* Fonction non utilisée car l'encodeur est actuellement en polling, à utiliser plus tard si on le passe en interruption
		if(flags_recus & UI_EVENT_ENCODER_MOVED){
			// Action à exécuter en cas de détection de rotation d'encodeur
		}
		*/
	}
}

/* Private functions ---------------------------------------------------------*/
