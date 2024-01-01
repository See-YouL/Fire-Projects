#include "bsp_key.h"

void KEY_GPIO_Config(void)
{
    RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK, ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = KEY1_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStruct);
}

// 端口扫面函数 检测按下返回1，否则返回0
uint8_t Key_Scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    if(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON)
    {
        while(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON)
        {
            ;
        }

        return KEY_ON;
    }
    else
    {
        return KEY_OFF;
    }
    
}
