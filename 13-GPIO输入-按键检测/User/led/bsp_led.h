#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "stm32f10x.h"

// 宏定义
#define LED_B_GPIO_PIN GPIO_Pin_1 // stm32f10x_gpio.h中定义
#define LED_B_GPIO_PORT GPIOB // stm32f10x.h中定义 
#define LED_B_GPIO_CLK RCC_APB2Periph_GPIOB

#define ON 1 
#define OFF 0
#define LED_B(a) if (a)\
                     GPIO_ResetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN); \
                     else\
                     GPIO_SetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN);
// 使用\可以进行换行，其后不能跟空格，\后应该直接回车
#define LED_B_TOGGLE {LED_B_GPIO_PORT->ODR ^= LED_B_GPIO_PIN;}

// 函数声明
void LED_GPIO_Config(void);

#endif // !__BSP_LED_H
