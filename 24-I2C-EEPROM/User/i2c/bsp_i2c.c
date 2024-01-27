/** ******************************************************************************
  * @file    bsp_i2c.c
  * @author  eric
  * @version V0.0.1
  * @date    27-January-2024
  * @brief   这个文件提供了I2C的函数 
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FUNTIONS WHICH IS FOR GUIDANCE ONLY
  ******************************************************************************
  */

#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "bsp_i2c.h"

/**
 * @brief I2C EEPROM配置函数 
 * @param None
 * @retval None 
 */
void I2C_EEPROM_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    I2C_InitTypeDef I2C_InitStructure;

    /*-------------------------- 时钟配置 ------------------------------*/
    /* 使能I2C GPIO的时钟 */
    EEPROM_I2C_GPIO_APBxClkCmd(EEPROM_I2C_SCL_GPIO_CLK | EEPROM_I2C_SDA_GPIO_CLK, ENABLE);
    /* 使能I2C的时钟 */
    EEPROM_I2C_APBxClkCmd(EEPROM_I2C_CLK, ENABLE);

    /*-------------------------- I2C_SCL的GPIO配置 ------------------------------*/
    /* 配置引脚为I2C的SCL */
    GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SCL_GPIO_Pin;
    /* 配置输出速率为50MHz */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    /* 配置模式开漏复用输出 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    /* 初始化I2C_SCL的GPIO配置 */ 
    GPIO_Init(EEPROM_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);

    /*-------------------------- I2C_SDA的GPIO配置 ------------------------------*/
    /* 配置引脚为I2C的SDA */
    GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SDA_GPIO_Pin;
    /* 配置输出速率为50MHz */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    /* 配置模式开漏复用输出 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    /* 初始化I2C_SDA的GPIO配置 */ 
    GPIO_Init(EEPROM_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);

    /*-------------------------- I2C的工作模式配置 ------------------------------*/
    /* 使能响应 */
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    /* 使用7位地址 */
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    /* 时钟频率 400kHz*/
    I2C_InitStructure.I2C_ClockSpeed = EEPROM_I2C_BAUDRATE;
    /* 占空比 Tlow/Thigh = 2 */
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    /* 模式 I2C */
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_OwnAddress1 = STM32_I2C_OWN_ADDR;
    /* 初始化I2C */
    I2C_Init(EEPROM_I2C, &I2C_InitStructure); 
    /* 使能I2C */
    I2C_Cmd(EEPROM_I2C, ENABLE);
}

/**
 * @brief 函数实现了STM32作为主发送器向EEPROM以Byte Writting的方式写数据 
 * @param WordAddress: 需要写入的字节所在的地址
 * @param Data: 真正要写入的内容
 * @retval None
 */
void EEPROM_Byte_Writting(uint8_t WordAddress, uint8_t Data)
{
/*---------------- STM32发送WordAddress ----------------*/
    /* STM32产生START信号 */
    I2C_GenerateSTART(EEPROM_I2C, ENABLE);
    /* 等待EV5事件完成(未设置检测时间超时, 不严谨) */
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) == ERROR)
    {
        ;
    }
    /* STM32发送EEPROM的写地址 */
    I2C_Send7bitAddress(EEPROM_I2C, EEPROM_I2C_WRITE_ADDRESS, I2C_Direction_Transmitter);
    /* 等待EV6事件(发送)完成(未设置检测时间超时, 不严谨) */
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == ERROR)
    {
       ;
    }
    /* 不检测EV8事件(I2C_SRx:TxE[7] = 1, 数据寄存器空很正常, 不进行检测) */
    /* STM32向EEPROM发送WordAddress */
    I2C_SendData(EEPROM_I2C, WordAddress);
    /* 等待EV8事件完成(未设置检测时间超时, 不严谨) */
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTING) == ERROR)
    {
        ;
    }
/*---------------- STM32发送Data ----------------*/
    /* STM32向EEPROM发送Data */
    I2C_SendData(EEPROM_I2C, Data);
    /* 等待EV8_2事件完成(未设置检测时间超时, 不严谨) */
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED) == ERROR)
    {
       ;
    }
    /* STM32产生STOP信号 */
    I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
}

/**
 * @brief 函数实现STM32从EEPROM以Random Read方式读取数据
 * @param WordAddress: 要读取数据的地址
 * @param Data: 要读取的数据
 * @retval None
 */
void EEPROM_Random_Read(uint8_t WordAddress, uint8_t* Data)
{
/*---------------- STM32发送WordAddress ----------------*/
    /* STM32产生START信号 */
    I2C_GenerateSTART(EEPROM_I2C, ENABLE);
    /* 等待EV5事件完成(未设置检测时间超时, 不严谨) */
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) == ERROR)
    {
       ;
    }
    /* STM32发送EEPROM的写地址 */
    I2C_Send7bitAddress(EEPROM_I2C, EEPROM_I2C_WRITE_ADDRESS, I2C_Direction_Transmitter);
    /* 等待EV6事件(发送)完成(未设置检测时间超时, 不严谨) */
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == ERROR)
    {
       ;
    }
    /* 不检测EV8事件(I2C_SRx:TxE[7] = 1, 数据寄存器空很正常, 不进行检测) */
    /* STM32向EEPROM发送WordAddress */
    I2C_SendData(EEPROM_I2C, WordAddress);
    /* 等待EV8事件完成(未设置检测时间超时, 不严谨) */
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTING) == ERROR)
    {
       ;
    }
