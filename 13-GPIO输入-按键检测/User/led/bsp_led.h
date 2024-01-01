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
/*----------------------------------------------------------------
^= 异或运算 (a ^ b) 则ab不同为1，相同则为0
ODR低16位和GPIO_Pin_1作异或并重新赋值给ODR可实现ODR的Bit0翻转
若Bit0=1则Bit0 = 1 ^ 1 = 0, 下一次运算时, Bit0=0则Bit0 = 0^1 = 1
实际上是ODR的Bit0在和1进行异或操作
----------------------------------------------------------------*/

// 函数声明
void LED_GPIO_Config(void);

#endif // !__BSP_LED_H
