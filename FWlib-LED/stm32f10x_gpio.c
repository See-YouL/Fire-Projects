#include "stm32f10x_gpio.h"

// 端口置位函数
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t Pin)
{
    GPIOx->BSRR |= Pin;
    /*----------------------------------------------------------------
    BSRR寄存器:
    低16位写1置1，写0不改变
    高16位写1置0，写0不改变
    *----------------------------------------------------------------*/
}

// 端口复位函数
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t Pin)
{
    GPIOx->BRR |= Pin;
    /*----------------------------------------------------------------
    BRR寄存器:
    低16位写1置0，写0不改变
    高16位保留
    ----------------------------------------------------------------*/
}