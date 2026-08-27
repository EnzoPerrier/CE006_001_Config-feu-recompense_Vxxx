/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_threadx.c
  * @author  MCD Application Team
  * @brief   ThreadX applicative file
  ******************************************************************************
    * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "app_threadx.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "main.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define UI_THREAD_STACK_SIZE   (1024)   // en octets

#define UI_THREAD_PRIORITY     (2)

#define UI_EVENT_BUTTON_PRESSED   (1 << 0)   // bit 0
#define UI_EVENT_ENCODER_MOVED    (1 << 1)   // bit 1

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/*-------------- UI THREAD */
UCHAR ui_thread_stack[UI_THREAD_STACK_SIZE];
TX_THREAD ui_thread;
TX_EVENT_FLAGS_GROUP ui_events_group;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/**
  * @brief  Application ThreadX Initialization.
  * @param memory_ptr: memory pointer
  * @retval int
  */
UINT App_ThreadX_Init(VOID *memory_ptr)
{
  UINT ret = TX_SUCCESS;
  /* USER CODE BEGIN App_ThreadX_MEM_POOL */


  /* USER CODE END App_ThreadX_MEM_POOL */
  /* USER CODE BEGIN App_ThreadX_Init */

  ret = tx_event_flags_create(&ui_events_group, "UI Events"); // Creation de flags pour détection d'appui BP/mouvement encodeur

  ret = tx_thread_create(
      &ui_thread,             // 1) thread_ptr
      "UI_THREAD",             // 2) name_ptr
      UI_Thread_Entry,          // 3) entry_function
      0,                        // 4) entry_input
      ui_thread_stack,          // 5) stack_start
      UI_THREAD_STACK_SIZE,     // 6) stack_size
      UI_THREAD_PRIORITY,       // 7) priority
      UI_THREAD_PRIORITY,       // 8) preempt_threshold
      TX_NO_TIME_SLICE,         // 9) time_slice
      TX_AUTO_START             // 10) auto_start
  );

  if (ret != TX_SUCCESS)
  {
      Error_Handler();
  }

  /* USER CODE END App_ThreadX_Init */

  return ret;
}

  /**
  * @brief  Function that implements the kernel's initialization.
  * @param  None
  * @retval None
  */
void MX_ThreadX_Init(void)
{
  /* USER CODE BEGIN Before_Kernel_Start */

  /* USER CODE END Before_Kernel_Start */

  tx_kernel_enter();

  /* USER CODE BEGIN Kernel_Start_Error */

  /* USER CODE END Kernel_Start_Error */
}

/* USER CODE BEGIN 1 */

/**
  * @brief  UI Thread
  * @param Imposé par ThreadX, non utilisé (void (*)(ULONG))
  * @retval None
  */


/* USER CODE END 1 */
