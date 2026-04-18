/************************************************************************
 * @file bsp_key.h
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
#ifndef __BSP_KEY_H
#define __BSP_KEY_H
/**********************Includes**********************/
#include "main.h"
#include <stdint.h>
#include <stdio.h>

/*				Core Os				layer*/
#include "cmsis_os.h"
//
#include "queue.h" //specific file for operations
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"

/**********************Includes*******************/
/**********************Defines**********************/
extern QueueHandle_t key_queue;
extern osThreadId_t Key_TaskHandle;
extern const osThreadAttr_t Key_Task_attributes;
typedef enum
{
    KEY_OK = 0,
    KEY_ERROR,
    KEY_TIMEOUT,
    KEY_ERRORPARAM,
    KEY_ERRORRESOURCE,
} key_status_t;
typedef enum
{
    KEY_PRESSED,
    KEY_NOT_PRESSED,
} key_press_status_t;


key_status_t key_read(key_press_status_t *key_value);
void Key_Task(void *argument);
#endif // !__BSP_KEY_H
