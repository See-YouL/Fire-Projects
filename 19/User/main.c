#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_systick.h"

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
 * This function initializes the LED GPIO and enters an infinite loop. 
 * In each iteration of the loop, it turns off the blue LED, delays for 0.5 seconds,
 * turns on the blue LED, and delays for 0.5 seconds again.
 * 
 * @return int The exit status of the program.
 */
int main(void)
{
    LED_GPIO_Config(); // Initialize the LED GPIO

    while(1)
    {
        LED_B(OFF); // Turn off the blue LED
        SysTick_Delay_ms(500); // Delay for 0.5 seconds
        LED_B(ON); // Turn on the blue LED
        SysTick_Delay_us(500000); // Delay for 0.5 seconds
    }
}
