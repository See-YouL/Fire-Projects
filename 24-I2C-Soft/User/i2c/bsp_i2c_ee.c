/**
  ******************************************************************************
  * @file    bsp_i2c_ee.c
  * @author  eric
  * @version V0.0.1
  * @date    31-January-2024
  * @brief   I2C EEPROM(AT24C02) 应用函数
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FUCTIONS WHICH IS FOR GUIDANCE ONLY
  ******************************************************************************
  */

#include "stm32f10x_conf.h"
#include "bsp_i2c_ee.h"
#include "bsp_usart.h"
#include "bsp_i2c_gpio.h"

/**
 * @brief 判断EEPROM是否正常 
 * @param None
 * @return 1表示正常, 0表示不正常
 */
uint8_t ee_CheckOk(void)
{
    if (I2C_CheckDevice(EEPROM_DEV_ADDRESS) == 0) /* 检测设备是否存在 */
    {
        /* 发送状态值 */
        return 1;
    }
    else
    {
        /* 发送停止信号 */
        I2C_Stop();
        /* 发送状态值 */
        return 0;
    }
}

/**
 * @brief 从指定地址采用Random Read方式读取若干数据 
 * @param _pReadBuf: 存放读到的数据的缓冲区指针
 * @param _usAddress: 起始地址
 * @param _usSize: 数据长度, 单位为字节
 * @retval 0: 失败, 1: 成功 
 */
uint8_t ee_ReadBytes(uint8_t *_pReadBuf, uint16_t _usAddress, uint16_t _usSize)
{
    /* 计数变量 */
    uint16_t i = 0;
    /* 发送启动信号 */
    I2C_Start();
    /* 发送设备写地址 */
    I2C_SendByte(EEPROM_DEV_ADDRESS | EEPROM_I2C_WR); 
    /* 等待ACK */
    if (I2C_WaitAck() != 0) /* 器件无应答 */
    {
        goto cmd_fail;
    }
    /* 发送字节地址 */
    I2C_SendByte((uint8_t)_usAddress);
    /* 等待ACK */
    if (I2C_WaitAck()!= 0) /* 器件无应答 */
    {
        goto cmd_fail;
    }
    /* 重新启动I2C总线 */
    I2C_Start();
    /* 发送设备读地址 */
    I2C_SendByte(EEPROM_DEV_ADDRESS | EEPROM_I2C_RD); 
    if (I2C_WaitAck()!= 0) /* 器件无应答 */
    {
        goto cmd_fail;
    }
    /* 循环读取数据 */
    for (i = 0; i < _usSize; i++)
    {
        /* 读取一个位 */
        _pReadBuf[i] = I2C_ReadByte();
        if (i != _usSize - 1)
        {
            /* 中间字节读完后, CPU产生ACK信号 */
            I2C_Ack();
        }
        else
        {
            /* 最后一个字节读完后, CPU产生NAck信号 */
            I2C_NAck();
        }
    }
    /* 发送I2C总线停止信号 */
    I2C_Stop();
    /* 执行成功 */
    return 1;

cmd_fail: /* 命令执行失败 */
    /* 发送停止命令 */
    I2C_Stop();
    /* 返回函数失败值 */
    return 0;
}

/**
 * @brief 向指定地址采用Page Write方式写入若干数据 
 * @param _pWriteBuf: 存放要写入数据的缓冲区指针
 * @param _usAddress: 起始地址
 * @param _usSize: 数据长度, 单位为字节
 * @retval 0: 失败, 1: 成功 
 */
uint8_t ee_WriteBytes(uint8_t *_pWriteBuf, uint16_t _usAddress, uint16_t _usSize)
{
    /* 计数变量 */
    uint16_t m = 0;
    uint16_t i = 0;
    /* usAddress存放设备的起始地址 */
    uint16_t usAddress = _usAddress;
    for (i = 0; i < _usSize; i++)
    {
        /* 发送第一个字节或是页面首地址时需要重新发起启动信号和地址 */
        if ((i == 1) || (usAddress & (EEPROM_PAGE_SIZE-1)) == 0)
        {
            /* 发送停止信号 */
            I2C_Stop();
            /*----------------------------------------
             * 通过检查器件应答的方式
             * 判断内部写操作是否完成
             * 一般小于10ms
             * CLK频率为200kHz时, 查询次数为30次左右
             *----------------------------------------*/
            for (m = 0; m < 1000; m++) /* 不断发送等待设备响应 */
            {
                /* 发起I2C启动信号 */
                I2C_Start();
                /* 发送设备8位写地址 */
                I2C_SendByte(EEPROM_DEV_ADDRESS | EEPROM_I2C_WR); 
                if (I2C_WaitAck() == 0) /* 器件有应答 */
                {
                    break;
                }
            }
            if (m == 1000) /* 设备超时 */
            {
                goto cmd_fail;
            }
            /* 发送字节所在地址 */
            I2C_SendByte((uint8_t)usAddress);
            /* 等待ACK响应 */
            if (I2C_WaitAck() != 0) /* 器件无应答 */
            {
                goto cmd_fail;
            }
            /* 开始写入数据 */
            I2C_SendByte(_pWriteBuf[i]);
            if (I2C_WaitAck() != 0) /* 器件无应答 */
            {
                goto cmd_fail;
            }
            /* 地址自增 */
            usAddress++;
        }
        /* 写入完成后, 发送总线停止信号 */
        I2C_Stop();
        /* 返回发送成功标志值 */
        return 1;
    }

cmd_fail:
    /* 发送I2C总线停止信号 */
    I2C_Stop();
    /* 返回发送失败标志值 */
    return 0;
}

