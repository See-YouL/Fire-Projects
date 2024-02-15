/**
  ******************************************************************************
  * @file    main.c
  * @author  eric
  * @version V0.0.1
  * @date    10-February-2024
  * @brief   
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FUNCTIONS WHICH IS FOR GUIDANCE ONLY
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_spi_flash.h"


/**
 * @defgroup: Global_Values
 * @{  
 */


/**
 * @} 
 * 
 */

void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

/**
 * @brief STM32与EEPROM通过I2C协议进行读写测试 
 * @param None
 * @retval None 
 */
int main(void)
{
    /* 定义测试用变量 */
    uint32_t id;
    /* LED_GPIO初始化 */
    LED_GPIO_Config();
    /* 串口初始化 */
    USART_Config();
    /* SPI Flash初始化 */
    SPI_FLASH_Init();
    /* 点亮蓝灯 */
    LED_BLUE;
    /* 串口发送字符串 */
    printf("\r\nSPI-FLASH\r\n");
    /* 读取ID */
    id = SPI_FLASH_ReadID();
    Delay(200);
    /* 串口发送字符串 */
    printf("\r\nFlash ID is 0x%X\r\n", id);

    /* 空循环 */
    while(1)
    {
        ;
    }
}
