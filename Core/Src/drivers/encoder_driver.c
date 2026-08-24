/**
 ******************************************************************************
 * @author  Enzo Perrier
 * @file    encoder_driver.c
 * @brief   Driver bas niveau pour l'encodeur rotatif (LPTIM3 en mode Encoder)
 *
 * Ce module encapsule l'accès matériel au LPTIM3 configuré en mode encodeur.
 * Il expose une interface indépendante de l'implémentation HAL sous-jacente,
 * afin que le code applicatif (menu, app_state...) n'ait jamais à connaître
 * le handle hlptim3 ni les détails d'accès registre.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "encoder_driver.h"
#include "stm32u0xx_hal_lptim.h"

#include <stdbool.h>

/* Extern variables ---------------------------------------------------------*/

extern LPTIM_HandleTypeDef hlptim3;

/* Private constants ---------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static bool encoder_status = false;

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/**
 * @brief  				 Initialisation du module.
 * @retval ENCODER_OK    Encodeur initialisé.
 * @retval ENCODER_ERROR Initialization failed.
 */
Encoder_Status_t Encoder_Init(void)
{
    /* TODO: Initialize module */

	if(HAL_LPTIM_Encoder_Start(&hlptim3) != HAL_OK){
		encoder_status = false;
		return ENCODER_ERROR;
	}else{
		encoder_status = true;
		return ENCODER_OK;
	}
}

/* Private functions ---------------------------------------------------------*/

/**
 * @brief 				 		   Cette fonction permet de récupérer la valeur de l'encodeur.
 * @retval ENCODER_OK    		   Lecture OK.
 * @retval ENCODER_NOT_INITIALIZED driver non initialisé.
 * @retval ENCODER_INVALID_PARAM   paramètre invalide passé dans la fonction (ex: pointeur = NULL).
 */
Encoder_Status_t Encoder_GetPosition(int32_t *p_position)
{
	if(p_position == NULL)
	{
		return(ENCODER_INVALID_PARAM);
	}

	if(encoder_status == false)
	{
		return(ENCODER_NOT_INITALIZED);
	}

	*p_position = HAL_LPTIM_ReadCounter(&hlptim3);
	return ENCODER_OK;


}

