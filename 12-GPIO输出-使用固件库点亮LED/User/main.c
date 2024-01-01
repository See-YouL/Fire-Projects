#include "stm32f10x.h"
#include "bsp_led.h"

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

int main(void)
{
    LED_GPIO_Config();

    while(1)
    {
        GPIO_SetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN);
        Delay(0xFFF); // 延时
        GPIO_ResetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN);
        Delay(0xFFF); // 延时
    }
}