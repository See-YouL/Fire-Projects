#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include "stm32f10x.h"

#define KEY_ON 1
#define KEY_OFF 0

// 宏定义
#define KEY1_GPIO_PIN GPIO_Pin_0 // stm32f10x_gpio.h中定义
#define KEY1_GPIO_PORT GPIOA // stm32f10x.h中定义 
#define KEY1_GPIO_CLK RCC_APB2Periph_GPIOA
#define KEY2_GPIO_PIN GPIO_Pin_13 // stm32f10x_gpio.h中定义
#define KEY2_GPIO_PORT GPIOC // stm32f10x.h中定义 
#define KEY2_GPIO_CLK RCC_APB2Periph_GPIOC

// 函数声明
void KEY_GPIO_Config(void);
uint8_t Key_Scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

#endif // !__BSP_KEY_H
