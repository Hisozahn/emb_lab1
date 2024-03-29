/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "gpio.h"
#include "oled.h"
#include "fonts.h"
#include "keyboard.h"
#include "../snk/snk.h"
#include "../snk/snk_util.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MAX_GLOABL_QUEUE_MSG_COUNT 100
#define MAX_GLOABL_QUEUE_MSG_SIZE 1
#define MAX_TIMER_QUEUE_MSG_COUNT 100
#define MAX_TIMER_QUEUE_MSG_SIZE 1
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
osMessageQueueId_t global_queue;
osMessageQueueId_t timer_queue;
/* USER CODE END Variables */
osThreadId_t task_1Handle;
osThreadId_t task_2Handle;
osTimerId_t global_timerHandle;
osMutexId_t global_mutexHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void start_task_1(void *argument);
void start_task_2(void *argument);
void global_timer_callback(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */
osKernelInitialize();

  /* Create the mutex(es) */
  /* definition and creation of global_mutex */
  const osMutexAttr_t global_mutex_attributes = {
    .name = "global_mutex"
  };
  global_mutexHandle = osMutexNew(&global_mutex_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* definition and creation of global_timer */
  const osTimerAttr_t global_timer_attributes = {
    .name = "global_timer"
  };
  global_timerHandle = osTimerNew(global_timer_callback, osTimerPeriodic, NULL, &global_timer_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of task_1 */
  const osThreadAttr_t task_1_attributes = {
    .name = "task_1",
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 4096
  };
  task_1Handle = osThreadNew(start_task_1, NULL, &task_1_attributes);

  /* definition and creation of task_2 */
  const osThreadAttr_t task_2_attributes = {
    .name = "task_2",
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 1024
  };
  task_2Handle = osThreadNew(start_task_2, NULL, &task_2_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  osTimerStart(global_timerHandle, 100);
  global_queue = osMessageQueueNew(MAX_GLOABL_QUEUE_MSG_COUNT, MAX_GLOABL_QUEUE_MSG_SIZE, NULL);
  timer_queue = osMessageQueueNew(MAX_TIMER_QUEUE_MSG_COUNT, MAX_TIMER_QUEUE_MSG_SIZE, NULL);
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_start_task_1 */
/**
  * @brief  Function implementing the task_1 thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_start_task_1 */
void start_task_1(void *argument)
{
  /* USER CODE BEGIN start_task_1 */
	 uint8_t buf[MAX_GLOABL_QUEUE_MSG_SIZE] = {0};
		  //snk_field_obstacle obstacles[] = {{{0, 0}, {5, 0}}};
		  snk_position start_position = {5, 5};
		  snk_process process;
		  snk_field field;
		  uint8_t draw_data[2048];

		  snk_create_field(42, 20, 0, NULL, 1, &field);

		  snk_create(&field, &start_position, SNK_DIRECTION_RIGHT, 5, &process);

	  /* Infinite loop */
	  for(;;)
	  {
		  if (osMessageQueueGet(global_queue, buf, 0, 10) == osOK)
		  {
			  snk_choose_direction(&process, buf[0]);
		  }
		  if (osMessageQueueGet(timer_queue, buf, 0, 10) == osOK)
		  {
			  snk_next_tick(&process);
			  snk_render(&process, draw_data, sizeof(draw_data));
			  oled_SetCursor(0, 0);
			  oled_Fill(Black);
			  oled_DrawData(draw_data, field.width, field.height);
			  oled_UpdateScreen();
		  }

	  }
  /* USER CODE END start_task_1 */
}

/* USER CODE BEGIN Header_start_task_2 */
/**
* @brief Function implementing the task_2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_start_task_2 */
void start_task_2(void *argument)
{
  /* USER CODE BEGIN start_task_2 */
	uint8_t buf[MAX_GLOABL_QUEUE_MSG_SIZE] = {0};
    snk_direction new_direction;
    keyboard_key_set key_set_old;
    keyboard_key_set key_set_new;
    keyboard_key_set key_set;
	//int i;
	int rc;
	keyboard_Get(&key_set_old);

	while (1)
	{
		osDelay(1..0);
		rc = keyboard_Get(&key_set_new);
		//rc = 1;
		if (rc == 0 && key_set_new != key_set_old)
		{
			key_set = (~key_set_old) & key_set_new;
			key_set_old = key_set_new;
			if (keyboard_key_is_in_set(KEYBOARD_KEY_1, &key_set))
			{
				new_direction = SNK_DIRECTION_UP;
			}
			else if (keyboard_key_is_in_set(KEYBOARD_KEY_3, &key_set))
			{
				new_direction = SNK_DIRECTION_LEFT;
			}
			else if (keyboard_key_is_in_set(KEYBOARD_KEY_4, &key_set))
			{
				new_direction = SNK_DIRECTION_DOWN;
			}
			else if (keyboard_key_is_in_set(KEYBOARD_KEY_5, &key_set))
			{
				new_direction = SNK_DIRECTION_RIGHT;
			}
			else
			{
				continue;
			}
			buf[0] = new_direction;
			osMessageQueuePut(global_queue, buf, 0, 5000);
		}
	}
  /* USER CODE END start_task_2 */
}

/* global_timer_callback function */
void global_timer_callback(void *argument)
{
  /* USER CODE BEGIN global_timer_callback */
	uint8_t buf[MAX_TIMER_QUEUE_MSG_SIZE] = {0};
#if 0
    keyboard_key_set key_set;
	int i;
	int rc;
	char display_str[40] = "error";

	rc = keyboard_Get(&key_set);
	if (rc == 0)
	{
		for (i = 0; i < 12; i++)
		{
			display_str[11 - i] = key_set % 2 == 0 ? '0' : '1';
			key_set >>= 1;
		}
		display_str[12] = '\0';
	}

	//HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
	oled_SetCursor(0, 0);
	oled_Fill(Black);
	oled_WriteString(display_str, Font_7x10, White);
	//oled_WriteString((i++ % 2) == 0 ? "kek" : "lol", Font_16x26, White);
	oled_UpdateScreen();
	osMessageQueuePut(timer_queue, buf, 0, 5000);
#else
	osMessageQueuePut(timer_queue, buf, 0, 5000);
#endif
  /* USER CODE END global_timer_callback */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
