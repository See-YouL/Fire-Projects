/**
  ******************************************************************************
  * @file    bsp_i2c_gpio.c
  * @author  eric
  * @version V0.0.1
  * @date    31-January-2024
  * @brief   用GPIO模拟I2C总线, 不包含应用层命令帧
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FUCTIONS WHICH IS FOR GUIDANCE ONLY
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "bsp_i2c_gpio.h"

static void I2C_CfgGpio(void);

/**
 * @brief I2C总线位延迟, 最快400kHz 
 * @param None
 * @return None
 */
static void I2C_Delay(void)
{
    uint8_t i;

    /*--------------------------------------------------------------------
     * 下面的时间是通过逻辑分析仪测试得到的
     * 工作条件: CPU主频72MHz, MDK编译环境, 1级优化
     * 循环次数为0时, SCL频率=205kHz
     * 循环次数为7时, SCL频率=347kHz, SCL高电平时间1.5us, SCL低电平时间2.87us
     * 循环次数为5时, SCL频率=421kHz, SCL高电平时间1.25us, SCL低电平时间2.375us
     *---------------------------------------------------------------------*/
    
    for (i = 0; i < 10; i++)
    {
        ;
    }
    
}

/**
 * @brief CPU发起I2C总线启动信号
 * @param None
 * @return None
 */
void I2C_Start(void)
{
    /*-----------------------------------------------------------------------
     * START信号的构成: 
     * SCL高电平时
     * SDA出现一个下降沿
     *--------------------------------------------------------------------------*/

    /* SDA高电平 */
    EEPROM_I2C_SDA_1();
    /* SCL高电平 */
    EEPROM_I2C_SCL_1();
    /* 总线延迟 */
    I2C_Delay();
    /* SDA低电平 */
    EEPROM_I2C_SDA_0();
    /* 总线延迟 */
    I2C_Delay();
    /* SCL低电平 */
    EEPROM_I2C_SCL_0();
    /* 总线延迟 */
    I2C_Delay();
}

/**
 * @brief CPU发起I2C总线停止信号
 * @param None
 * @return None
 */
void I2C_Stop(void)
{
    /*-----------------------------------------------------------------------
     * STOP信号的构成: 
     * SCL高电平时
     * SDA出现一个上升沿
     *--------------------------------------------------------------------------*/

    /* SDA 低电平 */
    EEPROM_I2C_SDA_0();
    /* SCL 高电平 */
    EEPROM_I2C_SCL_1();
    /* 总线延迟 */
    I2C_Delay();
    /* SDA 高电平 */
    EEPROM_I2C_SDA_1();
}

/**
 * @brief CPU向I2C总线设备发送8bit数据
 * @param _ucByte: 等待发送的字节数据
 * @return None
 */
void I2C_SendByte(uint8_t _ucByte)
{
    /*-----------------------------------------------------------------------
     * 数据有效性
     * SCL高电平时数据有效, SCL低电平时SDA进行电平转换 
     * SDA线上的电平即为数据
     *----------------------------------------------------------------------*/

    /* 循环发送高位 */
    for (uint8_t i = 0; i < 8; i++)
    {
        /* 将SDA置于bit7的电平 */
        if (_ucByte & 0x80) 
        {
            EEPROM_I2C_SDA_1();
        }
        else
        {
            EEPROM_I2C_SDA_0();
        }
        /* 总线延迟 */
        I2C_Delay();
        /* SCL高电平 */
        EEPROM_I2C_SCL_1();
        /* 总线延迟 */
        I2C_Delay();
        /* SCL低电平 */
        EEPROM_I2C_SCL_0();
        /* 全部bit发送完毕 */
        if (i == 7)
        {
            /* 释放总线 */
            EEPROM_I2C_SDA_1();
        }
        /* 左移一个bit位 */
        _ucByte <<= 1;
        /* 总线延迟 */
        I2C_Delay();
    }
}

/**
 * @brief CPU从I2C总线设备读取8bit数据
 * @param None
 * @return 读到的数据
 */
uint8_t I2C_ReadByte(void)
{
    /*-----------------------------------------------------------------------
     * 数据有效性
     * SCL高电平时数据有效, SCL低电平时SDA进行电平转换 
     * SDA线上的电平即为数据
     *----------------------------------------------------------------------*/

    /* value初始值0b(00000000) */
    uint8_t value = 0;
    /* 循环读入高位到value */
    for (uint8_t i = 0; i < 8; i++)
    {
        /* value 左移一个bit位 */
        value <<= 1;
        /* SCL 高电平 */
        EEPROM_I2C_SCL_1();
        /* 总线延迟 */
        I2C_Delay();
        if (EEPROM_I2C_SDA_READ()) /* 高电平时value最低位为1 */
        {
            value++;
        } 
        else /* 低电平时value最低位不操作为初始值0 */
        {
            ;
        }
        /* SCL 低电平 */
        EEPROM_I2C_SCL_0();
        /* 总线延迟 */
        I2C_Delay();
    }
    /* 返回value值 */
    return value;
}

