/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  eric
  * @version V0.0.1
  * @date   29-December-2024 
  * @brief  LED蓝灯GPIO配置函数 
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FUCTIONS WHICH IS FOR GUIDANCE ONLY
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_conf.h"
#include "bsp_led.h" // bsp: board support package 板级支持包

/**
 * @brief 配置PB1为推挽输出
 * @param None
 * @retval None 
 */
void LED_GPIO_Config(void)
{
    RCC_APB2PeriphClockCmd(LED_B_GPIO_CLK, ENABLE); // 使能PB端口时钟
    GPIO_InitTypeDef GPIO_InitStruct; // 定义GPIO初始化结构体变量
    GPIO_InitStruct.GPIO_Pin = LED_B_GPIO_PIN; // 1端口
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出模式
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; // 速度50MHz
    GPIO_Init(LED_B_GPIO_PORT, &GPIO_InitStruct); // 初始化PB1
}
