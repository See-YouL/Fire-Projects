/**                             
  ******************************************************************************
  **--------------------------------------------------------------------------**
  ** @FileName      : main.c  
  ** @Brief         : 增加复位/置位函数
  **--------------------------------------------------------------------------**
  ** @Author Data   : Eric 2023-12-29
  ** @Version       : v1.0				
  **--------------------------------------------------------------------------**
  ** @Function List : None
  **--------------------------------------------------------------------------**
  ** @Attention     : Complier(V.6.19)
  **--------------------------------------------------------------------------**
  ******************************************************************************
  *
 **/
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"


int main(void)
{
  RCC->APB2ENR |= ((1) << 3); // 开启GPIOB的时钟

  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHZ;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_ResetBits(GPIOB, GPIO_Pin_1); // PB1置0 蓝灯亮
}

// Arm6 编译器不需要下面的操作
void SystemInit(void)
{
    // 函数体为空，目的是骗过编译器不报错
}
