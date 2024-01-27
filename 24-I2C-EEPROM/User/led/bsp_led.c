// bsp: board support package 板级支持包
#include "stm32f10x_conf.h"
#include "bsp_led.h"

void LED_GPIO_Config(void)
{
    RCC_APB2PeriphClockCmd(LED_B_GPIO_CLK, ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = LED_B_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_B_GPIO_PORT, &GPIO_InitStruct);
}
