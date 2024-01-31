/**
  ******************************************************************************
  * @file    bsp_i2c_gpio.h
  * @author  eric
  * @version V0.0.1
  * @date    31-January-2024
  * @brief   GPIO模拟I2C的宏定义
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FUCTIONS WHICH IS FOR GUIDANCE ONLY
  ******************************************************************************
  */
#ifndef __BSP_I2C_GPIO_H
#define __BSP_I2C_GPIO_H

#include <inttypes.h>
#include "stm32f10x_conf.h"

/**
 * @defgroup EEPROM_GPIO_Define 
 * @{
 */

/**
 * @brief R/W Bit
 */
#define EEPROM_I2C_WR 0 /*!< 写控制bit */
#define EEPROM_I2C_RD 1 /*!< 读控制bit */

/**
 * @brief GPIO端口和引脚
 */
#define EEPROM_GPIO_PORT_I2C GPIOB /*!< GPIOB端口 */
#define EEPROM_RCC_I2C_PORT RCC_APB2Periph_GPIOB /*!< GPIOB端口时钟 */
#define EEPROM_I2C_SCL_PIN GPIO_Pin_6 /*!< 连接到SCL时钟线的GPIO */
#define EEPROM_I2C_SDA_PIN GPIO_Pin_7 /*!< 连接到SDA数据线的GPIO */

/**
 * @brief 定义读写SCL和SDA的宏 
 */
#define GPIO_REG_EEPROM 1 /*!< 1为使用GPIO的库函数实现IO读写, 0为寄存器方式(在IAR最高级别优化时会被编译器错误优化)*/
#if GPIO_REG_EEPROM
    #define EEPROM_I2C_SCL_1() GPIO_SetBits(EEPROM_GPIO_PORT_I2C, EEPROM_I2C_SCL_PIN) /*!< SCL=1 */
    #define EEPROM_I2C_SCL_0() GPIO_ResetBits(EEPROM_GPIO_PORT_I2C, EEPROM_I2C_SCL_PIN) /*!< SCL=0 */
    #define EEPROM_I2C_SDA_1() GPIO_SetBits(EEPROM_GPIO_PORT_I2C, EEPROM_I2C_SDA_PIN) /*!< SDA=1 */
    #define EEPROM_I2C_SDA_0() GPIO_ResetBits(EEPROM_GPIO_PORT_I2C, EEPROM_I2C_SDA_PIN) /*!< SDA=0 */
    #define EEPROM_I2C_SDA_READ() GPIO_ReadInputDataBit(EEPROM_GPIO_PORT_I2C, EEPROM_I2C_SDA_PIN) /*!< 读SDA口的状态 */
#else
    #define EEPROM_I2C_SCL_1() EEPROM_GPIO_PORT_I2C->BSRR = EEPROM_I2C_SCL_PIN /*!< SCL = 1 */
    #define EEPROM_I2C_SCL_0() EEPROM_GPIO_PORT_I2C->BRR = EEPROM_I2C_SCL_PIN /*!< SCL = 0 */
    #define EEPROM_I2C_SDA_1() EEPROM_GPIO_PORT_I2C->BSRR = EEPROM_I2C_SDA_PIN /*!< SDA = 1 */
    #define EEPROM_I2C_SDA_0() EEPROM_GPIO_PORT_I2C->BRR = EEPROM_I2C_SDA_PIN /*!< SDA = 0 */
    #define EEPROM_I2C_SDA_READ() ((EEPROM_GPIO_PORT_I2C->IDR & EEPROM_I2C_SDA_PIN) != 0) /*!< 读SDA口的状态 */
#endif

/**
 * @} 
 */

/**
 * @defgroup I2C_GPIO_Fuctions
 * @{
 */

void I2C_Start(void);
void I2C_Stop(void);
void I2C_SendByte(uint8_t _ucByte);
uint8_t I2C_ReadByte(void);
uint8_t I2C_WaitAck(void);
void I2C_Ack(void);
void I2C_NAck(void);
uint8_t I2C_CheckDevice(uint8_t _Address);

/**
 * @} 
 */

#endif // !__BSP_I2C_GPIO_H
