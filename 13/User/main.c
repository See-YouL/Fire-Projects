#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_key.h"

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
    KEY_GPIO_Config();

    while(1)
    {
        if(Key_Scan(KEY1_GPIO_PORT, KEY1_GPIO_PIN) == KEY_ON)
        {
            LED_B_TOGGLE;
        }
    }
}