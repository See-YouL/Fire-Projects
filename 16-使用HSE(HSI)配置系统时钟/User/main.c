#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_rccclkconfig.h"

// 延时函数Delay()
void Delay(uint32_t count)
{
    uint32_t i = 0;
    for(; count != 0; count--)
    {
        for(i = 0; i < 0x2AFF; i++)
        {
            ;
        }
    }
}
    
int main(void)
{
    // HSE_SetSysClk(RCC_PLLMul_9); // 72MHz
    // HSE_SetSysClk(RCC_PLLMul_16); // 128MHz
    // HSI_SetSysClk(RCC_PLLMul_12); // 4*12=48MHz
    MCO_GPIO_Config();
    RCC_MCOConfig(RCC_MCO_SYSCLK); // 配置MCO选择系统时钟
    LED_GPIO_Config();

    while(1)
    {
        LED_B(OFF);
        Delay(50); // 延时
        LED_B(ON);
        Delay(50); // 延时
    }
}
