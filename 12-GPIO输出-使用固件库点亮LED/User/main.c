/**
  ******************************************************************************
  * @file    main.c
  * @author  eric
  * @version V0.0.1
  * @date   29-December-2024 
  * @brief  GPIO输出实现蓝灯闪烁 
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FUCTIONS WHICH IS FOR GUIDANCE ONLY
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "bsp_led.h"

/**
 * @brief 延时函数
 * 
 * @param count: 延时时间参数(单位不确定) 
 * @retval None
 */
void Delay(uint32_t count)
{
    for( ; count != 0; count--)
    {
        uint32_t current;
        for(current = count; current != 0; current--)
        {
            ;
        }
    }
    
}

/**
 * @brief 实现蓝色LED闪烁
 * @param None
 * @retval None 
 */
int main(void)
{
    LED_GPIO_Config(); // 配置PB1为推挽输出

    while(1)
    {
        LED_B(OFF); // 蓝灯灭
        Delay(0xFFF); // 延时
        LED_B(ON); // 蓝灯亮
        Delay(0xFFF); // 延时
    }
}
