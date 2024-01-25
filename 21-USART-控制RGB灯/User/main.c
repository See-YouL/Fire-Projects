#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_usart.h"

int main(void)
{
    uint8_t ch = 0;

    USART_Config(); // 初始化USART
    LED_GPIO_Config(); // 初始化LED

    printf("USART-RGB\n");
    printf("1:RED, 2:GREEN, 3:BLUE, 4:YELLOW, 5:PURPLE, 6:CYAN, 7:WHITE\n");
    printf("Others: BLACK\n");
    

    while(1)
    {
        ch = getchar();
        printf("ch = %c\n", ch);

        switch(ch)
        {
        case '1': LED_RED;
            break;
        case '2': LED_GREEN;
            break;
        case '3': LED_BLUE;
            break;
        case '4': LED_YELLOW;
            break;
        case '5': LED_PURPLE;
            break;
        case '6': LED_CYAN;
            break;
        case '7': LED_WHITE;
            break;
        
        default: LED_RGBOFF;
            break;
        }
    }
}