/**
 * @brief 用0填充EEPROM
 * @param None
 * @return None
 */
void ee_Erase(void)
{
    /* 循环变量 */
    uint16_t i = 0;
    uint8_t buf[EEPROM_DEV_SIZE];
    /* 用1填充EEPROM */
    for (i = 0; i < EEPROM_DEV_SIZE; i++)
    {
        buf[i] = 0xFF;
    }
    /* 用0填充EEPROM */
    if (ee_WriteBytes(buf, 0, EEPROM_DEV_SIZE) == 0)
    {
        printf("Delete EEPROM ERROR\n");
        return;
    }
    else
    {
        printf("Delete EEPROM OK\n");
        return;
    }
}

/**
 * @brief 简单延时函数 
 * @param nCount: 延时次数
 * @return None
 */
static void ee_Delay(__IO uint32_t nCount)
{
    for ( ; nCount!= 0; nCount--)
    {
        ;
    }
}

/**
 * @brief 对EEPROM进行读写测设
 * @param None
 * @retval 0: 失败, 1: 成功
 */
uint8_t ee_Test(void)
{
    uint16_t i = 0;
    /* 定义写入缓冲区和读取缓冲区 */
    uint8_t write_buf[EEPROM_DEV_SIZE];
    uint8_t read_buf[EEPROM_DEV_SIZE];
    /* 检测EEPROM是否正常 */
    if (ee_CheckOk() == 0)
    {
        /* 打印EEPROM设备检测错误信息 */
        printf("No EEPROM\n");
    }
    /* 填充测试缓冲区 */
    for (i = 0; i < EEPROM_DEV_SIZE; i++)
    {
        /* 用0 ~ EEPROM_DEV_SIZE 填充 */
        write_buf[i] = i;
    }
    /* 写入EEPROM */
    if (ee_WriteBytes(&write_buf[0], 0, EEPROM_DEV_SIZE) == 0) /* 写入错误 */
    {
        /* 打印写入错误信息 */
        printf("Write EEPROM ERROR\n");
    }
    else
    {
        /* 打印写入正确信息 */
        printf("Write EEPROM OK\n");
    }
    /* 等待EEPROM写内部写入结束 */
    ee_Delay(0x0FFFFF);
    /* 读取EEPROM数据 */
    if (ee_ReadBytes(&read_buf[0], 0, EEPROM_DEV_SIZE) == 0) /* 读取错误 */
    {
        /* 打印读取错误信息 */
        printf("Read EEPROM ERROR\n");
        /* 程序结束返回0 */
        return 0;
    }
    else /* 读取正确 */
    {
        /* 打印正确读取信息 */
        printf("Read EEPROM OK\n");
    }
    /* 打印输出比较结果信息 */
    printf("Here are the results\n");
    /* 判断数据是否相同 */
    for (i = 0; i < EEPROM_DEV_ADDRESS; i++)
    {
        if (read_buf[i] != write_buf[i]) /* 数据不同 */
        {
            /* 打印错误数据的内容 */
            printf("0x%02X", read_buf[i]);
            /* 打印错误显示 */
            printf("ERROR: The Data is not correct\n");
            /* 程序结束返回0 */
            return 0;
        }
        else /* 数据相同 */
        {
            /* 打印正确数据的内容 */
            printf(" %02X", read_buf[i]);
        }
        /* 每16位换行 */
        if ((i & 15) == 15)
        {
            printf("\r\n");
        }
    }
    /* 输出通过测试信息 */
    printf("Test Past\n");
    /* 程序结束返回1 */
    return 1;
}
