/**
  ******************************************************************************
  * @file    bsp_dma_m2m.h
  * @author  eric
  * @version None
  * @date    2024年1月26日14:47:05
  * @brief   DMA存储器到存储器模式配置头文件 
  ******************************************************************************
  */

#ifndef __BSP_DMA_M2M_H
#define __BSP_DMA_M2M_H

#include "stm32f10x.h"

// 当使用存储器到存储器模式时候，通道可以随便选，没有硬性的规定
#define M2M_DMA_CHANNEL     DMA1_Channel6
#define M2M_DMA_CLOCK       RCC_AHBPeriph_DMA1
// 传输完成标志
#define M2M_DMA_FLAG_TC     DMA1_FLAG_TC6
// 要发送的数据大小
#define BUFFER_SIZE     32

void M2M_DMA_Config(void);
uint8_t Buffercmp(const uint32_t* pBuffer, uint32_t* pBuffer1, uint16_t BufferLength);

#endif // !__BSP_DMA_M2M_H
