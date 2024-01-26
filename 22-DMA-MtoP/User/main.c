/**
  ******************************************************************************
  * @file    main.c
  * @author  eric
  * @version None
  * @date    26-January-2024
  * @brief   SRAM to 串口, 同时LED灯闪烁, 演示DMA数据不需占用CPU 
  ******************************************************************************
  */

#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_dma_m2p.h"

extern uint8_t SendBuff[SENDBUFF_SIZE];

/**
 * @brief Delays the execution for a specified number of milliseconds.(Not Sure)
 * @param ms The number of milliseconds to delay.
 * @return None.
 */
void Delay_ms(uint32_t ms)
{
    uint32_t i = 0;
    for(i = 0; i < ms; i++)
    {
        uint16_t j = 0;
        for(j = 0; j < 1000; j++)
        {
            ;
        }
    }
}

/**
 * @brief 实现DMA将储存器中的数据发送到USART->DR, 并实现LED1闪烁
 * 
 * @return int 
 */
int main(void)
{

    LED_GPIO_Config(); // 初始化LED
    USART_Config(); // 串口初始化

    for(uint16_t i = 0; i < SENDBUFF_SIZE; i++)
    {
        SendBuff[i] = 'P';
    }

    USARTx_DMA_Config(); // 初始化DMA
    USART_DMACmd(DEBUG_USARTx, USART_DMAReq_Tx, ENABLE); // 使能DMA发送

    while(1)
    {
        LED1_TOGGLE;
        Delay_ms(10000);
    }
}
