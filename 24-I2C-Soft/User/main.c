/**
  ******************************************************************************
  * @file    main.c
  * @author  eric
  * @version V0.0.1
  * @date    31-January-2024
  * @brief   STM32与EEPROM通过软件I2C进行读写测试
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FUCTIONS WHICH IS FOR GUIDANCE ONLY
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_i2c_ee.h"
#include "bsp_i2c_gpio.h"


/**
 * @brief 进行软件模拟I2C与EEPROM通信的读写测试 
 * @param None
 * @retval None 
 */
int main(void)
{
    /* LED_GPIO配置*/
    LED_GPIO_Config();
    /* 亮蓝灯 */
    LED_BLUE;
    /* USART初始化 */
    USART_Config();
    /* 打印测试开始信息 */
    printf("EEPROM Software Test Begin \r\n");
    if (ee_Test() == 1) /* 测试成功 */
    {
        /* 亮绿灯 */
        LED_GREEN;
    }
    else /* 测试不通过 */
    {
        /* 亮红灯 */
        LED_RED;
    }
    
    /* 空循环 */
    while(1)
    {
        ;
    }
}
