/**
  ******************************************************************************
  * @file    bsp_led.h
  * @author  eric
  * @version V0.0.1
  * @date   29-December-2024 
  * @brief  LED蓝灯GPIO端口定义 
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FUCTIONS WHICH IS FOR GUIDANCE ONLY
  ******************************************************************************
  */

#ifndef __BSP_LED_H
#define __BSP_LED_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

#define LED_B_GPIO_PIN GPIO_Pin_1 //!< 引脚1 
#define LED_B_GPIO_PORT GPIOB //!< 端口B 
#define LED_B_GPIO_CLK RCC_APB2Periph_GPIOB //!< 端口时钟GPIOB

#define ON 1 //!< 亮为1
#define OFF 0 //!< 灭为0

// 参数为1时IO口输出低电平，灯亮；参数为0时IO口输出高电平，灯灭
#define LED_B(a) if (a)\
                     GPIO_ResetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN); \
                     else\
                     GPIO_SetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN);
// 使用\可以进行换行，其后不能跟空格，\后应该直接回车

void LED_GPIO_Config(void);

#endif // !__BSP_LED_H
