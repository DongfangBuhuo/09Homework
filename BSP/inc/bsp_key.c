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
/**
 * @brief
 *
 * @param 参数名 参数说明
 * @return 返回值说明
 */
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
