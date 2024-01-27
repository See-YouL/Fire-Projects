/**
  ******************************************************************************
  * @file    bsp_i2c.h
  * @author  eric
  * @version V0.0.1
  * @date    27-January-2024
  * @brief   这个文件包含了I2C函数的声明 
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FUNTIONS WHICH IS FOR GUIDANCE ONLY
  ******************************************************************************
  */

#ifndef __BSP_I2C_H
#define __BSP_I2C_H

#include "stm32f10x.h"
#include "stm32f10x_conf.h"

// I2C的引脚宏定义 @ref

/**
 * @defgroup I2C_EEPROM_Define 
 * @{
 */

/**
 * @brief I2C的宏定义
 */

#define EEPROM_I2C I2C1 /*!< EEPROM所使用的I2Cx */
#define EEPROM_I2C_CLK RCC_APB1Periph_I2C1 /*!< I2C的时钟 */
#define EEPROM_I2C_APBxClkCmd RCC_APB1PeriphClockCmd /*!< I2C时钟的使能函数 */
#define EEPROM_I2C_BAUDRATE 400000 /*!< I2C的通信速率 */
#define STM32_I2C_OWN_ADDR 0x5F /*!< STM32在I2C总线上的自身地址, 可任意配置(只要在I2C总线上唯一即可) */
#define EEPROM_I2C_WRITE_ADDRESS 0xA0 /*!< EEPROM在I2C总线上的8位写地址 */
#define EEPROM_I2C_READ_ADDRESS 0xA1 /*!< EEPROM在I2C总线上的8位读地址 */

/**
 * @brief I2C的GPIO引脚宏定义
 */

#define EEPROM_I2C_SCL_GPIO_CLK (RCC_APB2Periph_GPIOB) /*!< I2C的SCL引脚的GPIO时钟 */
#define EEPROM_I2C_SDA_GPIO_CLK (RCC_APB2Periph_GPIOB) /*!< I2C的SDA引脚的GPIO时钟 */
#define EEPROM_I2C_GPIO_APBxClkCmd RCC_APB2PeriphClockCmd /*!< I2C的GPIO时钟的使能函数 */
#define EEPROM_I2C_SCL_GPIO_PORT GPIOB /*!< I2C的SCL引脚的GPIO端口 */
#define EEPROM_I2C_SCL_GPIO_Pin GPIO_Pin_6 /*!< I2C的SCL引脚的GPIO引脚 */
#define EEPROM_I2C_SDA_GPIO_PORT GPIOB /*!< I2C的SDA引脚的GPIO端口 */
#define EEPROM_I2C_SDA_GPIO_Pin GPIO_Pin_7 /*!< I2C的SDA引脚的GPIO引脚 */

/**
 * @} 
 */

/**
 * @defgroup EEPROM_I2C_Functions 
 * @{
 */

void I2C_EEPROM_Config(void);
void EEPROM_Byte_Writting(uint8_t WordAddress, uint8_t Data);
void EEPROM_Random_Read(uint8_t WordAddress, uint8_t* Data);
void EEPROM_Sequential_Read(uint8_t WordAddress, uint8_t* Data, uint8_t NumByteToRead);

/**
 * @} 
 * 
 */

#endif // !__BSP_I2C_H
