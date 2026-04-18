/************************************************************************
 * @file bsp_key.c
 * @brief 文件功能简述
 *
 * 详细描述:
 * - 功能1: 具体描述
 * - 功能2: 具体描述
 *
 * @author DFBH
 * @date 2026-04-18
 * @version 1.0.0
 *
 * @note 备注信息 (可选)
 * @warning 警告信息 (可选)
 ************************************************************************/
#include "bsp_key.h"

/********************Defines***************/
QueueHandle_t key_queue;
osThreadId_t Key_TaskHandle;
const osThreadAttr_t Key_Task_attributes = {
    .name = "Key_Task",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityHigh,
};
/**
 * @brief
 *
 * @param 参数名 参数说明
 * @return 返回值说明
 */
void Key_Task(void *argument)
{
    key_status_t key_status = KEY_OK;
    key_press_status_t key_press_status = KEY_NOT_PRESSED;
    uint32_t count_tick = 0;
    key_queue = xQueueCreate(10, sizeof(count_tick));
    if (NULL == key_queue)
    {
        printf("Failed to create led queue!\r\n");
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
key_status_t key_read(key_press_status_t *key_value)
{
    uint32_t counter = 0;
    key_press_status_t key_status = KEY_NOT_PRESSED;
    while (counter < 1000)
    {
        if (HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin) == GPIO_PIN_RESET)
        {
            key_status = KEY_PRESSED;
            *key_value = key_status;
            return KEY_OK;
        }
        counter++;
    }
    return KEY_TIMEOUT;
}
