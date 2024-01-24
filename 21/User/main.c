#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_usart.h"

int main(void)
{
    USART_Config(); // 初始化USART

    // 发送1字节数据
    Usart_SendByte(DEBUG_USARTx, 'a');
    Usart_SendByte(DEBUG_USARTx, '\n');

    // 发送2字节数据
    Usart_SendHalfWord(DEBUG_USARTx, 0xFF56);

    // 发送数组
    Usart_SendArray(DEBUG_USARTx, (uint8_t*)"Hello World!", 11);
    uint8_t array[11] = {"Hello World!"};
    Usart_SendArray(DEBUG_USARTx, array, 11);

    // 发送字符串
    Usart_SendString(DEBUG_USARTx, "\nString: Hello World\n");

    // 重定向printf函数
    printf("printf: Hello World\n");

    // 重定向putchar函数
    putchar('p');
    putchar('u');
    putchar('t');
    putchar('c');
    putchar('h');
    putchar('a');
    putchar('r');
    putchar('\n');
    
    while(1)
    {
        ;
    }
}
