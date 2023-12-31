/**                             
  ******************************************************************************
  **--------------------------------------------------------------------------**
  ** @FileName      : main.c  
  ** @Brief         : 书写库函数  
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

#define LED_B_GPIO_PORT	GPIOB
#define LED_B_GPIO_CLK_ENABLE (RCC->APB2ENR |= ((1) << 3)) 
#define LED_B_GPIO_PIN GPIO_Pin_1

void Delay(uint32_t count)
{
  for( ; count != 0; count-- )
  {
    ;
  }
}

int main(void)
{

#if 0
  // 通过结构体操作寄存器
  RCC->APB2ENR |= ((1) << 3); // 开启GPIOB的时钟
  GPIOB->CRL &= ~((0x0F) << (4*1)); // 将GPIOB状态复位
  GPIOB->CRL |= ((1) << (4*1)); // 将GPIOB设置为推挽输出
  GPIOB->ODR &= ~(1<<1); // PB1置0

#elif 0
  // 增加复位/置位函数
	RCC->APB2ENR  |=  ( (1) << 3 );
	GPIOB->CRL &=  ~( (0x0f) << (4*0) );
	GPIOB->CRL |=  ( (1) << (4*0) );
	GPIO_SetBits(GPIOB,GPIO_Pin_1);
	GPIO_ResetBits( GPIOB,GPIO_Pin_1 );

#elif 0
	RCC->APB2ENR  |=  ( (1) << 3 );
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHZ;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_ResetBits(GPIOB, GPIO_Pin_1); // PB1置0 蓝灯亮

#elif 1
// 增加宏定义以增强代码可移植性
	LED_B_GPIO_CLK_ENABLE;
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = LED_B_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHZ;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  while(1)
  {
    GPIO_SetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN); // PB1置1 蓝灯灭
    Delay(0xFFFF);
    GPIO_ResetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN); // PB1置0 蓝灯亮
    Delay(0xFFFF);
  }

#endif // 0 
}

// Arm6 编译器不需要下面的操作
void SystemInit(void)
{
    // 函数体为空，目的是骗过编译器不报错
}
