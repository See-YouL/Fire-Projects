/**
  ******************************************************************************
  * @file    main.c
  * @author  eric
  * @version V0.0.1
  * @date    27-January-2024
  * @brief   STM32与EEPROM通过I2C协议进行读写测试
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FUNTIONS WHICH IS FOR GUIDANCE ONLY
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_i2c.h"

/*----------------------------------------------------------------------------
 * 操作流程:
 * 
 * 1. 初始化I2C相关的GPIO
 * 2. 配置I2C外设的工作模式
 * 3. 编写I2C写入EEPROM的Byte Write函数 
 * 4. 编写I2C读取EEPROM的Random Read函数
 * 5. 使用read函数和write函数进行读写校验
 * 6. 编写Page Write和Sequential Read函数进行校验
 *----------------------------------------------------------------------------*/

/**
 * @defgroup: Global_Values
 * @{  
 */

uint8_t ReadData[20] = {0};
uint8_t WriteData[3] = {3, 4, 5};

/**
 * @} 
 * 
 */

/**
 * @brief STM32与EEPROM通过I2C协议进行读写测试 
 * @param None
 * @retval None 
 */
int main(void)
{
    /* 初始化USART */
    USART_Config(); 
    /* 串口打印 */
    printf("I2C-EEPROM\n");
    /* 初始化I2C */
    I2C_EEPROM_Config();
    /* STM32向EEPROM 地址1写入数据0x01 */
    EEPROM_Byte_Writting(1, 0x01);
    /* ACKNOWLEDGE POLLING 确认询问 */
    EEPROM_ACK_Polling();
    /* STM32向EEPROM 地址2写入数据0x02 */
    EEPROM_Byte_Writting(2, 0x02);
    /* ACKNOWLEDGE POLLING 确认询问 */
    EEPROM_ACK_Polling();
    /*----------------------------------------
     * Page Writting的地址对齐
     * 为保证数据无误需addr%8 == 0
     *----------------------------------------*/ 
    /* STM32向EEPROM 地址3-5写入数据0x03-0x05 */
    EEPROM_Page_Writting(0x03, WriteData, 3);
    /* ACKNOWLEDGE POLLING 确认询问 */
    EEPROM_ACK_Polling();
    /* STM32从EEPROM以SequentialRead方式读取地址1-4的数据 */ 
    EEPROM_Sequential_Read((uint8_t)1, ReadData, 4);
    /* STM32从EEPROM以RandomRead方式读取地址5的数据 */ 
    EEPROM_Random_Read((uint8_t)5, &ReadData[4]);
    /* 将读出的数据循环打印 */
    for (uint8_t i = 0; i < 5; i++)
    {
        printf("ReadData[%d] = 0x%x\n", i, ReadData[i]);
    }
    
    /* 空循环 */
    while(1)
    {
        ;
    }
}