/*---------------- STM32接收Data ----------------*/
    /* STM32另外产生一个START信号 */
    I2C_GenerateSTART(EEPROM_I2C, ENABLE);
    /* 等待EV5事件完成(未设置检测时间超时, 不严谨) */
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) == ERROR)
    {
       ;
    }
    /* STM32发送EEPROM的读地址 */
    I2C_Send7bitAddress(EEPROM_I2C, EEPROM_I2C_READ_ADDRESS, I2C_Direction_Receiver);
    /* 等待EV6事件(接收)完成(未设置检测时间超时, 不严谨) */
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) == ERROR)
    {
       ;
    }

    /*------------------------------------------------------------------------
    * 注意: 
    * 该部分为STM32接收来自EEPROM的数据
    * 接收数据部分, 硬件会自动进行接收, 软件编程时无需操作
    * I2C_ReceiveData函数只是返回I2Cx上最近接收到的数据
    * 而不是进行数据接收
    *------------------------------------------------------------------------*/

    /* 监测到EV7事件发生, 说明接收到了新数据 */
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_RECEIVED ) == ERROR)
    {
       ;
    }
    /* 将接收到的数据赋值给Data变量 */
    *Data = I2C_ReceiveData(EEPROM_I2C);
    /* STM32产生NO ACK响应 */
    I2C_AcknowledgeConfig(EEPROM_I2C, DISABLE);
    /* STM32产生STOP信号 */
    I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
}

/**
 * @brief 函数实现STM32从EEPROM以Sequential Read方式读取数据
 * @param WordAddress: 要读取数据的地址
 * @param Data: 要读取的数据
 * @param NumByteToRead: 要读取数据的个数
 * @retval None
 */
void EEPROM_Sequential_Read(uint8_t WordAddress, uint8_t* Data, uint8_t NumByteToRead)
{
/*---------------- STM32发送WordAddress ----------------*/
    /* STM32产生START信号 */
    I2C_GenerateSTART(EEPROM_I2C, ENABLE);
    /* 等待EV5事件完成(未设置检测时间超时, 不严谨) */
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) == ERROR)
    {
       ;
    }
    /* STM32发送EEPROM的写地址 */
    I2C_Send7bitAddress(EEPROM_I2C, EEPROM_I2C_WRITE_ADDRESS, I2C_Direction_Transmitter);
    /* 等待EV6事件(发送)完成(未设置检测时间超时, 不严谨) */
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == ERROR)
    {
      ;
    }
    /* 不检测EV8事件(I2C_SRx:TxE[7] = 1, 数据寄存器空很正常, 不进行检测) */
    /* STM32向EEPROM发送WordAddress */
    I2C_SendData(EEPROM_I2C, WordAddress);
    /* 等待EV8事件完成(未设置检测时间超时, 不严谨) */
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTING) == ERROR)
    {
        ;
    }
  /*---------------- STM32接收Data ----------------*/
    /* STM32另外产生一个START信号 */
    I2C_GenerateSTART(EEPROM_I2C, ENABLE);
    /* 等待EV5事件完成(未设置检测时间超时, 不严谨) */
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) == ERROR)
    {
       ;
    }
    /* STM32发送EEPROM的读地址 */
    I2C_Send7bitAddress(EEPROM_I2C, EEPROM_I2C_READ_ADDRESS, I2C_Direction_Receiver);
    /* 等待EV6事件(接收)完成(未设置检测时间超时, 不严谨) */
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) == ERROR)
    {
       ;
    }
    /*------------------------------------------------------------------------
    * 注意: 
    * 该部分为STM32接收来自EEPROM的数据
    * 接收数据部分, 硬件会自动进行接收, 软件编程时无需操作
    * I2C_ReceiveData函数只是返回I2Cx上最近接收到的数据
    * 而不是进行数据接收
    *------------------------------------------------------------------------*/
    while(NumByteToRead)
    {
        if (NumByteToRead == 1) /* 如果为最后一个字节, 产生NO ACK响应 */
        {
            /* STM32产生NO ACK响应 */
            I2C_AcknowledgeConfig(EEPROM_I2C, DISABLE);
        }
        /* 监测到EV7事件发生, 说明接收到了新数据 */
        while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_RECEIVED ) == ERROR)
        {
            
        }
        /* 将接收到的数据赋值给Data变量 */
        *Data = I2C_ReceiveData(EEPROM_I2C);
        /* Data 指针自增 */
        Data++;
        /* NumByteToRead递减 */
        NumByteToRead--;
    }
    /* STM32产生STOP信号 */
    I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
    /* STM32使能ACK信号, 恢复到默认状态 */
    I2C_AcknowledgeConfig(EEPROM_I2C, ENABLE);
}

/**
 * @brief 等待EEPROM向内部写完数据并和EEPROM进行一次握手, 
 *   使得下一次其他设备与EEPROM通信处于正常状态
 * @param None
 * @retval None
 */
void EEPROM_WaitForWriteEnd(void)
{
    do
    {
        /* STM32产生START信号 */
        I2C_GenerateSTART(EEPROM_I2C, ENABLE);
    } while (I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) == ERROR);
    
    
    
}