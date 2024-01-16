#ifndef __BSP_EXTI_H
#define __BSP_EXTI_H

#include "stm32f10x.h"

// 宏定义
#define KEY1_INT_GPIO_PIN GPIO_Pin_0 // stm32f10x_gpio.h中定义
#define KEY1_INT_GPIO_PORT GPIOA // stm32f10x.h中定义 
#define KEY1_INT_GPIO_CLK RCC_APB2Periph_GPIOA

void EXTI_Key_Config(void);

#endif // !__BSP_EXTI_H