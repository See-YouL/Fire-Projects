/**
  ******************************************************************************
  * @file    bsp_dma_m2m.c
  * @author  eric
  * @version None
  * @date    2024年1月26日14:43:41
  * @brief   DMA存储器到存储器模式配置 
  ******************************************************************************
  */

#include "bsp_dma_m2m.h"


/* 定义aSRC_Const_Buffer数组作为DMA传输数据源
 * const关键字将aSRC_Const_Buffer数组变量定义为常量类型
 * 表示数据存储在内部的FLASH中
 */
const uint32_t aSRC_Const_Buffer[BUFFER_SIZE]= {
                                    0x01020304,0x05060708,0x090A0B0C,0x0D0E0F10,
                                    0x11121314,0x15161718,0x191A1B1C,0x1D1E1F20,
                                    0x21222324,0x25262728,0x292A2B2C,0x2D2E2F30,
                                    0x31323334,0x35363738,0x393A3B3C,0x3D3E3F40,
                                    0x41424344,0x45464748,0x494A4B4C,0x4D4E4F50,
                                    0x51525354,0x55565758,0x595A5B5C,0x5D5E5F60,
                                    0x61626364,0x65666768,0x696A6B6C,0x6D6E6F70,
                                    0x71727374,0x75767778,0x797A7B7C,0x7D7E7F80};

/**
 * 定义DMA传输目标存储器
 * 存储在内部的SRAM中																		
 */
uint32_t aDST_Buffer[BUFFER_SIZE];

/**
 * @brief 配置存储器到存储器的DMA传输
 * 
 * @param None
 * @return None
 */
void M2M_DMA_Config(void)
{
    DMA_InitTypeDef DMA_InitStructure; // 定义DMA初始化结构体变量
    
    RCC_AHBPeriphClockCmd(M2M_DMA_CLOCK, ENABLE); // 打开DMA时钟

    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)aSRC_Const_Buffer; // 配置外设地址, 实际将FLASH的数据配置成了外设
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)aDST_Buffer; // 配置存储器地址
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; // 配置传输方向，从外设读取数据发送到存储器
    DMA_InitStructure.DMA_BufferSize = BUFFER_SIZE; // 配置传输数据大小
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable; // 配置外设地址自增
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; // 配置存储器地址自增
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word; // 配置外设数据大小
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word; // 配置存储器数据大小
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; // 配置传输模式，非循环模式
    DMA_InitStructure.DMA_Priority = DMA_Priority_High; // 配置传输通道优先级
    DMA_InitStructure.DMA_M2M = DMA_M2M_Enable; // 配置存储器到存储器模式

    DMA_Init(M2M_DMA_CHANNEL, &DMA_InitStructure); // 初始化DMA通道
    DMA_ClearFlag(M2M_DMA_FLAG_TC); // 清除DMA通道传输完成标志位
    DMA_Cmd(M2M_DMA_CHANNEL, ENABLE); // 使能DMA通道
}

/**
 * @brief 比较两个缓冲区的数据是否相等
 * 
 * @param pBuffer 指向第一个缓冲区的指针
 * @param pBuffer1 指向第二个缓冲区的指针
 * @param BufferLength 缓冲区的长度
 * @return uint8_t 如果两个缓冲区的数据相等，则返回1；否则返回0
 */
uint8_t Buffercmp(const uint32_t* pBuffer, uint32_t* pBuffer1, uint16_t BufferLength)
{
    /* 数据长度递减 */
    while(BufferLength--)
    {
        /* 判断两个数据源是否对应相等 */
        if(*pBuffer != *pBuffer1)
        {
            /* 对应数据源不相等马上退出函数，并返回0 */
            return 0;
        }
        /* 递增两个数据源的地址指针 */
        pBuffer++;
        pBuffer1++;
    }
    /* 完成判断并且对应数据相对 */
    return 1;  
}
