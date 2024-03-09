/**
  ******************************************************************************
  * @file    bsp_spi_flash.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_SPI_FLASH_H
#define __BSP_SPI_FLASH_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>
#include "stm32f10x_conf.h"

/**
 * @defgroup W25Q64相关定义
 * @{
 */

/**
 * @brief FLASH型号宏定义
 */

// #define sFLASH_ID 0xEF3015 /*!< W25X16的ID */
// #define sFLASH_ID 0xEF4015 /*!< W25Q16的ID */
// #define sFLASH_ID 0xEF4018 /*!< W25Q128的ID */
#define sFLASH_ID 0xEF4017 /*!< W25Q64的ID */

/**
 * @brief FLASH存储空间宏定义
 */
#define SPI_FLASH_PageSize 256
#define SPI_FLASH_PerWritePageSize 256

/**
 * @brief W25Q64命令定义
 */

#define W25X_WriteEnable		      0x06 
#define W25X_WriteDisable		      0x04 
#define W25X_ReadStatusReg		    0x05 
#define W25X_WriteStatusReg		    0x01 
#define W25X_ReadData			        0x03 
#define W25X_FastReadData		      0x0B 
#define W25X_FastReadDual		      0x3B 
#define W25X_PageProgram		      0x02 
#define W25X_BlockErase			      0xD8 
#define W25X_SectorErase		      0x20 
#define W25X_ChipErase			      0xC7 
#define W25X_PowerDown			      0xB9 
#define W25X_ReleasePowerDown	    0xAB 
#define W25X_DeviceID			        0xAB 
#define W25X_ManufactDeviceID   	0x90 
#define W25X_JedecDeviceID		    0x9F

/**
 * @brief W25Q64标志
 */

#define WIP_Flag 0x01
#define Dummy_Byte 0xFF

/**
 * @} 
 */

/**
 * @defgroup SPI_FLASH_Define 
 * @{
 */

/**
 * @brief SPI的宏定义
 */

#define FLASH_SPIx SPI1 /*!< FLASH所使用的SPIx */
#define FLASH_SPI_APBxClock_FUN RCC_APB2PeriphClockCmd /*!< SPI的GPIO时钟的使能函数 */
#define FLASH_SPI_CLK RCC_APB2Periph_SPI1 /*!< SPI的时钟 */

/**
 * @brief 如果使用霸道开发板则配置为1, 指南者开发板为0
 */

#define USE_BD 1

/**
 * @brief SPI的CS引脚的宏定义
 */

#if (1 == USE_BD)
    #define FLASH_SPI_CS_APBxClock_FUN RCC_APB2PeriphClockCmd /*!< CS的时钟使能函数 */
    #define FLASH_SPI_CS_CLK RCC_APB2Periph_GPIOA /*!< CS的CLK时钟端口 */
    #define FLASH_SPI_CS_PORT GPIOA /*!< SPI的CS引脚 */
    #define FLASH_SPI_CS_PIN GPIO_Pin_4 /*!< SPI的CS引脚 */
#else
    #define FLASH_SPI_GPIO_CLK (RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC)
    #define FLASH_SPI_CS_PORT GPIOC /*!< SPI的CS引脚 */
    #define FLASH_SPI_CS_PIN GPIO_Pin_0 /*!< SPI的CS引脚 */
#endif

/**
 * @brief SPI的SCK引脚的宏定义
 */

#define FLASH_SPI_SCK_APBxClock_FUN RCC_APB2PeriphClockCmd /*!< SPI的SCK时钟的使能函数 */
#define FLASH_SPI_SCK_CLK RCC_APB2Periph_GPIOA /*!< SPI的时钟短裤 */
#define FLASH_SPI_SCK_PORT GPIOA /*!< SPI的SCK引脚 */
#define FLASH_SPI_SCK_PIN GPIO_Pin_5 /*!< SPI的SCK引脚 */

/**
 * @brief SPI的MISO引脚的宏定义
 */

#define FLASH_SPI_MISO_APBxClock_FUN RCC_APB2PeriphClockCmd /*!< SPI的MISO时钟的使能函数 */
#define FLASH_SPI_MISO_CLK RCC_APB2Periph_GPIOA /*!< SPI的MISO时钟端口 */
#define FLASH_SPI_MISO_PORT GPIOA /*!< SPI的MISO引脚 */
#define FLASH_SPI_MISO_PIN GPIO_Pin_6 /*!< SPI的MISO引脚 */

/**
 * @brief SPI的MOSI引脚的宏定义
 */

#define FLASH_SPI_MOSI_APBxClock_FUN RCC_APB2PeriphClockCmd /*!< SPI的MOSI时钟的使能函数 */
#define FLASH_SPI_MOSI_CLK RCC_APB2Periph_GPIOA /*!< SPI的MOSI时钟端口 */
#define FLASH_SPI_MOSI_PORT GPIOA /*!< SPI的MOSI引脚 */
#define FLASH_SPI_MOSI_PIN GPIO_Pin_7 /*!< SPI的MOSI引脚 */

/**
 * @brief CS引脚高低函数实现
 */
#define FLASH_SPI_CS_HIGH() GPIO_SetBits(FLASH_SPI_CS_PORT, FLASH_SPI_CS_PIN);
#define FLASH_SPI_CS_LOW() GPIO_ResetBits(FLASH_SPI_CS_PORT, FLASH_SPI_CS_PIN);

/**
 * @brief 超时等待时间
 */

#define SPIT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define SPIT_LONG_TIMEOUT         ((uint32_t)(10 * SPIT_FLAG_TIMEOUT))

/**
 * @brief DEBUG信息输出
 */
#define FLASH_DEBUG_ON 1
#define FLASH_INFO(fmt, arg...) printf("<<-FLASH-INFO->> "fmt"\n", ##arg)
#define FLASH_ERROR(fmt, arg...) printf("<<-FLASH-ERROR->> "fmt"\n", ##arg)
#define FLASH_DEBUG(fmt, arg...) do{\
                                    if(FLASH_DEBUG_ON)\
                                    printf("<<-FLASH-DEBUG->> [%d]"fmt"\n", __LINE__, ##arg);\
                                   }while(0)


/**
 * @} 
 */


/**
 * @defgroup FLASH_SPI_Functions 
 * @{
 */

void SPI_FLASH_Init(void);
uint32_t SPI_FLASH_ReadID(void);

/**
 * @} 
 */

#endif // !__BSP_SPI_FLASH_H
