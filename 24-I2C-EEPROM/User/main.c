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

uint8_t ReadData[10] = {0};

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
    /* STM32向EEPROM写入1字节数据 */
    EEPROM_Byte_Writting(11, 0x55);
    /*-----------------------------------------------------------------------
     * 注意: 
     * STM32向EEPROM写入数据后
     * EEPROM需要时间向内部存储期间进行写入
     * 此时EEPROM不应答
     * 所以在发送下一次I2C请求之前
     * 应等待EEPROM写入完成
     *-----------------------------------------------------------------------*/
    /* STM32从EEPROM读取1字节数据 */ 
    EEPROM_Sequential_Read(11, ReadData, 1);
    /* 将读出的数据打印出来 */
    printf("ReadData = 0x%x\n", ReadData[0]);
    /* 空循环 */
    while(1)
    {
        ;
    }
}
