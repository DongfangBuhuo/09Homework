/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "main.h"
#include "queue.h"
#include "task.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bsp_key.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
void Key_Task(void *argument);
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
QueueHandle_t key_queue;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
    .name = "defaultTask",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
osThreadId_t Key_TaskHandle;
const osThreadAttr_t Key_Task_attributes = {
    .name = "Key_Task",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityHigh,
};
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void)
{
    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
    /* USER CODE END RTOS_MUTEX */

    /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
    /* USER CODE END RTOS_SEMAPHORES */

    /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
    /* USER CODE END RTOS_TIMERS */

    /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
    /* USER CODE END RTOS_QUEUES */

    /* Create the thread(s) */
    /* creation of defaultTask */
    defaultTaskHandle =
        osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

    /* USER CODE BEGIN RTOS_THREADS */
    Key_TaskHandle = osThreadNew(Key_Task, NULL, &Key_Task_attributes);
    /* add threads, ... */
    /* USER CODE END RTOS_THREADS */

    /* USER CODE BEGIN RTOS_EVENTS */
    /* add events, ... */
    /* USER CODE END RTOS_EVENTS */
}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
    /* USER CODE BEGIN StartDefaultTask */
    /* Infinite loop */
    uint32_t count_tick = 0;
    for (;;)
    {
        if (NULL != key_queue)
        {
            if (pdTRUE == xQueueReceive(key_queue, &count_tick, 0))
            {
                printf("Received key status from queue: %d\n", count_tick);
            }
        }
        osDelay(1);
    }
    /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void Key_Task(void *argument)
{
    key_status_t key_status = KEY_OK;
    key_press_status_t key_press_status = KEY_NOT_PRESSED;
    uint32_t count_tick = 0;
    key_queue = xQueueCreate(10, sizeof(count_tick));
    if (NULL == key_queue)
    {
        printf("Failed to create key queue!\r\n");
        vTaskDelete(NULL);
    }
    else
    {
        printf("Key queue created successfully!\r\n");
    }
    for (;;)
    {
        count_tick++;
        key_status = key_read(&key_press_status);
        if (KEY_OK == key_status)
        {
            if (KEY_PRESSED == key_press_status)
            {
                printf("Key Pressed!\r\n");
                if (pdPASS == xQueueSendToFront(key_queue, &count_tick, 0))
                {
                    printf("Key status sent to queue successfully!\r\n");
                }
                else
                {
                    printf("Failed to send key status to queue!\r\n");
                }
            }
        }
        else
        {
            printf("Key Not Pressed!\r\n");
        }
        osDelay(500);
    }
}
/* USER CODE END Application */
