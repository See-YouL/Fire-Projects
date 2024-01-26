/**
  ******************************************************************************
  * @file    main.c
  * @author  eric
  * @version None
  * @date    2024年1月26日14:47:55
  * @brief   DMA实验1(存储器到存储器)的主函数
  ******************************************************************************
  */

#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_dma_m2m.h"

// 声明以下变量来自外部文件
extern const uint32_t aSRC_Const_Buffer[BUFFER_SIZE];
extern uint32_t aDST_Buffer[BUFFER_SIZE];

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

int main(void)
{
    uint8_t status = 0; // 接收比较的结构

    LED_GPIO_Config(); // 初始化LED
    M2M_DMA_Config(); // 初始化DMA
     
    // 等待DMA1传送完毕
    while(DMA_GetFlagStatus(M2M_DMA_FLAG_TC) == RESET)
    {
        ;
    }

    LED_YELLOW;
    Delay_ms(10000); // DMA初始化完成后亮黄灯

    status = Buffercmp(aSRC_Const_Buffer, aDST_Buffer, BUFFER_SIZE); // 比较两个数组的数据是否相等
    if(status == 0)
    {
        LED_RED; // 数据不相等亮红灯
    }
    else
    {
        LED_GREEN; // 数据相等亮绿灯
    }

    while(1)
    {
        ;
    }
}
