/** ****************************************************************************
  * @file    bsp_spi_flash.c
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

#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "bsp_spi_flash.h"

/**
 * @brief 超时函数
 */
static __IO uint32_t SPITimeout = SPI_LONG_TIMEOUT;
static uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode);

/**
 * @brief SPI_FLASH初始化
 * @param None
 * @return None
 */
void SPI_FLASH_Init(void)
{
    /* 定义GPIO初始化结构体 */
    GPIO_InitTypeDef GPIO_InitStructure;
    /* 定义SPI初始化结构体 */
    SPI_InitTypeDef SPI_InitStructure;
/*----------------------------SPI时钟及引脚配置---------------------------------*/
    /* 使能SPI时钟 */
    FLASH_SPI_APBxClock_FUN(FLASH_SPI_CLK, ENABLE);
    /* 使能SPI引脚相关的时钟 */
    FLASH_SPI_CS_APBxClock_FUN(FLASH_SPI_CS_CLK|FLASH_SPI_SCK_CLK, ENABLE);
    /* SPI的CS引脚软件配置 */
    GPIO_InitStructure.GPIO_Pin = FLASH_SPI_CS_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(FLASH_SPI_CS_PORT, &GPIO_InitStructure);
    /* SCK 配置 */
    GPIO_InitStructure.GPIO_Pin = FLASH_SPI_SCK_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(FLASH_SPI_SCK_PORT, &GPIO_InitStructure);
    /* MISO 配置 */
    GPIO_InitStructure.GPIO_Pin = FLASH_SPI_MISO_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(FLASH_SPI_MISO_PORT, &GPIO_InitStructure);
    /* MOSI 配置 */
    GPIO_InitStructure.GPIO_Pin = FLASH_SPI_MOSI_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(FLASH_SPI_MOSI_PORT, &GPIO_InitStructure);
    /* 停止信号, CS引脚配置为高电平 */
    FLASH_SPI_CS_HIGH();
/*-------------------------------SPI模式配置-----------------------------------*/
    /* 配置方向为双向全双工 */
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    /* 配置为主机模式 */
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    /* 数据位配置为8位 */
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    /* 配置CPOL高电平采样 */
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    /* 配置CPHA偶数边缘采样 */
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    /* 配置为软件CS */
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    /* 四分频 */
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
    /* 配置为MSB先行 */
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    /* CRC校验 */
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    /* 初始化SPI */
    SPI_Init(FLASH_SPIx, &SPI_InitStructure);
    /* 使能SPI */
    SPI_Cmd(FLASH_SPIx, ENABLE);
}

/**
 * @brief 擦除FLASH扇区 
 * @param SectorAddr: 要擦除的扇区地址
 * @return None
 */
void SPI_FLASH_SectorErase(u32 SectorAddr)
{
    /* 发送FLASH写使能命令 */
    SPI_FLASH_WriteEnable();
    SPI_FLASH_WaitForWriteEnd();
    /* 选择FLASH: CS低 */
    SPI_FLASH_CS_LOW();
    /* 发送扇区擦除命令 */
    SPI_FLASH_SendByte(W25X_SectorErase);
    /* 发送扇区地址的高位 */
    SPI_FLASH_SendByte((SectorAddr & 0xFF0000) >> 16);
    /* 发送扇区地址的中位 */
    SPI_FLASH_SendByte((SectorAddr & 0xFF00) >> 8);
    /* 发送扇区地址的低位 */
    SPI_FLASH_SendByte(SectorAddr & 0xFF);
    /* 通讯结束, CS高 */
    SPI_FLASH_CS_HIGH();
    /* 等待擦除完毕 */
    SPI_FLASH_WaitForWriteEnd();
}

/**
 * @brief 擦除FLASH扇区, 整片擦除
 * @param None
 * @return None
 */
void SPI_FLASH_BulkErase(void)
{
    /* 发送FLASH写使能命令 */
    SPI_FLASH_WriteEnable();
    /* 选择FLASH: CS低 */
    SPI_FLASH_CS_LOW();
    /* 发送整块擦除指令 */
    SPI_FLASH_SendByte(W25X_ChipErase);
    /* 停止信号FLASH: CS高 */
    SPI_FLASH_CS_HIGH();
    /* 等待擦除完毕 */
    SPI_FLASH_WaitForWriteEnd();
}

