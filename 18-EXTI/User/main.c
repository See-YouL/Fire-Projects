#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_exti.h"

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
 * @brief Main function of the program.
 * 
 * This function initializes the LED GPIO and EXTI Key configurations.
 * It then enters an infinite loop, where no program execution takes place.
 */
int main(void)
{
    LED_GPIO_Config();
    EXTI_Key_Config();

    while(1)
    {
        ; // 主函数不执行程序
    }
}