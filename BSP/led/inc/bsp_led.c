/************************************************************************
 * @file bsp_led.c
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
#include "bsp_led.h"
/**
 * @brief led control function
 *
 * @param 参数名 参数说明
 * @return 返回值说明
 */
QueueHandle_t led_queue;
osThreadId_t Led_TaskHandle;
const osThreadAttr_t Led_Task_attributes = {
    .name = "Led_Task",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityHigh,
};
/**
 * @brief
 *
 * @param 参数名 参数说明
 * @return 返回值说明
 */
void Led_Task(void *argument)
{
    led_operation_t led_opes = LED_OFF;
    led_queue = xQueueCreate(10, sizeof(led_operation_t));
    if (NULL == led_queue)
    {
        printf("Failed to create led queue!\r\n");
        vTaskDelete(NULL);
    }
    else
    {
        printf("Led queue created successfully!\r\n");
    }
    for (;;)
    {
        if (pdTRUE == xQueueReceive(led_queue, &led_opes, portMAX_DELAY))
        {
            printf("Receive led_opes successfully!\r\n");
            led_control(led_opes);
        }
        osDelay(1);
    }
}
led_status_t led_control(led_operation_t operation)
{
    led_status_t ret = LED_ERROR;
    if (LED_ON == operation)
    {

        // Make the LED  On
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
    }
    else if (LED_OFF == operation)
    {
        // Make the LED  Off
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
    }
    else if (LED_TOGGLE == operation)
    {
        // Make the LED  Toggle
        HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    }

    return ret;
}