/**
 * @brief 向FLASH发送写使能命令
 * @param None
 * @return None
 */
void SPI_FLASH_WriteEnable(void)
{
    /* 通讯开始, CS低 */
    SPI_FLASH_CS_LOW();
    /* 发送写使能命令 */
    SPI_FLASH_SendByte(W25X_WriteEnable);
    /* 通讯结束, CS高 */
    SPI_FLASH_CS_HIGH();
}

/**
 * @brief 等待WIP(BUSY)标志被置0, 即等待到FLASH内部数据写入完毕
 * @param None
 * @return None
 */
void SPI_FLASH_WaitForWriteEnd(void)
{
    u8 FLASH_Status = 0;

    /* 选择FLASH: CS低 */
    SPI_FLASH_CS_LOW();
    /* 发送读状态寄存器命令 */
    SPI_FLASH_SendByte(W25X_ReadStatusReg);
}

/**
 * @brief 擦除FLASH扇区
 * @param SectorAddr: 要擦除的扇区地址
 * @return None
 */
void SPI_FLASH_SectorErase(u32 SectorAddr)
{
    /* 发送FLASH写使能命令 */
    SPI_FLASH_WriteEnable();


}

/**
 * @brief 发送一个字节
 * @param byte: 要发送的数据
 * @retval 返回接收的数据 
 */
uint8_t SPI_FLASH_SendByte(uint8_t byte)
{
    SPITimeout = SPI_FLAG_TIMEOUT;

    /* 等待发送缓冲区为空 */
    while(RESET == SPI_I2S_GetFlagStatus(FLASH_SPIx, SPI_I2S_FLAG_TXE))
    {
        if (0 == (SPITimeout--))
        {
            return SPI_TIMEOUT_UserCallback(0);
        }
    }
    /* 写入数据到SPI_DR, DR寄存器硬件自动发送 */
    SPI_I2S_SendData(FLASH_SPIx, byte);
    /* 重新赋值 */
    SPITimeout = SPI_FLAG_TIMEOUT;
    /* 接受数据缓冲区为空时, 发送缓冲区也为空 */
    while(RESET == SPI_I2S_GetFlagStatus(FLASH_SPIx, SPI_I2S_FLAG_RXNE))
    {
        if (0 == (SPITimeout--))
        {
            return SPI_TIMEOUT_UserCallback(1);
        }
    }

    /* 读取数据寄存器, 获取接收缓冲区数据 */
    return SPI_I2S_ReceiveData(FLASH_SPIx);
}

/**
 * @brief 返回一个字节
 * @param None
 * @retval 返回接收的数据 
 */
uint8_t SPI_FLASH_ReadByte(void)
{
    return (SPI_FLASH_SendByte(Dummy_Byte));
}

/**
 * @brief 读取Flash的ID号 
 * @param None
 * @retval 返回Flash的ID号  
 */
uint32_t SPI_FLASH_ReadID(void)
{
    /* 定义存储Flash ID的变量 */
    uint32_t flash_id = 0;
    uint32_t tmp0 = 0, tmp1 = 0, tmp2 = 0;

    /* 片选使能, 开始通讯 */
    FLASH_SPI_CS_LOW();
    /* 发送读取ID命令 */
    SPI_FLASH_SendByte(W25X_JedecDevice_ID);
    /* 接收Manufacturer */
    tmp0 = SPI_FLASH_SendByte(Dummy_Byte);
    /* 接收Memory Type */
    tmp1 =  SPI_FLASH_SendByte(Dummy_Byte);
    /* 接收Capacity */
    tmp2 =  SPI_FLASH_SendByte(Dummy_Byte);
    /* 关闭片选 */
    FLASH_SPI_CS_HIGH();
    /* 汇总到flash_id中 */
    flash_id = (tmp0 << 16) | (tmp1 << 8) | tmp2;
    /* 返回ID */
    return flash_id;
}

/**
 * @brief 超时函数
 * @param errorCode: 错误代码, 用来定位是哪个环节出错
 * @retval 返回0, 表示SPI读取失败 
 */
static uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode)
{
    FLASH_ERROR("SPI Timeout, errorCode = %d\r\n", errorCode);
    return 0;
}