/**
  ******************************************************************************
  * @file    bsp_i2c_ee.h
  * @author  eric
  * @version V0.0.1
  * @date    31-January-2024
  * @brief   I2C EEPROM(AT24C02) 应用函数的宏定义
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FUCTIONS WHICH IS FOR GUIDANCE ONLY
  ******************************************************************************
  */

#ifndef __BSP_I2C_EE_H
#define __BSP_I2C_EE_H

#include "stm32f10x.h"
#include "stm32f10x_conf.h"

/**
 * @defgroup EEPROM_Define 
 * @{
 */

#define EEPROM_DEV_ADDRESS 0xA0 /*!< AT24C02设备写地址, 读地址为0xA1 */
#define EEPROM_PAGE_SIZE 8 /*!< AT24C02的页大小 */
#define EEPROM_DEV_SIZE 256 /*! AT24C02的总容量大小 */
/**
 * @} 
 */


/**
 * @defgroup EEPROM_Soft_Functions 
 * @{
 */

uint8_t ee_CheckOk(void);
uint8_t ee_ReadBytes(uint8_t *_pReadBuf, uint16_t _usAddress, uint16_t _usSize);
uint8_t ee_WriteBytes(uint8_t *_pWriteBuf, uint16_t _usAddress, uint16_t _usSize);
void ee_Erase(void);
uint8_t ee_Test(void);

/**
 * @brief 
 * @}
 */

#endif // !__BSP_I2C_EE_H