/**
 * @brief CPU产生一个时钟并读取器件的ACK应答信号
 * @param None
 * @retval 0: 正确应答, 1: 无器件响应 
 */
uint8_t I2C_WaitAck(void)
{
    /*-----------------------------------------------------------------------
     * 响应:
     * 数据发送端控制SDA高电平, 释放SDA控制权
     * 在SCL高电平时, 数据接收端应答响应
     * 数据接收端控制SDA会发送信号(高电平表示非应答信号, 低电平表示应答信号)
     *----------------------------------------------------------------------*/

    /* re表示应答信号 */
    uint8_t re;
    /* CPU释放SDA总线 */
    EEPROM_I2C_SDA_1();
    /* 总线延迟 */
	I2C_Delay();
    /* SCL高电平 */
	EEPROM_I2C_SCL_1();
    /* 总线延迟 */
	I2C_Delay();
    /* 读取SDA口的状态 */
	if (EEPROM_I2C_SDA_READ())
	{
		re = 1;
	}
	else
	{
		re = 0;
	}
    /* SCL低电平 */
	EEPROM_I2C_SCL_0();
    /* 总线延迟 */
	I2C_Delay();
	return re;

}

/**
 * @brief CPU产生一个ACK信号 
 * @param None
 * @return None
 */
void I2C_Ack(void)
{
    /*-----------------------------------------------------------------------
     * 响应:
     * 在SCL高电平时, SDA输出低电平表示应答信号
     * 响应后CPU发送SDA高电平, 释放SDA控制权
     *----------------------------------------------------------------------*/
    /* SDA 低电平 */
    EEPROM_I2C_SDA_0();
    /* 总线延迟 */
    I2C_Delay();
    /* SCL 高电平 */
    EEPROM_I2C_SCL_1();
    /* 总线延迟 */
    I2C_Delay();
    /* SCL 低电平 */
    EEPROM_I2C_SCL_0();
    /* 总线延迟 */
    I2C_Delay();
    /* SDA 高电平 */
    EEPROM_I2C_SDA_1();
}

/**
 * @brief CPU产生一个NACK信号 
 * @param None
 * @return None
 */
void I2C_NAck(void)
{
    /*-----------------------------------------------------------------------
     * 响应:
     * 在SCL高电平时, SDA输出高电平表示非应答信号
     *----------------------------------------------------------------------*/
    /* SDA 高电平 */
    EEPROM_I2C_SDA_1();
    /* 总线延迟 */
    I2C_Delay();
    /* SCL 高电平 */
    EEPROM_I2C_SCL_1();
    /* 总线延迟 */
    I2C_Delay();
    /* SCL 低电平 */
    EEPROM_I2C_SCL_0();
    /* 总线延迟 */
    I2C_Delay();
}

/**
 * @brief 配置I2C总线的GPIO, 采用模拟IO的方式实现
 * @param None
 * @return None
 */
static void I2C_CfgGpio(void)
{
    /* 定义GPIO初始化结构体变量 */
    GPIO_InitTypeDef GPIO_InitStructure;
    /* 使能GPIO时钟 */
    RCC_APB2PeriphClockCmd(EEPROM_RCC_I2C_PORT, ENABLE);
    /* 配置GPIO引脚SCL和SDA线 */
    GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SCL_PIN | EEPROM_I2C_SDA_PIN;
    /* 配置GPIO模式为开漏输出 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    /* 配置GPIO速度为50MHz */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    /* 调用GPIO初始化函数 */
    GPIO_Init(EEPROM_GPIO_PORT_I2C, &GPIO_InitStructure);
    /* 发送停止信号, 复位I2C总线上的所有设备到待机模式 */
    I2C_Stop();
}

/**
 * @brief 检测I2C总线设备是否存在
 * @param _Address: 设备的I2C总线地址
 * @retral: 0: 检测到, 1: 未检测到
 */
uint8_t I2C_CheckDevice(uint8_t _Address)
{
    /* 返回变量设备的状态 */
    uint8_t ucACK;
    /* 初始化I2C总线的GPIO */
    I2C_CfgGpio();
    /* 发送启动信号 */
    I2C_Start();
    /* 发送设备的八位写地址 */
    I2C_SendByte(_Address | EEPROM_I2C_WR);
    /* 检测设备应答 */
    ucACK = I2C_WaitAck();
    /* 发送停止信号 */
    I2C_Stop();
    /* 返回设备状态值 */
    return ucACK;
}
