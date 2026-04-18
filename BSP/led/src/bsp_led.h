/************************************************************************
 * @file bsp_led.h
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
#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "main.h"
#include <stdint.h>
#include <stdio.h>

/*				Core Os				layer*/
#include "cmsis_os.h"
//
#include "queue.h" //specific file for operations
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
/*********************Defines****************/
extern QueueHandle_t led_queue;
extern osThreadId_t Led_TaskHandle;
extern const osThreadAttr_t Led_Task_attributes;
/*********************Defines***************/

typedef enum
{
    LED_OK = 0,
    LED_ERROR,
    LED_TIMEOUT,
    LED_ERRORPARAM,
    LED_ERRORRESOURCE,
} led_status_t;
typedef enum
{
    LED_ON,
    LED_OFF,
    LED_TOGGLE,
} led_operation_t;
/**
 * @brief led_control
 *
 * @param led_operation_t
 * @return led_status_t
 */
led_status_t led_control(led_operation_t operation);
void Led_Task(void *argument);
#endif // !__BSP_LED_H
