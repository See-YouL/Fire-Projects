
# GPIO输出-使用固件库点亮LED

项目地址: **12-GPIO输出-使用固件库点亮LED**

## RGB原理图

![RGB原理图](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202412290150001.png)

- IO口低电平点亮
- 红PB5, 绿PB0, 蓝PB1

在User目录下新建led文件夹，添加bsp_led.c和bsp_led.h

## 在bsp_led.h中添加所使用的宏定义和函数声明

```c
/**
  ******************************************************************************
  * @file    bsp_led.h
  * @author  eric
  * @version V0.0.1
  * @date   29-December-2024 
  * @brief  LED蓝灯GPIO端口定义 
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FUCTIONS WHICH IS FOR GUIDANCE ONLY
  ******************************************************************************
  */

#ifndef __BSP_LED_H
#define __BSP_LED_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

#define LED_B_GPIO_PIN GPIO_Pin_1 //!< 引脚1 
#define LED_B_GPIO_PORT GPIOB //!< 端口B 
#define LED_B_GPIO_CLK RCC_APB2Periph_GPIOB //!< 端口时钟GPIOB

#define ON 1 //!< 亮为1
#define OFF 0 //!< 灭为0

// 参数为1时IO口输出低电平，灯亮；参数为0时IO口输出高电平，灯灭
#define LED_B(a) if (a)\
                     GPIO_ResetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN); \
                     else\
                     GPIO_SetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN);
// 使用\可以进行换行，其后不能跟空格，\后应该直接回车

void LED_GPIO_Config(void);

#endif // !__BSP_LED_H

```

## 在bsp_led.c中添加初始化函数

```c
/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  eric
  * @version V0.0.1
  * @date   29-December-2024 
  * @brief  LED蓝灯GPIO配置函数 
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FUCTIONS WHICH IS FOR GUIDANCE ONLY
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bsp_led.h" // bsp: board support package 板级支持包

/**
 * @brief 配置PB1为推挽输出
 * @param None
 * @retval None 
 */
void LED_GPIO_Config(void)
{
    RCC_APB2PeriphClockCmd(LED_B_GPIO_CLK, ENABLE); // 使能PB端口时钟
    GPIO_InitTypeDef GPIO_InitStruct; // 定义GPIO初始化结构体变量
    GPIO_InitStruct.GPIO_Pin = LED_B_GPIO_PIN; // 1端口
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出模式
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; // 速度50MHz
    GPIO_Init(LED_B_GPIO_PORT, &GPIO_InitStruct); // 初始化PB1
}

```

## 在main.c中调用初始化函数，并进行软件延时，实现LED闪烁

```c
/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  eric
  * @version V0.0.1
  * @date   29-December-2024 
  * @brief  LED蓝灯GPIO配置函数 
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FUCTIONS WHICH IS FOR GUIDANCE ONLY
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bsp_led.h" // bsp: board support package 板级支持包

/**
 * @brief 配置PB1为推挽输出
 * @param None
 * @retval None 
 */
void LED_GPIO_Config(void)
{
    RCC_APB2PeriphClockCmd(LED_B_GPIO_CLK, ENABLE); // 使能PB端口时钟
    GPIO_InitTypeDef GPIO_InitStruct; // 定义GPIO初始化结构体变量
    GPIO_InitStruct.GPIO_Pin = LED_B_GPIO_PIN; // 1端口
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出模式
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; // 速度50MHz
    GPIO_Init(LED_B_GPIO_PORT, &GPIO_InitStruct); // 初始化PB1
}

```
