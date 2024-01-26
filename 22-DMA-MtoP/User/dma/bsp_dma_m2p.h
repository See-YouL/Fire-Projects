/**
  ******************************************************************************
  * @file    bsp_dma_m2p.h
  * @author  eric
  * @version None
  * @date    26-January-2024
  * @brief   DMA存储器到外设配置头文件 
  ******************************************************************************
  */

#ifndef __BSP_DMA_M2P_H
#define __BSP_DMA_M2P_H

#include "stm32f10x.h"
#include <stdio.h>

// 串口工作参数宏定义
#define  DEBUG_USARTx                   USART1
#define  DEBUG_USART_CLK                RCC_APB2Periph_USART1
#define  DEBUG_USART_APBxClkCmd         RCC_APB2PeriphClockCmd
#define  DEBUG_USART_BAUDRATE           115200

// USART GPIO 引脚宏定义
#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
#define  DEBUG_USART_TX_GPIO_PORT       GPIOA   
#define  DEBUG_USART_TX_GPIO_PIN        GPIO_Pin_9
#define  DEBUG_USART_RX_GPIO_PORT       GPIOA
#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_10

#define USART_TX_DMA_CLK RCC_AHBPeriph_DMA1 // 串口DMA时钟
#define  USART_TX_DMA_CHANNEL     DMA1_Channel4 // 串口对应的DMA请求通道
#define  USART_DR_ADDRESS        (USART1_BASE+0x04) // 外设寄存器地址
#define  SENDBUFF_SIZE            5000 // 一次发送的数据量
#define  USART_TX_DMA_FLAG_TC DMA1_FLAG_TC4 // 标志位

void USART_Config(void);
void USARTx_DMA_Config(void);

#endif // !__BSP_DMA_M2P_H
