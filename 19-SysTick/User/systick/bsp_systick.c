#include "bsp_systick.h"

/**
 * @brief 延时指定的微秒数
 * @param us 延时的微秒数
 * @retval None
 */
void SysTick_Delay_us(uint32_t us)
{
    SysTick_Config(SystemCoreClock / 1000000); // reload 设置为 72, t = 1us
    
    for(int i = 0; i < us; i++)
    {
        while(!(SysTick->CTRL & (1 << 16)))
        {
            ; // 等待CTRL的Bit16置1
        }
    }

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // 状态位清除
}

/**
 * @brief 延时指定的毫秒数
 * @param ms 延时的毫秒数
 * @return 无
 */
void SysTick_Delay_ms(uint32_t ms)
{
    SysTick_Config(SystemCoreClock / 1000); // reload 设置为 72000, t = 1ms
    
    for(int i = 0; i < ms; i++)
    {
        while(!(SysTick->CTRL & (1 << 16)))
        {
            ; // 等待CTRL的Bit16置1
        }
    }

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // 状态位清除
}