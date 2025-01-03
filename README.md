# STM32F103学习笔记

## 说明

本库仅供学习交流使用

- 开发板: 野火霸道V2开发板
- 编译器： ARM v5.06
- C编译版本: C99
- 固件库版本: V3.5.0
- MDK version: 538A
- 芯片包: Keil.STM32F1xx_DFP.2.4.1
- 芯片型号: STM32F103ZET6
- 参考视频: 【【单片机】野火STM32F103教学视频 (配套霸道/指南者/MINI)【全】(刘火良老师出品) (无字幕)】 <https://www.bilibili.com/video/BV1yW411Y7Gw/?p=9&share_source=copy_web&vd_source=0db47c15b9f51dbaa4548ec2dc55dea4>
- [仓库地址](https://github.com/See-YouL/Fire-Projects.git)
- [博客地址](https://see-youl.github.io/)
- 使用Doxygen生成项目文档保存在Doc/html/index.html

### 代码规范

注意一下提到的代码规范符合**Doxygen要求**

参考链接[CSDN关于Doxygen语法](https://blog.csdn.net/qq_41204464/article/details/102458103)

#### 变量批注

```c
int a = 1; //!< 测试变量a的单行批注
int b = 1; /*!< 测试变量b的块批注 */
```

#### 在每个文件的头部添加如下注释

```c
/**
  ******************************************************************************
  * @file    文件名
  * @author  作者名
  * @version 版本号V0.0.1
  * @date    日期31-January-2024
  * @brief   文件作用简介
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FUCTIONS WHICH IS FOR GUIDANCE ONLY
  ******************************************************************************
  */
```

#### 在函数前添加如下注释

```c
/**
 * @brief 函数简介
 * @param 形参1: 形参1说明
 * @param 形参2: 形参2说明
 * @retval 返回值说明
 */

/// 例如

/**
  * @brief  Initializes the GPIOx peripheral according to the specified
  *         parameters in the GPIO_InitStruct.
  * @param  GPIOx: where x can be (A..G) to select the GPIO peripheral.
  * @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure that
  *         contains the configuration information for the specified GPIO peripheral.
  * @retval None
  */
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{

}
 
```

#### 在结构体或枚举变量前添加如下注释

```c
/**
 * @brief 结构体或枚举说明
 */

typedef struct
{
    int a; //!< 成员单行注释
    int b; /*!< 成员
                换行注释块 */
}A;

// 例如

/** 
  * @brief  GPIO Init structure definition  
  */

typedef struct
{
  uint16_t GPIO_Pin;             /*!< Specifies the GPIO pins to be configured.
                                      This parameter can be any value of @ref GPIO_pins_define */

  GPIOSpeed_TypeDef GPIO_Speed;  /*!< Specifies the speed for the selected pins.
                                      This parameter can be a value of @ref GPIOSpeed_TypeDef */

  GPIOMode_TypeDef GPIO_Mode;    /*!< Specifies the operating mode for the selected pins.
                                      This parameter can be a value of @ref GPIOMode_TypeDef */
}GPIO_InitTypeDef;

/** 
  * @brief  Bit_SET and Bit_RESET enumeration  
  */

typedef enum
{ Bit_RESET = 0,
  Bit_SET
}BitAction;
```

## 基础配置

### 配置KeilMDK

看视频配置KeilMDK,P2

[看视频配置Keil MDK](https://www.bilibili.com/video/BV1yW411Y7Gw)

### 配置串口下载程序

看视频配置串口下载程序,P4

[看视频配置串口下载程序](https://www.bilibili.com/video/BV1yW411Y7Gw)

### 美化Keil界面

**非必须步骤**, 用来美化界面

[使用该方案的插件](https://www.bilibili.com/video/BV1uT411S7mB/?share_source=copy_web&vd_source=0db47c15b9f51dbaa4548ec2dc55dea4)

[使用该方案的主题配色](https://www.bilibili.com/video/BV1Df4y1k75Z/?share_source=copy_web&vd_source=0db47c15b9f51dbaa4548ec2dc55dea4)

### 配置VScode

**非必须步骤**, 用来使用VScode开发, *也可使用Keil MDK则不需要该步骤*

方案一: 使用VScode + Keil5 MDK进行开发(主要插件**Keil Assistant**)

- 优点: 不需要使用Keil进行编辑
- 缺点: 不具备Debug功能,只有编译和烧录

[方案一参考视频](https://www.bilibili.com/video/BV19V411g7gD/?share_source=copy_web&vd_source=0db47c15b9f51dbaa4548ec2dc55dea4)

方案二: 使用Vscode + EIDE进行开发(主要插件**EIDE**)

- 优点: 可在VScode中进行调试
- 缺点: 依赖Keil的编译环境

[方案二参考视频](https://www.bilibili.com/video/BV1nr4y1R7Jb/?share_source=copy_web&vd_source=0db47c15b9f51dbaa4548ec2dc55dea4)

## 理论知识

### STM32命名方式

- STM32: 32bit的MCU
- F或L: F表示基础型(Foundation)或高性能型(High-Performance), L表示低功耗型(Ultra-low-power)
- xxx: 芯片特性, 如性能级别、内存大小、特殊功能等
- 系列:
  - F0, F1, F2, F3, F4, F7：这些数字代表不同的性能级别，数字越大，性能通常越高。
  - L0, L1, L4, L5：这些是低功耗系列，数字越大，性能和功能通常越丰富。
- 性能级别: 通常由一到两位数字表示，如STM32F103或STM32L152。这些数字表示不同的性能级别、内存大小和外设
- 包装类型: 通常由一个字母表示，如STM32F103C8T6中的C表示LQFP48封装
- 额外特性: 如STM32F103C8T6中的8表示该芯片有64KB闪存，T表示温度范围（-40°C 到 85°C），6表示批次号或版本

#### 例子

以 STM32F103C8T6 为例：

- STM32：STMicroelectronics的32位微控制器。
- F：Foundation系列。
- 103：该系列中的特定型号，具有特定的性能、内存和外设配置。
- C：封装类型，这里是LQFP48。
- 8：闪存大小，这里是64KB。
- T：温度范围，这里是-40°C 到 85°C。
- 6：批次号或版本。

## 置位与清零

- &= ~(1 << n); **将bit n清零,其他位保持不变**
- |= (1 << n); **将bit n置1,其他位保持不变**

## GPIO

### GPIO简介

GPIO(General purpose input output)通用输入输出端口的简称,**软件可以控制的引脚,可输入可输出**

#### GPIO和引脚的区别

引脚（Pin）

- 定义：引脚是指微控制器、微处理器或其他电子组件上的物理接点。它们是硬件设备的一部分，用于连接电路板、传递信号或供电。
- 通用性：引脚可以有多种功能，包括但不限于传输数据、供电、接地或作为特殊功能的接口（如模拟输入、PWM输出等）。
- 物理特性：引脚是实体的、物理存在的，可以是金属的脚或焊盘。

GPIO（General-Purpose Input/Output）

- 定义：GPIO是指在微控制器或其他数字电路设备上的一种特定类型的引脚，可以通过编程设置为输入或输出模式。
- 功能：GPIO引脚的功能非常灵活，可以用于读取数字信号（如按钮的按压）或输出数字信号（如控制LED灯的开关）。
- 编程控制：GPIO引脚的主要特点是它们可以通过软件编程来控制其行为，这使得它们非常适合于各种通用的数字输入输出任务。

区别

- 功能范围：所有GPIO都是引脚，但并非所有引脚都是GPIO。引脚是一个更广泛的概念，包括GPIO以及其他专用功能的引脚。
- 灵活性和用途：GPIO引脚特别设计用于通用的数字输入输出任务，并且它们的行为可以通过软件编程来改变。而其他类型的引脚可能有固定的功能，如电源、接地或特定的通信功能。
- 编程控制：GPIO的关键特性是它们可以被编程来执行不同的任务（输入或输出），而其他类型的引脚可能不具备这种灵活性。

总的来说，**GPIO是引脚的一个子集，专门用于可编程的通用数字输入输出任务。而引脚是一个更广泛的概念，涵盖了电子设备上的所有物理接点。**

#### 引脚的分类

![引脚的分类](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/%E6%88%AA%E5%B1%8F2023-12-28%2014.37.46.png)

### GPIO 框图讲解

#### 保护二极管

![保护二极管](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/%E6%88%AA%E5%B1%8F2023-12-28%2014.41.14.png)

- **如果引脚电压大于VDD则上面的保护二极管导通**,防止高电压进入芯片内部,如果电压过高则会烧坏二极管进而烧坏芯片
- **如果引脚电压低于VSS则下面的保护二极管导通**,保护芯片

#### 推挽输出

![ODR=1时推挽输出原理图](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/%E6%88%AA%E5%B1%8F2023-12-28%2015.09.27.png)

推挽输出部分的INT来自ODR寄存器

若ODR为1, 经过反相器后为0, 此时PMOS和NMOS的Ug=0V

对于PMOS, Us=3.3V > Ug=0V, PMOS管导通, OUT=VDD

对于NMOS, Us=0V = Ug=0V, 简单认为, NMOS管截止

![ODR=0时推挽输出原理图](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/%E6%88%AA%E5%B1%8F2023-12-28%2015.20.46.png)

若ODR为0,经过反相器后为1, 此时PMOS和NMOS的Ug=3.3V

对于PMOS, Us=3.3V = Ug=3.3V, 简单认为, PMOS管截止

对于NMOS, Us=0V < Ug=3.3V, NMOS管导通, OUT=GND=0V

##### 推挽输出的含义

![推挽输出含义图](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/%E6%88%AA%E5%B1%8F2023-12-28%2015.23.18.png)

- PMOS导通时, OUT处电流向外称为**推**, 此时电流称为**灌电流**
- NMOS导通时, OUT处电流向里称为**挽**, 此时电流称为**拉电流**

推挽输出（Push-Pull Output）是一种常见的电子电路输出类型，特别是在数字电路和微控制器的GPIO（通用输入/输出）引脚中。这种输出类型的**主要特点是它使用两个晶体管（一个N型和一个P型）来控制输出引脚的电压状态。**

##### 推挽输出的原理

在推挽配置中，通常有两个晶体管：

- N型晶体管：当被激活（或导通）时，它将输出引脚连接到地（GND），从而产生低电平（0）输出。
- P型晶体管：当被激活时，它将输出引脚连接到正电源（VCC），从而产生高电平（1）输出。

这两个晶体管不会同时导通，以避免短路。在任何给定的时刻，要么N型晶体管导通将输出拉低，要么P型晶体管导通将输出拉高。

##### 推挽输出的特点

- 强驱动能力：**推挽输出可以提供较强的电流驱动能力**，无论是向输出引脚提供电流（高电平）还是从引脚吸收电流（低电平）。
- 确定的逻辑状态：输出要么明确地是高电平，要么是低电平，**不会处于悬空（高阻态）状态**。
- 无需外部上拉或下拉电阻：由于**推挽输出自身就可以明确地驱动高电平或低电平**，因此不需要外部的上拉或下拉电阻来确保稳定的输出状态。

##### 推挽输出的应用

推挽输出广泛应用于各种数字电路，特别是**在需要驱动LED、继电器或其他需要较高电流的负载时**。由于其**强大的驱动能力和清晰的逻辑电平**，推挽输出是实现**数字信号传输**的理想选择。

##### 推挽输出对比开漏/开集输出

与推挽输出相对的是开漏（在MOSFET技术中）或开集（在双极晶体管技术中）输出，**这种类型的输出只有一个晶体管，要么将输出拉低，要么让它悬空（高阻态）**。开漏/开集输出**需要外部上拉电阻来确保高电平状态**，常用于需要多个设备共享同一输出线的应用，如I2C通信协议。

#### 开漏输出

内部只能输出低电平,不能输出高电平

![当ODR为1时开漏输出原理图](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/%E6%88%AA%E5%B1%8F2023-12-28%2016.06.58.png)

 该图片标注有误, 实际用的是ODR=0时的图, 但是结构相同, 不影响分析

ODR=1, 经反相器为0, Vg=0V=Vs=0V, NMOS管截止, 此时OUT为高阻态悬空, 加入外部上拉电阻后, OUT=1

如果外部需要高电平驱动可以通过更换外部上拉电路来进行更换

![当ODR为0时开漏输出原理图](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/%E6%88%AA%E5%B1%8F2023-12-28%2016.06.58.png)

ODR=0, 经反相器为1, Vg=1 > Vs=0, NMOS管导通, 此时OUT=0V

开漏输出（Open-Drain Output，在使用MOSFET技术的情况下称为开漏，而在使用双极性晶体管的情况下称为开集（Open-Collector）输出）是一种常见的电子电路设计，特别是在数字电路和微控制器的GPIO（通用输入/输出）引脚中。这种输出类型的**主要特点是它使用单个晶体管来控制输出引脚的电压状态，而不是像推挽输出那样使用两个晶体管。**

##### 开漏输出的原理

在开漏配置中，只有一个N型晶体管：

- N型晶体管：当晶体管导通（激活）时，它将输出引脚连接到地（GND），产生低电平（0）输出。当晶体管关闭（非激活）时，输出引脚不连接到任何东西，处于悬空状态。
- 由于输出在晶体管关闭时处于悬空状态，因此通常需要一个外部的上拉电阻连接到正电源（VCC），以确保当晶体管关闭时输出能够达到高电平（1）。

##### 开漏输出的特点

- 单向驱动能力：开漏输出**只能将输出拉低，不能主动驱动高电平**。
- 需要外部上拉电阻：**为了确保输出能够达到高电平，需要外部上拉电阻**。
- 适合于总线和共享线路：开漏输出非常**适合于多个设备共享同一输出线的应用**，因为任何一个设备都可以将线路拉低，而不会对其他设备造成干扰。

##### 开漏输出的应用

开漏输出**常用于需要多个设备共享同一通信线路的场合**，如I2C和1-Wire通信协议。在这些应用中，**多个设备可以连接到同一条线路上，每个设备都可以通过将线路拉低来发送信号，而不会影响其他设备。**

##### 开漏输出对比推挽输出

与开漏输出相对的是推挽输出，后者使用两个晶体管（一个N型和一个P型）来分别驱动高电平和低电平。推挽输出可以主动驱动高电平和低电平，而**开漏输出只能驱动低电平，需要外部上拉电阻来实现高电平状态。**

#### 补充: 高阻态与悬空

**高阻态（High-Impedance State），通常简称为Hi-Z**，是电子电路中的一个术语，用来描述一个电路节点在特定条件下呈现出非常高电阻的状态。在这种状态下，**电路节点既不明显地连接到电源（高电平），也不明显地连接到地（低电平）**。换句话说，这个节点处于一种“断开”或“浮空”的状态，对电路中的其他部分几乎没有任何电气影响。

##### 高阻态的应用

- **三态逻辑（Tri-state Logic）**：在数字电路中，高阻态常用于三态逻辑，**允许多个输出连接到同一个线路或总线上，而不会相互干扰**只有被选中的设备会将其输出置于低电阻状态（高电平或低电平），其他设备的输出则处于高阻态。
- **总线系统**：在微处理器、微控制器和其他数字系统的总线（如数据总线、地址总线）上，高阻态用于控制哪个设备可以在特定时刻向总线发送数据。
- **输入/输出端口**：在可编程的微控制器的GPIO（通用输入/输出）端口中，**高阻态可以用来防止未使用的或被配置为输入的端口对电路造成影响**。

##### 高阻态的重要性

- **避免冲突**：在多个设备共享同一通信线路时，高阻态可以防止输出冲突。
- **节能**：当端口处于高阻态时，它几乎不消耗电流，有助于降低功耗。
- **灵活性**：高阻态提供了电路设计的灵活性，特别是在需要多个设备共享同一资源的情况下。

##### 高阻态的注意事项

- **浮动电压**：当一个端口或线路处于高阻态时，它可能会因为电磁干扰或静电感应而捕获不确定的电压，**有时可能需要通过上拉或下拉电阻来确保稳定的逻辑状态**。
- **设计考虑**：在设计电路和编写程序时，需要考虑到高阻态的影响，确保在适当的时候启用或禁用高阻态。

在电子电路中，**“悬空”（Floating）是指一个电路节点没有被明确连接到电源（高电平）或地（低电平），也没有通过任何电阻或其他电子元件连接到其他电路节点的状态**这种状态下的节点电压是不确定的，因为它既不是被固定在逻辑高也不是逻辑低，而是可以随外部电磁场或附近电路的状态变化而变化。

##### 悬空状态的特点

- 不确定的电压：悬空的节点可能会随机地捕获周围环境的电磁干扰，导致其电压处于不确定的状态。
- 易受干扰：由于没有明确的电气连接，悬空的节点容易受到外部电磁干扰的影响。
- 可能导致问题：在数字电路中，悬空的输入引脚可能导致不稳定的逻辑状态，从而引发电路的不可预测行为。

##### 高阻态与悬空的关系

高阻态是一种特定的电路配置，**其中一个节点（如微控制器的GPIO引脚）被设置为非常高的电阻状态。这意味着该节点对电路的其他部分几乎没有电气影响，类似于断开连接**因此，**当一个引脚被设置为高阻态时，它实际上是在悬空状态**，因为它既不是明确地连接到高电平也不是低电平。

##### 高阻态与悬空区别和联系

- 联系：**高阻态通常会导致节点悬空**当一个节点处于高阻态时，由于其极高的电阻值，它实际上与电路的其他部分隔离，从而处于悬空状态。
- 区别：**高阻态是一种有意设置的电路状态**，用于特定的目的（如防止总线冲突）。而**悬空可能是无意的**，可能是由于设计不当或电路未完成造成的。

##### 悬空的注意事项

- 设计考虑：在设计电子电路和系统时，**应避免输入引脚悬空，因为这可能导致不稳定的行为**。通常**使用上拉或下拉电阻来确保这些引脚有一个确定的逻辑状态。**
- 高阻态应用：在某些情况下，如**多个设备共享一个通信总线，高阻态是必要的，以确保只有一个设备在任何时刻控制总线。**

#### 复用功能输出

![复用功能输出原理框图](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/%E6%88%AA%E5%B1%8F2023-12-28%2018.18.55.png)

通过片上外设如EXTI到引脚输出

#### 输入模式

ISR读出

![普通模式的输入](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/%E6%88%AA%E5%B1%8F2023-12-28%2018.24.03.png)

I/O引脚至上拉/下拉输入(通过BSRR寄存器软件配置), 经TTL肖特基触发器(>2V <1.2V), 至IDR寄存器读出

复用功能输入

![复用功能输入](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/%E6%88%AA%E5%B1%8F2023-12-28%2018.29.40.png)

以EXTI为例,RX数据经由TTL肖特基触发器到DR寄存器

模拟输入

![模拟输入框图](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/%E6%88%AA%E5%B1%8F2023-12-28%2018.33.21.png)

不经过TTL肖特基触发器直接被读出

#### GPIO框图对应寄存器

![GPIO框图](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/%E6%88%AA%E5%B1%8F2023-12-28%2018.35.42.png)

- 2部分: 推挽,开漏输出对应CRL,CRH寄存器
- 3部分: 输出数据寄存器对应ODR; 位设置/清除寄存器对应BSRR
- 上拉/下拉输入: 对应CRL,CRH,具体选择上拉还是下拉需要软件配置BSRR
- 5部分: 输入数据寄存器对应IDR

### GPIO输出初始化顺序

1. 时钟使能
2. 选择具体的GPIO
3. 配置GPIO的工作模式(CRL CRH)
4. 控制GPIO输出高低电平(ODR,BRR和BSRR)

## 手写库

### 通过地址使用寄存器

项目地址: **REG-LED**

#### main.c中的主要代码

```c
*(unsigned int *)(0x40021018) |= ((1) << 3); // RCC_APB2ENR的bit3置1
/*----------------------------------------------------------------
开启GPIOB的时钟
GPIOB挂载在APB2总线
RCC_APB2ENR的偏移量为0x18
RCC的基地址为0x40021000
RCC_APB2ENR的bit3为IOPBEN(IO端口B时钟使能) 1开启
****************************************************************************/
*(unsigned int *)(0x40010C00) |= ((1) << (4*0)); // GPIOB_CRL的bit4-0置0001
/*----------------------------------------------------------------
将GPIOB设置为推挽输出
GPIOB 基地址 0x40010C00
GPIOx_CRL 偏移量 00h 
bit1-0: 01 输出模式，最大速度10MHz
bit4-3: 00 通用推挽输出模式
((1) << (4*0)) // 若修改PB1则为(4*1)
****************************************************************************/
*(unsigned int *)(0x40010C0C) &= ~(1<<0); // GPIOB_ODR的bit0置0
/*----------------------------------------------------------------
修改PB0为1
GPIOB 基地址 0x40010C00
GPIOx_ODR 偏移量 0Ch 
****************************************************************************/
```

### 通过头文件定义使用寄存器

项目地址: **REG-LED-Register**

确定总线基地址, 其中AHB的基地址是从DMA1开始的,即从0x40020000开始

#### 在stm32f10x.h中增加宏定义

 ```c
// 存放stm32寄存器映射的代码

// 外设 Peripheral
#define PERIPH_BASE ((unsigned int)0x40000000)
#define APB1PERIPH_BASE (PERIPH_BASE) // 从TIM2开始
#define APB2PERIPH_BASE (PERIPH_BASE + 0x10000) // 从AFIO开始
#define AHBPERIPH_BASE (PERIPH_BASE + 0x20000) // 从DMA1开始

// RCC
#define RCC_BASE (AHBPERIPH_BASE + 0x1000) // RCC基地址 

// GPIOB
#define GPIOB_BASE (APB2PERIPH_BASE + 0x0C00) // GPIOB基地址

// 定义寄存器

#define RCC_APB2ENR (*(volatile unsigned int *)(RCC_BASE + 0x18)) // APB2外设时钟使能寄存器
#define GPIOB_CRL (*(volatile unsigned int *)(GPIOB_BASE + 0x00))// GPIOB_CRL
#define GPIOB_CRH (*(volatile unsigned int *)(GPIOB_BASE + 0x04)) // GPIOB_CRH
#define GPIOB_ODR (*(volatile unsigned int *)(GPIOB_BASE + 0x0C)) // GPIOB_CRH
 ```

#### 在main.c中的主函数代码改为

```c
RCC_APB2ENR |= ((1) << 3); // 开启GPIOB的时钟
GPIOB_CRL &= ~((0x0F) << (4*0)); // 将GPIOB状态清零
GPIOB_CRL |= ((1) << (4*0)); // 将GPIOB设置为推挽输出
GPIOB_ODR &= ~(1<<0); // PB0置0
```

#### 补充: 关键字volatile的作用

在C语言中，尤其是在嵌入式领域，volatile 关键字用于告诉编译器，**定义为 volatile 的变量可能会以编译器不可预知的方式被改变**。这意味着编译器在处理这些变量时，**应避免进行某些优化，确保每次访问都直接从内存中读取变量的值**。

#### 关键字volatile含义

当一个变量被声明为 volatile 时，编译器会对该变量的处理方式做出以下调整：

- **防止优化**：编译器不会对这些变量进行优化，这可能包括消除看似多余的读取或写入操作。
- **直接访问**：每次访问 volatile 变量时，都会直接从其内存地址读取数据，而不是使用可能存储在寄存器中的副本。

#### 关键字volatile的应用场景

在嵌入式编程中，volatile 关键字的使用场景主要包括：

- **硬件寄存器访问**：当编程与硬件寄存器交互时，如读取一个传感器的数据寄存器或写入一个控制寄存器。这些寄存器的值可能会在任何时候改变，因此需要使用 volatile 来确保每次读取或写入都是最新的值。
- **中断服务例程**：在中断服务例程（ISR）中使用的变量，这些变量可能在ISR中被改变，并在程序的其他部分被访问。使用 volatile 可以确保主程序中的代码能够看到在ISR中对这些变量所做的更改。
- **多线程和并发**：在多线程或并发环境中，一个线程可能修改另一个线程正在访问的变量。volatile 确保每个线程都能访问到最新的值。

#### 关键字volative的注意事项

- **不是并发解决方案**：volatile 关键字不能替代互斥锁或其他并发控制机制。它不保证操作的原子性或内存可见性。
- **性能影响**：由于 volatile 防止了某些优化，过度使用它可能会降低程序的性能。
- **正确使用**：只有在上述特定场景中才应使用 volatile。错误地使用 volatile 可能会导致难以发现的错误。

### 通过结构体操作寄存器

项目地址: **FWlib-LED**

#### 在stm32f10x.h中添加结构体定义

```c
// 定义结构体
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

typedef struct 
{
    uint32_t CRL;
    uint32_t CRH;
    uint32_t IDR;
    uint32_t ODR;
    uint32_t BSRR;
    uint32_t BRR;
    uint32_t LCKR;
}GPIO_TypeDef;

#define GPIOB ((GPIO_TypeDef *)GPIOB_BASE) // 使用GPIOB->访问成员变量
/*----------------------------------------------------------------
若定义为 #define GPIOB (*(GPIO_TypeDef *)(GPIOB_BASE))
则使用GPIOB.XXX来访问成员变量
----------------------------------------------------------------*/
```

在main.c中使用GPIOB->XXX的方式来访问结构体成员(即寄存器), 主要代码如下

```c
GPIOB->CRL &= ~((0x0F) << (4*1)); // 将GPIOB状态复位
GPIOB->CRL |= ((1) << (4*1)); // 将GPIOB设置为推挽输出
GPIOB->ODR &= ~(1<<0); // PB0置0
```

#### 在stm32f10x.h中增加RCC的结构体定义,如下

```c
typedef struct 
{
    uint32_t CR;
    uint32_t CFGR;
    uint32_t CIR;
    uint32_t APB2RSTR;
    uint32_t APB1RSTR;
    uint32_t AHBENR;
    uint32_t APB2ENR;
    uint32_t APB1ENR;
    uint32_t BDCR;
    uint32_t CSR;
    uint32_t AHBRSTR;
    uint32_t CFGR2;
}RCC_Typedef;

#define RCC ((RCC_Typedef*)RCC_BASE) // 使用RCC->访问成员变量
/*----------------------------------------------------------------
若定义为 #define RCC (*(RCC_Typedef*)RCC_Base)
则使用RCC.XXX来访问成员变量
----------------------------------------------------------------*/
```

#### 在main.c中通过结构体访问RCC寄存器,代码如下

```c
RCC->APB2ENR |= ((1) << 3); // 开启GPIOB的时钟
```

#### 更换LED说明

由于我的开发板，PB0总是点亮蓝灯(本应该是绿灯), 以后的测试换为测试蓝灯，**PB0换为PB1进行测试**

### 增加端口置位/复位函数

项目地址: **FWlib-LED**

增加stm32f10x_gpio.c和stm32f10x_gpio.h文件

#### 在stm32f10x_gpio.c中增加置位/复位函数

```c
#include "stm32f10x_gpio.h"

// 端口置位函数
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t Pin)
{
    GPIOx->BSRR |= Pin;
    /*----------------------------------------------------------------
    BSRR寄存器:
    低16位写1置1，写0不改变
    高16位写1置0，写0不改变
    *----------------------------------------------------------------*/
}

// 端口复位函数
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t Pin)
{
    GPIOx->BRR |= Pin;
    /*----------------------------------------------------------------
    BRR寄存器:
    低16位写1置0，写0不改变
    高16位保留
    ----------------------------------------------------------------*/
}
```

#### 在stm32f10x_gpio.h中添加16位PIN置1的宏定义与函数声明

```c
#ifndef __STM32F10X_GPIO_H
#define __STM32F10X_GPIO_H

#include "stm32f10x.h"

// 宏定义端口
#define GPIO_Pin_0    ((uint16_t)0x0001)  /*!< 选择Pin0 */    //(00000000 00000001)b
#define GPIO_Pin_1    ((uint16_t)0x0002)  /*!< 选择Pin1 */    //(00000000 00000010)b
#define GPIO_Pin_2    ((uint16_t)0x0004)  /*!< 选择Pin2 */    //(00000000 00000100)b
#define GPIO_Pin_3    ((uint16_t)0x0008)  /*!< 选择Pin3 */    //(00000000 00001000)b
#define GPIO_Pin_4    ((uint16_t)0x0010)  /*!< 选择Pin4 */    //(00000000 00010000)b
#define GPIO_Pin_5    ((uint16_t)0x0020)  /*!< 选择Pin5 */    //(00000000 00100000)b
#define GPIO_Pin_6    ((uint16_t)0x0040)  /*!< 选择Pin6 */    //(00000000 01000000)b
#define GPIO_Pin_7    ((uint16_t)0x0080)  /*!< 选择Pin7 */    //(00000000 10000000)b
#define GPIO_Pin_8    ((uint16_t)0x0100)  /*!< 选择Pin8 */    //(00000001 00000000)b
#define GPIO_Pin_9    ((uint16_t)0x0200)  /*!< 选择Pin9 */    //(00000010 00000000)b
#define GPIO_Pin_10   ((uint16_t)0x0400)  /*!< 选择Pin10 */   //(00000100 00000000)b
#define GPIO_Pin_11   ((uint16_t)0x0800)  /*!< 选择Pin11 */   //(00001000 00000000)b
#define GPIO_Pin_12   ((uint16_t)0x1000)  /*!< 选择Pin12 */   //(00010000 00000000)b
#define GPIO_Pin_13   ((uint16_t)0x2000)  /*!< 选择Pin13 */   //(00100000 00000000)b
#define GPIO_Pin_14   ((uint16_t)0x4000)  /*!< 选择Pin14 */   //(01000000 00000000)b
#define GPIO_Pin_15   ((uint16_t)0x8000)  /*!< 选择Pin15 */   //(10000000 00000000)b
#define GPIO_Pin_All  ((uint16_t)0xFFFF)  /*!< 选择全部引脚*/ //(11111111 11111111)b
/*----------------------------------------------------------------
对于类似于GPIOx_BSRR, GPIOx_BRR寄存器通过写1来进行置位/复位操作的寄存器来说
宏定义16位端口的1值很有必要
----------------------------------------------------------------*/

// 函数声明
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t Pin);
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t Pin);

#endif // !__STM32F10X_GPIO
```

#### 在main.c函数中使用置位/复位函数

```c
 // 增加复位/置位函数
RCC->APB2ENR  |=  ( (1) << 3 );
GPIOB->CRL &=  ~( (0x0f) << (4*0) );
GPIOB->CRL |=  ( (1) << (4*0) );
GPIO_SetBits(GPIOB,GPIO_Pin_1);
GPIO_ResetBits( GPIOB,GPIO_Pin_1 );
```

#### 在stm32f10x.h中增加#ifndef

```c
#ifndef __STM32F10X_H
#define __STM32F10X_H

// 中间代码省略

#endif // !__STM32F10X_H
```

#### 补充: 在C语言中#ifndef的作用

在C语言中，#ifndef 是一种预处理指令，用于条件编译。它的全称是 "if not defined"，意思是“如果没有定义”。#ifndef 通常与 #define 和 #endif 一起使用，**用于防止头文件的内容被多次包含（重复包含）**。

##### ifndef的作用

"#ifndef"的主要作用是**确保一个头文件中的内容只被包含一次，防止因重复包含同一头文件而导致的编译错误**这种技术被称为“包含卫士”（Include Guards）或“头文件卫士”（Header Guards）。

##### ifndef的使用方式

一个典型的使用 #ifndef 的例子如下：

```c
// 假设这是一个头文件 example.h

#ifndef EXAMPLE_H    // 如果没有定义 EXAMPLE_H
#define EXAMPLE_H    // 定义 EXAMPLE_H

// 头文件的内容
void someFunction();
// 更多的声明...

#endif // 结束 #ifndef
```

在这个例子中：

1. 当编译器首次遇到 example.h 时，EXAMPLE_H 还没有被定义，所以编译器会处理 #define EXAMPLE_H 和随后的头文件内容。
2. 如果同一源文件或其他包含了 example.h 的文件再次尝试包含 example.h，EXAMPLE_H 已经被定义了，因此 #ifndef EXAMPLE_H 条件失败，编译器将跳过文件的其余部分，防止重复包含。

##### ifndef的重要性

在C语言项目中，特别是在大型项目中，头文件经常被多个源文件包含，或者一个头文件包含其他头文件。如果没有包含卫士，头文件中的定义（如函数声明、宏定义、类型定义等）可能会被重复包含，导致编译错误（如重复定义错误）。使用 #ifndef 可以有效地避免这种情况。

#### 补充: 使用#ifndef命名使用双下划线说明

在C语言中，当使用 #ifndef（和 #define、#endif）作为头文件的包含卫士时，通常会在文件名前加上双下划线 __ 或其他类似的前缀/后缀，**这是一种非正式的约定，用于减少命名冲突的风险**然而，需要注意的是，**使用双下划线作为前缀或后缀在某些情况下可能并不是最佳实践**。

##### 使用双下划线的原因

- **唯一性**：在大型项目中，可能会有许多不同的头文件。使用文件名作为宏的一部分可以帮助确保每个包含卫士的宏是唯一的。
- **减少冲突**：添加额外的字符（如双下划线）可以进一步减少不同头文件之间宏名称冲突的可能性。

##### 使用双下划线的注意事项

**保留标识符**：根据C和C++标准，**以双下划线开头或以单下划线后跟大写字母开头的标识符是保留给实现（编译器和标准库）使用的**。因此，使用这样的标识符作为宏名称**可能会导致与标准库或编译器的内部标识符冲突**。

建议的做法：更安全的做法是**使用文件名的大写形式加上一个后缀（如 _H），而不是使用双下划线**。例如，对于 example.h 头文件，可以使用 EXAMPLE_H 作为包含卫士的宏。

##### 示例

```c
#ifndef EXAMPLE_H    // 更安全的做法
#define EXAMPLE_H

// 头文件内容

#endif // EXAMPLE_H
```

总之，**虽然在文件名前加上双下划线是一种常见做法，但为了避免与编译器或标准库的内部标识符冲突，建议使用其他方法来确保宏名称的唯一性和安全性**。

### 增加GPIO初始化结构体

项目地址: **FWlib-LED**

配置GPIO工作模式的宏定义(GPIOMode_TypeDef)参考下图

![GPIO工作模式图](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202312301523539.png)

实际写入寄存器的是bit3-0,bit7-4并不写入寄存器

勘误：上拉输入和下拉输入两行的bit3-2应该为10

- bit1-0: 置0, 配置输出速度，通过GPIOSpeed_TypeDef进行覆盖配置
- bit3-2: 配置输入/输出模式
- bi4: **不写入寄存器**, 用来标志是输入还是输出
- bit6-5: **不写入寄存器**， 用来判断是上拉输入还是下拉输入
- bit7: **不写入寄存器**

#### 在stm32f10x_gpio.h中增加宏定义

```c
// 通过枚举 限定GPIO_Speed的选择
typedef enum
{
    GPIO_Speed_10MHZ = 1, // 01 输出模式，最大速度10MHz
    GPIO_Speed_2MHZ, // 10 输出模式，最大速度2MHz
    GPIO_Speed_50MHZ // 11 输出模式，最大速度50MHz
}GPIOSpeed_TypeDef;

// 通过枚举限定GPIO_Mode的选择
typedef enum
{ GPIO_Mode_AIN = 0x0,           // 模拟输入     (0000 0000)b
  GPIO_Mode_IN_FLOATING = 0x04,  // 浮空输入     (0000 0100)b
  GPIO_Mode_IPD = 0x28,          // 下拉输入     (0010 1000)b
  GPIO_Mode_IPU = 0x48,          // 上拉输入     (0100 1000)b
  
  GPIO_Mode_Out_OD = 0x14,       // 开漏输出     (0001 0100)b
  GPIO_Mode_Out_PP = 0x10,       // 推挽输出     (0001 0000)b
  GPIO_Mode_AF_OD = 0x1C,        // 复用开漏输出 (0001 1100)b
  GPIO_Mode_AF_PP = 0x18         // 复用推挽输出 (0001 1000)b
}GPIOMode_TypeDef;

// 定义GPIO初始化结构体
typedef struct
{
    uint16_t GPIO_Pin;
    uint16_t GPIO_Speed;
    uint16_t GPIO_Mode;
}GPIO_InitTypeDef;

void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
```

#### 在stm32f10x_gpio.c中写入GPIO初始化函数

该函数是从库函数中复制得到

```c
// GPIO初始化函数
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
  uint32_t currentmode = 0x00, currentpin = 0x00, pinpos = 0x00, pos = 0x00;
  uint32_t tmpreg = 0x00, pinmask = 0x00;
  
/*---------------------- GPIO 模式配置 --------------------------*/
  // 把输入参数GPIO_Mode的低四位暂存在currentmode
  currentmode = ((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x0F);
 
  // bit4是1表示输出，bit4是0则是输入 
  // 判断bit4是1还是0，即首选判断是输入还是输出模式
  if ((((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x10)) != 0x00)
  { 
    // 输出模式则要设置输出速度
    currentmode |= (uint32_t)GPIO_InitStruct->GPIO_Speed;
  }
/*-------------GPIO CRL 寄存器配置 CRL寄存器控制着低8位IO- -------*/
  // 配置端口低8位，即Pin0~Pin7
  if (((uint32_t)GPIO_InitStruct->GPIO_Pin & ((uint32_t)0x00FF)) != 0x00)
  {
    // 先备份CRL寄存器的值
    tmpreg = GPIOx->CRL;
  
    // 循环，从Pin0开始配对，找出具体的Pin
    for (pinpos = 0x00; pinpos < 0x08; pinpos++)
    {
      // pos的值为1左移pinpos位
      pos = ((uint32_t)0x01) << pinpos;
      
      // 令pos与输入参数GPIO_PIN作位与运算，为下面的判断作准备
      currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;
   
      //若currentpin=pos,则找到使用的引脚
      if (currentpin == pos)
      {
        // pinpos的值左移两位（乘以4），因为寄存器中4个寄存器位配置一个引脚
        pos = pinpos << 2;
       //把控制这个引脚的4个寄存器位清零，其它寄存器位不变
        pinmask = ((uint32_t)0x0F) << pos;
        tmpreg &= ~pinmask;
    
        // 向寄存器写入将要配置的引脚的模式
        tmpreg |= (currentmode << pos);  
    
        // 判断是否为下拉输入模式
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
        {
          // 下拉输入模式，引脚默认置0，对BRR寄存器写1可对引脚置0
          GPIOx->BRR = (((uint32_t)0x01) << pinpos);
        }    
        else
        {
          // 判断是否为上拉输入模式
          if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
          {
            // 上拉输入模式，引脚默认值为1，对BSRR寄存器写1可对引脚置1
            GPIOx->BSRR = (((uint32_t)0x01) << pinpos);
          }
        }
      }
    }
  // 把前面处理后的暂存值写入到CRL寄存器之中
    GPIOx->CRL = tmpreg;
  }
/*-------------GPIO CRH 寄存器配置 CRH寄存器控制着高8位IO- -----------*/
  // 配置端口高8位，即Pin8~Pin15
  if (GPIO_InitStruct->GPIO_Pin > 0x00FF)
  {
    // 先备份CRH寄存器的值
    tmpreg = GPIOx->CRH;
  
    // 循环，从Pin8开始配对，找出具体的Pin
    for (pinpos = 0x00; pinpos < 0x08; pinpos++)
    {
      pos = (((uint32_t)0x01) << (pinpos + 0x08));
   
      // pos与输入参数GPIO_PIN作位与运算
      currentpin = ((GPIO_InitStruct->GPIO_Pin) & pos);
   
      //若currentpin=pos,则找到使用的引脚
      if (currentpin == pos)
      {
        //pinpos的值左移两位（乘以4），因为寄存器中4个寄存器位配置一个引脚
        pos = pinpos << 2;
        
        //把控制这个引脚的4个寄存器位清零，其它寄存器位不变
        pinmask = ((uint32_t)0x0F) << pos;
        tmpreg &= ~pinmask;
    
        // 向寄存器写入将要配置的引脚的模式
        tmpreg |= (currentmode << pos);
        
        // 判断是否为下拉输入模式
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
        {
          // 下拉输入模式，引脚默认置0，对BRR寄存器写1可对引脚置0
          GPIOx->BRR = (((uint32_t)0x01) << (pinpos + 0x08));
        }
         // 判断是否为上拉输入模式
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
        {
          // 上拉输入模式，引脚默认值为1，对BSRR寄存器写1可对引脚置1
          GPIOx->BSRR = (((uint32_t)0x01) << (pinpos + 0x08));
        }
      }
    }
    // 把前面处理后的暂存值写入到CRH寄存器之中
    GPIOx->CRH = tmpreg;
  }
}
```

#### 在main.c中使用GPIO初始化函数

```c
GPIO_InitTypeDef GPIO_InitStructure;
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHZ;
GPIO_Init(GPIOB, &GPIO_InitStructure);
```

### 增加宏定义来增强代码可移植性

项目地址： **FWlib-LED**

#### 在main.c中增加宏定义

```c
#define LED_B_GPIO_PORT GPIOB
#define LED_B_GPIO_CLK_ENABLE (RCC->APB2ENR |= ((1) << 3)) 
#define LED_B_GPIO_PIN GPIO_Pin_0
```

在main.c中增加延时函数，实现LED闪烁

```c
void Delay(uint32_t count)
{
  for( ; count != 0; count-- )
  {
    ;
  }
}
```

#### 在main.c中使用宏定义后的代码实现LED闪烁

```c
// 增加宏定义以增强代码可移植性
LED_B_GPIO_CLK_ENABLE;
GPIO_InitTypeDef GPIO_InitStructure;
GPIO_InitStructure.GPIO_Pin = LED_B_GPIO_PIN;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHZ;
GPIO_Init(GPIOB, &GPIO_InitStructure);

while(1)
{
  GPIO_SetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN); // PB1置1 蓝灯灭
  Delay(0xFFFF);
  GPIO_ResetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN); // PB1置0 蓝灯亮
  Delay(0xFFFF);
}
```

## 固件库编程

### STM32固件库文件分析

1. 汇编编写的启动文件 startup_stm32f10x_h.s: 设置堆栈指针,设置PC指针，初始化中断向量表，配置系统时钟，调用C库函数_main最终去C的世界
2. 时钟配置文件 system_stm32f10x.c: 把外部时钟HSE=8M，经过PLL倍频成72M
3. 外设相关
   - stm32f10x.h: 实现了内核之外的外设的寄存器映射
   - xx: GPIO, USART, I2C
   - stm32f10x_xx.c: 外设的驱动函数库文件
   - stm32f10x_xx.h: 存放外设的初始化结构体，外设初始化结构体成员的参数列表，外设固件库的头文件声明
4. 内核相关
    - CMSIS: Cortex微控制器软件接口标准
    - core_cm3.h: 实现了内核里面外设的寄存器映射
    - core_cm3.c: 内核外设的驱动固件库
    - NVIC(嵌套向量中断控制器), SysTick(系统滴答定时器), misc.h, misc.c
5. 头文件的配置文件 stm32f10x_conf.h里面包含
    - stm32f10x_usar.c
    - stm32f10x_i2c.h
    - stm32f10x_spi.h
    - stm32f10x_adc.h
    - stm32f10x_fsmc.h
6. 专门存放终端服务函数的C文件(可以放在其他地方，不一定要放在stm32f10x_it.c中)
    - stm32f10x_it.c
    - stm32f10x_it.h

### 新建固件库版本工程

项目地址: **Fwlib-Template**

- Doc: 用来存放程序说明的文件，由写程序的人添加
- Libraries: 存放库文件
- Project: 存放工程
- User: 用户编写的驱动文件

其余按照视频配置，P18, 视频链接: [按照P18进行库移植](https://www.bilibili.com/video/BV1yW411Y7Gw/?p=18&share_source=copy_web&vd_source=0db47c15b9f51dbaa4548ec2dc55dea4)

### GPIO输出-使用固件库点亮LED

项目地址: **12-GPIO输出-使用固件库点亮LED**

#### RGB原理图

![RGB原理图](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202412290150001.png)

- IO口低电平点亮
- 红PB5, 绿PB0, 蓝PB1

在User目录下新建led文件夹，添加bsp_led.c和bsp_led.h

#### 在bsp_led.h中添加所使用的宏定义和函数声明

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

#### 在bsp_led.c中添加初始化函数

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

#### 在main.c中调用初始化函数，并进行软件延时，实现LED闪烁

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

### GPIO输入

项目地址: **13-GPIO输入-按键检测**

通过原理图可知**KEY1接PA0口, 按键按下后为高电平**, 原理图如下

![KEY1原理图](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401011723631.png)

实现**按下KEY1后蓝灯状态翻转**

#### 在bsp_led.h中宏定义电平翻转函数

```c
#define LED_B_TOGGLE {LED_B_GPIO_PORT->ODR ^= LED_B_GPIO_PIN;}
/*----------------------------------------------------------------
^= 异或运算 (a ^ b) 则ab不同为1，相同则为0
ODR低16位和GPIO_Pin_1作异或并重新赋值给ODR可实现ODR的Bit0翻转
若Bit0=1则Bit0 = 1 ^ 1 = 0, 下一次运算时, Bit0=0则Bit0 = 0^1 = 1
实际上是ODR的Bit0在和1进行异或操作
----------------------------------------------------------------*/
```

#### 在bsp_key.h中进行宏定义和函数声明

```c
#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include "stm32f10x.h"

#define KEY_ON 1
#define KEY_OFF 0

// 宏定义
#define KEY1_GPIO_PIN GPIO_Pin_0 // stm32f10x_gpio.h中定义
#define KEY1_GPIO_PORT GPIOA // stm32f10x.h中定义 
#define KEY1_GPIO_CLK RCC_APB2Periph_GPIOA

// 函数声明
void KEY_GPIO_Config(void);
uint8_t Key_Scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

#endif // !__BSP_KEY_H
```

#### 在bsp_key.c中写初始化函数和端口扫描函数

```c
#include "bsp_key.h"

void KEY_GPIO_Config(void)
{
    RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK, ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = KEY1_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStruct);
}

// 端口扫面函数 检测按下返回1，否则返回0
uint8_t Key_Scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    if(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON)
    {
        while(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON)
        {
            ;
        }

        return KEY_ON;
    }
    else
    {
        return KEY_OFF;
    }
    
}

```

#### 在main.c中进行调用

```c
int main(void)
{
    LED_GPIO_Config();
    KEY_GPIO_Config();

    while(1)
    {
        if(Key_Scan(KEY1_GPIO_PORT, KEY1_GPIO_PIN) == KEY_ON)
        {
            LED_B_TOGGLE;
        }
    }
}
```

#### 补充: C语言中的异或操作

在C语言中，异或运算是一种基本的位运算，使用符号 ^ 表示。**异或运算符对两个操作数的对应位进行比较，如果两个相应的位不同，则结果为1，如果相同，则结果为0**换句话说，它在以下情况下返回1：

- 第一个操作数的位是0，第二个操作数的位是1。
- 第一个操作数的位是1，第二个操作数的位是0。

##### C语言异或运算的特性

- 交换律：a ^ b 等于 b ^ a。
- 结合律：(a ^ b) ^ c 等于 a ^ (b ^ c)。
- 自反性：任何数与自身异或的结果都是0，即 a ^ a 等于 0。
- 与0的异或：任何数与0异或都等于它本身，即 a ^ 0 等于 a。

##### C语言异或操作的应用

异或运算在C语言编程中有多种应用：

**值交换**：不使用临时变量交换两个变量的值。

```c
a = a ^ b;
b = a ^ b;
a = a ^ b;
```

这种方法虽然巧妙，但**在实际编程中不常用**，因为如果 a 和 b 指向同一内存位置，这会导致结果为0。

**反转特定位**：可以使用异或运算来反转数值中的特定位。

```c
x = x ^ (1 << n);  // 反转x的第n位
```

**检查奇偶性**：通过检查数的最低位是否为1，可以使用异或运算来快速检查一个数是奇数还是偶数。

**加密和解密**：由于异或运算的自反性，它可以用于简单的加密和解密操作。

##### C语言异或操作的示例

```c
#include <stdio.h>

int main() {
    unsigned int a = 5;  // 二进制: 0101
    unsigned int b = 3;  // 二进制: 0011

    // 执行异或运算
    unsigned int result = a ^ b;  // 结果是 6，二进制: 0110

    printf("Result = %d\n", result);
    return 0;
}

```

在这个例子中，5（二进制0101）和3（二进制0011）进行异或运算的结果是6（二进制0110），因为每一位都被相应地比较并计算出结果。

## 位带操作

### 位带简介

Cortex-M3微控制器，作为ARM的Cortex-M系列的一部分，提供了位带（Bit-banding）功能，**这是一种允许对单个位进行原子读写操作的机制**。这种功能在需要精确控制或原子性操作单个位的场合非常有用，例如在多任务环境中操作共享资源。

在 CM3 中，有两个区中实现了位带。其中一个是 SRAM 区的最低 1MB 范围，第二个则是片内外设区的最低 1MB 范围。这两个位带中的地址除了可以像普通的 RAM 一样使用外，**它们还都有自己的“位带别名区”，位带别名区把每个比特膨胀成一个 32 位的字**。

![位带地址](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401021935413.png)

在CM3权威指南CnR2中**支持位带操作的两个内存区的范围**如下

![内存区范围](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401021941642.png)

### 位带操作的原理

位带操作在Cortex-M3中是**通过将一个较大的地址空间（位带区域）映射到一个较小的地址空间（位带别名区域）来实现的**。在Cortex-M3中，有两个主要的位带区域：

1. SRAM位带区域：通常用于内存中的变量。
2. 外设位带区域：用于外设寄存器。

每个位带区域的一个字（32位）对应主存储区的一个位。这意味着，通过写入位带区域的地址，你可以设置或清除主存储区相应位的值。

### 位带操作的地址映射

位带操作的地址映射通常遵循以下规则：

位带别名地址 = 位带基地址 + (字节偏移量 x 32) + (位编号 x 4)

其中，**字节偏移量是目标地址相对于位带区域基地址的偏移量**，**位编号是要操作的位**。

### 位带操作的示例

假设有一个外设寄存器的地址为 0x40000000，我们要设置这个寄存器的第2位。首先，我们需要计算这个位在位带别名区域中的地址。

假设外设位带区域的基地址是 0x42000000，那么：

- 字节偏移量 = 0x40000000 - 0x40000000 = 0x00000000
- 位编号 = 2
- 位带别名地址 = 0x42000000 + (0x00000000 x 32) + (2 x 4) = 0x42000008

然后，你可以直接写入这个位带别名地址来设置或清除该位：

```c
#define BITBAND_PERIPH(address, bit) ((void*)(0x42000000 + ((address) - 0x40000000) * 32 + (bit) * 4))

unsigned int *alias_address = (unsigned int *)BITBAND_PERIPH(0x40000000, 2);
*alias_address = 1;  // 设置第2位, 将第二位值设置为1
```

### 位带操作的注意事项

- 硬件支持：确保你的Cortex-M3微控制器支持位带操作。
- 地址计算：正确的地址计算对于位带操作至关重要。
- 原子操作：位带操作是原子的，这意味着在多任务或中断驱动的环境中，它们是安全的。

### 使用位带操作实现GPIO的输出和输入

项目地址: **14-位带操作-GPIO的输出和输入**

使用位带操作实现GPIO输出: LED_B的闪烁

#### 在main.c中添加位带操作的宏定义

```c
#define GPIOB_ODR_Addr (GPIOB_BASE+0x0C)
#define PBout(n) *(unsigned int*)((GPIOB_ODR_Addr&0xF0000000) + 0x02000000 + ((GPIOB_ODR_Addr&0x00FFFFFF)<<5)+(n<<2))
```

#### 在main.c中使用位带操作点灯

```c
while(1)
{
    PBout(1) = 1;
    Delay(0xFFF); // 延时
    PBout(1) = 0;
    Delay(0xFFF); // 延时
}
```

使用位带操作实现GPIO输入: KEY1和KEY2控制LED_B状态翻转

#### 在bsp_key.h中添加KEY2的宏定义

```c
#define KEY2_GPIO_PIN GPIO_Pin_13 // stm32f10x_gpio.h中定义
#define KEY2_GPIO_PORT GPIOC // stm32f10x.h中定义 
#define KEY2_GPIO_CLK RCC_APB2Periph_GPIOC
```

#### 在bsp.c中增加KEY2的GPIO初始化

```c
void KEY_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    // KEY1 初始化
    RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK, ENABLE);
    GPIO_InitStruct.GPIO_Pin = KEY1_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStruct);

    // KEY2 初始化
    RCC_APB2PeriphClockCmd(KEY2_GPIO_CLK, ENABLE);
    GPIO_InitStruct.GPIO_Pin = KEY2_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStruct);
}
```

#### 在main.c中添加GPIO输入位带操作的宏定义

```c
#define GPIOA_IDR_Addr (GPIOA_BASE+0x08)
#define GPIOC_IDR_Addr (GPIOC_BASE+0x08)
#define PAin(n) *(unsigned int*)((GPIOA_IDR_Addr&0xF0000000) + 0x02000000 + ((GPIOA_IDR_Addr&0x00FFFFFF)<<5)+(n<<2))
#define PCin(n) *(unsigned int*)((GPIOC_IDR_Addr&0xF0000000) + 0x02000000 + ((GPIOC_IDR_Addr&0x00FFFFFF)<<5)+(n<<2))
```

#### 在main.c中测试LED闪烁

```c
while(1)
{
    if(PAin(0) == KEY_ON)
    {
        Delay(0xFFF); // 加入软件消抖后可正常运行
        while(PAin(0) == KEY_ON) // 等待按键释放
        {
            ;
        }
        LED_B_TOGGLE;
    }

    if(PCin(13) == KEY_ON)
    {
        Delay(0xFFF); // 加入软件消抖后可正常运行
        while(PCin(13) == KEY_ON) // 等待按键释放
        {
            ;
        }
        LED_B_TOGGLE;
    }
}
```

## 启动文件详解

```assembly
;******************** (C) COPYRIGHT 2011 STMicroelectronics ********************
;* File Name          : startup_stm32f10x_hd.s
;* Author             : MCD Application Team
;* Version            : V3.5.0
;* Date               : 11-March-2011
;* Description        : STM32F10x High Density Devices vector table for MDK-ARM 
;*                      toolchain. 
;*                      This module performs:
;*                      - Set the initial SP 
;                       初始化堆栈指针
;*                      - Set the initial PC == Reset_Handler 
;                       初始化PC指针 == Reset_Handler程序
;*                      - Set the vector table entries with the exceptions ISR address 
;                       初始化中断向量表
;*                      - Configure the clock system and also configure the external 
;*                        SRAM mounted on STM3210E-EVAL board to be used as data 
;*                        memory (optional, to be enabled by user) 
;                       配置系统时钟
;*                      - Branches to __main in the C library (which eventually
;*                        calls main()). 
;                       调用C库函数, 最终去到C的世界
;*                      After Reset the CortexM3 processor is in Thread mode,
;*                      priority is Privileged, and the Stack is set to Main.
;* <<< Use Configuration Wizard in Context Menu >>>   
;*******************************************************************************
; THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
; WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
; AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
; INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
; CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
; INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
;*******************************************************************************

;****************************************************************************
;* 1- 栈的配置
;****************************************************************************

; Amount of memory (in bytes) allocated for Stack
; Tailor this value to your application needs
; <h> Stack Configuration 
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>
; 配置栈: 用于变量存储(局部/全局), 函数调用

Stack_Size      EQU     0x00000400 
; 宏定义的伪指令，相当于等于，类似与 C 中的 define。
; 将0x00000400命名为Stack_Size, 0x00000400表示1Kb大小

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
                ; 告诉汇编器汇编一个新的代码段或者数据段。
                ; STACK 表示段名，这个可以任意命名
                ; NOINIT 表示不初始化
                ; READWRITE 表示可读可写
                ; ALIGN=3，表示按照 2^3 对齐，即 8 字节对齐
Stack_Mem       SPACE   Stack_Size
__initial_sp
; SPACE：用于分配一定大小的内存空间，单位为字节。这里指定大小等于 Stack_Size。
; 标号 __initial_sp 紧挨着 SPACE 语句放置，表示栈的结束地址，即栈顶地址，栈是由高向低生长
的。 
                                                  
;****************************************************************
;* 2-堆的配置
;****************************************************************

; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>
; 配置堆: 主要用于动态内存的分配, 如malloc()函数

Heap_Size       EQU     0x00000200
; 将0x00000200命名为Heap_Size, 0x00000200为512Type

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
                ; 汇编数据段
                ; 名字叫HEAP
                ; 不初始化
                ; 可读可写
                ; 2^3即8字节对齐
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit
; __heap_base 表示对的起始地址
; SPACE 分配大小为Heap_Size即512字节的内存空间
; __heap_limit 表示堆的结束地址
; 堆是由低向高生长的，跟栈的生长方向相反。

                PRESERVE8
                ; 指定当前文件的堆栈按照 8 字节对齐
                THUMB
                ; 表示后面指令兼容 THUMB 指令

;****************************************************************
;* 3-初始化中断向量表
;****************************************************************

; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                ; 区域名称为RESET
                ; 区域类型为DATA, 与CODE相对,后者用于包含可执行指令
                ; 区域属性为只读
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size
                ; EXPORT声明标号__Vectors等具有全局属性, 可被外部的文件调用

__Vectors       DCD     __initial_sp               ; Top of Stack ; 栈顶地址
                DCD     Reset_Handler              ; Reset Handler ; 复位程序地址
                DCD     NMI_Handler                ; NMI Handler
                DCD     HardFault_Handler          ; Hard Fault Handler
                DCD     MemManage_Handler          ; MPU Fault Handler
                DCD     BusFault_Handler           ; Bus Fault Handler
                DCD     UsageFault_Handler         ; Usage Fault Handler
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     SVC_Handler                ; SVCall Handler
                DCD     DebugMon_Handler           ; Debug Monitor Handler
                DCD     0                          ; Reserved
                DCD     PendSV_Handler             ; PendSV Handler
                DCD     SysTick_Handler            ; SysTick Handler

                ; External Interrupts
                DCD     WWDG_IRQHandler            ; Window Watchdog
                DCD     PVD_IRQHandler             ; PVD through EXTI Line detect
                DCD     TAMPER_IRQHandler          ; Tamper
                DCD     RTC_IRQHandler             ; RTC
                DCD     FLASH_IRQHandler           ; Flash
                DCD     RCC_IRQHandler             ; RCC
                DCD     EXTI0_IRQHandler           ; EXTI Line 0
                DCD     EXTI1_IRQHandler           ; EXTI Line 1
                DCD     EXTI2_IRQHandler           ; EXTI Line 2
                DCD     EXTI3_IRQHandler           ; EXTI Line 3
                DCD     EXTI4_IRQHandler           ; EXTI Line 4
                DCD     DMA1_Channel1_IRQHandler   ; DMA1 Channel 1
                DCD     DMA1_Channel2_IRQHandler   ; DMA1 Channel 2
                DCD     DMA1_Channel3_IRQHandler   ; DMA1 Channel 3
                DCD     DMA1_Channel4_IRQHandler   ; DMA1 Channel 4
                DCD     DMA1_Channel5_IRQHandler   ; DMA1 Channel 5
                DCD     DMA1_Channel6_IRQHandler   ; DMA1 Channel 6
                DCD     DMA1_Channel7_IRQHandler   ; DMA1 Channel 7
                DCD     ADC1_2_IRQHandler          ; ADC1 & ADC2
                DCD     USB_HP_CAN1_TX_IRQHandler  ; USB High Priority or CAN1 TX
                DCD     USB_LP_CAN1_RX0_IRQHandler ; USB Low  Priority or CAN1 RX0
                DCD     CAN1_RX1_IRQHandler        ; CAN1 RX1
                DCD     CAN1_SCE_IRQHandler        ; CAN1 SCE
                DCD     EXTI9_5_IRQHandler         ; EXTI Line 9..5
                DCD     TIM1_BRK_IRQHandler        ; TIM1 Break
                DCD     TIM1_UP_IRQHandler         ; TIM1 Update
                DCD     TIM1_TRG_COM_IRQHandler    ; TIM1 Trigger and Commutation
                DCD     TIM1_CC_IRQHandler         ; TIM1 Capture Compare
                DCD     TIM2_IRQHandler            ; TIM2
                DCD     TIM3_IRQHandler            ; TIM3
                DCD     TIM4_IRQHandler            ; TIM4
                DCD     I2C1_EV_IRQHandler         ; I2C1 Event
                DCD     I2C1_ER_IRQHandler         ; I2C1 Error
                DCD     I2C2_EV_IRQHandler         ; I2C2 Event
                DCD     I2C2_ER_IRQHandler         ; I2C2 Error
                DCD     SPI1_IRQHandler            ; SPI1
                DCD     SPI2_IRQHandler            ; SPI2
                DCD     USART1_IRQHandler          ; USART1
                DCD     USART2_IRQHandler          ; USART2
                DCD     USART3_IRQHandler          ; USART3
                DCD     EXTI15_10_IRQHandler       ; EXTI Line 15..10
                DCD     RTCAlarm_IRQHandler        ; RTC Alarm through EXTI Line
                DCD     USBWakeUp_IRQHandler       ; USB Wakeup from suspend
                DCD     TIM8_BRK_IRQHandler        ; TIM8 Break
                DCD     TIM8_UP_IRQHandler         ; TIM8 Update
                DCD     TIM8_TRG_COM_IRQHandler    ; TIM8 Trigger and Commutation
                DCD     TIM8_CC_IRQHandler         ; TIM8 Capture Compare
                DCD     ADC3_IRQHandler            ; ADC3
                DCD     FSMC_IRQHandler            ; FSMC
                DCD     SDIO_IRQHandler            ; SDIO
                DCD     TIM5_IRQHandler            ; TIM5
                DCD     SPI3_IRQHandler            ; SPI3
                DCD     UART4_IRQHandler           ; UART4
                DCD     UART5_IRQHandler           ; UART5
                DCD     TIM6_IRQHandler            ; TIM6
                DCD     TIM7_IRQHandler            ; TIM7
                DCD     DMA2_Channel1_IRQHandler   ; DMA2 Channel1
                DCD     DMA2_Channel2_IRQHandler   ; DMA2 Channel2
                DCD     DMA2_Channel3_IRQHandler   ; DMA2 Channel3
                DCD     DMA2_Channel4_5_IRQHandler ; DMA2 Channel4 & Channel5
__Vectors_End
; _Vectors 为向量表起始地址，__Vectors_End 为向量表结束地址
; 向量表中，DCD 分配了一堆内存，并且以 ESR 的入口地址初始化它们 

__Vectors_Size  EQU  __Vectors_End - __Vectors
; 向量表的大小为结束地址减去起始地址

                AREA    |.text|, CODE, READONLY
                ; 定义一个名称为.text 的代码段，只读
                
;****************************************************************
;* 4-复位程序
;****************************************************************

; Reset handler
Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                ; WEAK 表示弱定义, 如果在其他地方定义了Reset_Handler就使用其他地方的定义
                ; 可以理解为C++中的"可以重载"
                IMPORT  __main
                IMPORT  SystemInit
                ;表示 SystemInit和 __main 这两个函数均来自外部的文件

                LDR     R0, =SystemInit
                ; 把SystemInit的地址加载到R0中
                BLX     R0               
                ; 跳转到R0执行, 执行完毕后返回
                LDR     R0, =__main
                ; 把__main的地址加载到R0中
                BX      R0
                ; 跳转到R0执行, 执行完毕后不返回
                ENDP
                
;****************************************************************
;* 5-中断服务函数
;****************************************************************

; Dummy Exception Handlers (infinite loops which can be modified)
; 中断服务函数均跳转到无限循环
; 目的是用户在未定义中断服务函数的情况下调用可进入无限循环状态中(兜底作用)

NMI_Handler     PROC
                EXPORT  NMI_Handler                [WEAK]
                B       .
                ; B 表示跳转指令
                ; . 表示无限循环
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler          [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler          [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler           [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler           [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler             [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler            [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  WWDG_IRQHandler            [WEAK]
                EXPORT  PVD_IRQHandler             [WEAK]
                EXPORT  TAMPER_IRQHandler          [WEAK]
                EXPORT  RTC_IRQHandler             [WEAK]
                EXPORT  FLASH_IRQHandler           [WEAK]
                EXPORT  RCC_IRQHandler             [WEAK]
                EXPORT  EXTI0_IRQHandler           [WEAK]
                EXPORT  EXTI1_IRQHandler           [WEAK]
                EXPORT  EXTI2_IRQHandler           [WEAK]
                EXPORT  EXTI3_IRQHandler           [WEAK]
                EXPORT  EXTI4_IRQHandler           [WEAK]
                EXPORT  DMA1_Channel1_IRQHandler   [WEAK]
                EXPORT  DMA1_Channel2_IRQHandler   [WEAK]
                EXPORT  DMA1_Channel3_IRQHandler   [WEAK]
                EXPORT  DMA1_Channel4_IRQHandler   [WEAK]
                EXPORT  DMA1_Channel5_IRQHandler   [WEAK]
                EXPORT  DMA1_Channel6_IRQHandler   [WEAK]
                EXPORT  DMA1_Channel7_IRQHandler   [WEAK]
                EXPORT  ADC1_2_IRQHandler          [WEAK]
                EXPORT  USB_HP_CAN1_TX_IRQHandler  [WEAK]
                EXPORT  USB_LP_CAN1_RX0_IRQHandler [WEAK]
                EXPORT  CAN1_RX1_IRQHandler        [WEAK]
                EXPORT  CAN1_SCE_IRQHandler        [WEAK]
                EXPORT  EXTI9_5_IRQHandler         [WEAK]
                EXPORT  TIM1_BRK_IRQHandler        [WEAK]
                EXPORT  TIM1_UP_IRQHandler         [WEAK]
                EXPORT  TIM1_TRG_COM_IRQHandler    [WEAK]
                EXPORT  TIM1_CC_IRQHandler         [WEAK]
                EXPORT  TIM2_IRQHandler            [WEAK]
                EXPORT  TIM3_IRQHandler            [WEAK]
                EXPORT  TIM4_IRQHandler            [WEAK]
                EXPORT  I2C1_EV_IRQHandler         [WEAK]
                EXPORT  I2C1_ER_IRQHandler         [WEAK]
                EXPORT  I2C2_EV_IRQHandler         [WEAK]
                EXPORT  I2C2_ER_IRQHandler         [WEAK]
                EXPORT  SPI1_IRQHandler            [WEAK]
                EXPORT  SPI2_IRQHandler            [WEAK]
                EXPORT  USART1_IRQHandler          [WEAK]
                EXPORT  USART2_IRQHandler          [WEAK]
                EXPORT  USART3_IRQHandler          [WEAK]
                EXPORT  EXTI15_10_IRQHandler       [WEAK]
                EXPORT  RTCAlarm_IRQHandler        [WEAK]
                EXPORT  USBWakeUp_IRQHandler       [WEAK]
                EXPORT  TIM8_BRK_IRQHandler        [WEAK]
                EXPORT  TIM8_UP_IRQHandler         [WEAK]
                EXPORT  TIM8_TRG_COM_IRQHandler    [WEAK]
                EXPORT  TIM8_CC_IRQHandler         [WEAK]
                EXPORT  ADC3_IRQHandler            [WEAK]
                EXPORT  FSMC_IRQHandler            [WEAK]
                EXPORT  SDIO_IRQHandler            [WEAK]
                EXPORT  TIM5_IRQHandler            [WEAK]
                EXPORT  SPI3_IRQHandler            [WEAK]
                EXPORT  UART4_IRQHandler           [WEAK]
                EXPORT  UART5_IRQHandler           [WEAK]
                EXPORT  TIM6_IRQHandler            [WEAK]
                EXPORT  TIM7_IRQHandler            [WEAK]
                EXPORT  DMA2_Channel1_IRQHandler   [WEAK]
                EXPORT  DMA2_Channel2_IRQHandler   [WEAK]
                EXPORT  DMA2_Channel3_IRQHandler   [WEAK]
                EXPORT  DMA2_Channel4_5_IRQHandler [WEAK]

WWDG_IRQHandler
PVD_IRQHandler
TAMPER_IRQHandler
RTC_IRQHandler
FLASH_IRQHandler
RCC_IRQHandler
EXTI0_IRQHandler
EXTI1_IRQHandler
EXTI2_IRQHandler
EXTI3_IRQHandler
EXTI4_IRQHandler
DMA1_Channel1_IRQHandler
DMA1_Channel2_IRQHandler
DMA1_Channel3_IRQHandler
DMA1_Channel4_IRQHandler
DMA1_Channel5_IRQHandler
DMA1_Channel6_IRQHandler
DMA1_Channel7_IRQHandler
ADC1_2_IRQHandler
USB_HP_CAN1_TX_IRQHandler
USB_LP_CAN1_RX0_IRQHandler
CAN1_RX1_IRQHandler
CAN1_SCE_IRQHandler
EXTI9_5_IRQHandler
TIM1_BRK_IRQHandler
TIM1_UP_IRQHandler
TIM1_TRG_COM_IRQHandler
TIM1_CC_IRQHandler
TIM2_IRQHandler
TIM3_IRQHandler
TIM4_IRQHandler
I2C1_EV_IRQHandler
I2C1_ER_IRQHandler
I2C2_EV_IRQHandler
I2C2_ER_IRQHandler
SPI1_IRQHandler
SPI2_IRQHandler
USART1_IRQHandler
USART2_IRQHandler
USART3_IRQHandler
EXTI15_10_IRQHandler
RTCAlarm_IRQHandler
USBWakeUp_IRQHandler
TIM8_BRK_IRQHandler
TIM8_UP_IRQHandler
TIM8_TRG_COM_IRQHandler
TIM8_CC_IRQHandler
ADC3_IRQHandler
FSMC_IRQHandler
SDIO_IRQHandler
TIM5_IRQHandler
SPI3_IRQHandler
UART4_IRQHandler
UART5_IRQHandler
TIM6_IRQHandler
TIM7_IRQHandler
DMA2_Channel1_IRQHandler
DMA2_Channel2_IRQHandler
DMA2_Channel3_IRQHandler
DMA2_Channel4_5_IRQHandler
                B       .

                ENDP

                ALIGN
                ; ALIGN 表示4字节对齐(参数缺省时)

;****************************************************************
;* 6-堆栈的初始化, 由C库函数__main实现
;****************************************************************

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************
                 IF      :DEF:__MICROLIB ; __MICROLIB在ide里定义, 在Keil5 MDK中勾选Use MicroLIB选项
                
                 EXPORT  __initial_sp
                 EXPORT  __heap_base
                 EXPORT  __heap_limit
                
                 ELSE
                
                 IMPORT  __use_two_region_memory ; 如果__MICROLIB未定义, 则由用户自己实现
                 EXPORT  __user_initial_stackheap
                 
__user_initial_stackheap

                 LDR     R0, =  Heap_Mem
                 LDR     R1, =(Stack_Mem + Stack_Size)
                 LDR     R2, = (Heap_Mem +  Heap_Size)
                 LDR     R3, = Stack_Mem
                 BX      LR

                 ALIGN

                 ENDIF

                 END

;******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE*****

```

### EQU指令

作用: The EQU directive is a register-relative address, a PC-relative address, an absolute address, or a 32-bit integer constant. // 为数值常量、寄存器相对值或 PC 相对值提供符号名称。(*可以理解为重命名*)

```assembly
Stack_Size      EQU     0x00000400 
; 宏定义的伪指令，相当于等于，类似与 C 中的 define。
; 将0x00000400命名为Stack_Size, 0x00000400表示1Kb大小
```

#### EQU手册说明

![EQU指令](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401031428875.png)

### AREA指令

AREA: 汇编一个新的代码段或数据段

```assembly
AREA    STACK, NOINIT, READWRITE, ALIGN=3
; 告诉汇编器汇编一个新的代码段或者数据段。
; STACK 表示段名，这个可以任意命名
; NOINIT 表示不初始化
; READWRITE 表示可读可写
; ALIGN=3，表示按照 2^3 对齐，即 8 字节对齐
```

#### AREA手册说明

![AREA](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401031529274.png)

![AREA](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401031530123.png)

![AREA](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401031530696.png)

![AREA](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401031531689.png)

### SPACE指令

SPACE：用于分配一定大小的内存空间，单位为字节。这里指定大小等于 Stack_Size, 标号 __initial_sp 紧挨着 SPACE 语句放置，表示栈的结束地址，即栈顶地址，栈是由高向低生长

```assembly
Stack_Mem       SPACE   Stack_Size
; SPACE：用于分配一定大小的内存空间，单位为字节。这里指定大小等于 Stack_Size。
__initial_sp
; 标号 __initial_sp 紧挨着 SPACE 语句放置，表示栈的结束地址，即栈顶地址，栈是由高向低生长
```

#### SPACE手册说明

![SPACE](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401031539781.png)

### PRESERVE8指令

PRESERVE8：指定当前文件的堆栈按照 8 字节对齐

#### PRESERVE8手册说明

![PRESERVE8](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401031556307.png)

![PRESERVE8](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401031557775.png)

### THUMB指令

野火的解释: **THUMB：表示后面指令兼容 THUMB 指令。THUBM 是 ARM 以前的指令集，16bit，现在 Cortex-M系列的都使用 THUMB-2 指令集，THUMB-2 是 32 位的，兼容 16 位和 32 位的指令，是 THUMB的超集**

#### THUMB手册说明

![THUMB](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401031600256.png)

### EXPORT指令

EXPORT：声明一个标号可被外部的文件使用，使标号具有全局属性。如果是 IAR 编译器，则使用的是 GLOBAL 这个指令

```assembly
EXPORT  __Vectors
EXPORT  __Vectors_End
EXPORT  __Vectors_Size
; EXPORT声明标号__Vectors等具有全局属性, 可被外部的文件调用
```

#### EXPORT手册说明

![EXPORT](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401031623174.png)

![EXPORT](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401031624509.png)

![EXPORT](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401031624882.png)

### DCD指令

DCD：分配一个或者多个以字为单位的内存，以四字节对齐，并要求初始化这些内存

#### DCD手册说明

![DCD](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401032016385.png)

### PROC指令

PROC: 定义子程序, 与ENDP成对使用, 表示子程序结束

#### PROC手册说明

![PROC](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401032025440.png)

![PROC](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401032026200.png)

### IMPORT指令

IMPORT：表示该标号来自外部文件，跟 C 语言中的 EXTERN 关键字类似

```assembly
IMPORT  __main
IMPORT  SystemInit
;表示 SystemInit和 __main 这两个函数均来自外部的文件
```

#### IMPORT手册说明

![IMPORT](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401032034894.png)

![IMPORT](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401032034604.png)

![IMPORT](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401032035341.png)

### LDR指令

LDR: 从存储器中加载字到一个寄存器中

```assembly
LDR     R0, =SystemInit
; 把SystemInit的地址加载到R0中
BLX     R0               
; 跳转到R0执行, 执行完毕后返回
LDR     R0, =__main
; 把__main的地址加载到R0中
BX      R0
; 跳转到R0执行, 执行完毕后不返回
```

#### LDR手册说明

![LDR](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401032046548.png)

![LDR](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401032046349.png)

![LDR](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401032047305.png)

### BLX指令

BLX: 跳转到由寄存器给出的地址, 并根据寄存器的LSE确定处理器的状态, 还要把跳转前的下条指令地址保存到LR

```assembly
BLX     R0               
; 跳转到R0执行, 执行完毕后返回
```

### BX指令

BX: 跳转到由寄存器/标号给出的地址, 不用返回

```assembly
BX      R0
; 跳转到R0执行, 执行完毕后不返回
```

### ALIGN指令

ALIGN：对指令或者数据存放的地址进行对齐，后面会跟一个立即数。缺省表示 4 字节对齐

#### ALIGN手册说明

![ALIGN](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401032103293.png)

![ALIGN](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401032103739.png)

![ALIGN](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401032103256.png)

## 时钟

### 时钟系统框图

![时钟系统框图](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/%E6%88%AA%E5%B1%8F2024-01-04%2009.47.02.png)

#### SYSCLK系统时钟源选择

- HSI_RC: 高速内部时钟, RC 震荡产生(频率约为 8MHz)
- HSE: 高速外部时钟,通过外接晶振产生(频率范围: 4-16MHz)
- PLL: 锁相环,倍频到72MHz

##### SYSCLK 系统时钟的选择

1. HSI_RC 约 8MHz
2. PLLCLK 倍频至72MHz
3. HSE_Osc直接使用

##### PLL锁相环的选择

1. HSI_RC 两分频后
2. HSE_Osc or HSE_Osc二分频后

CSS: 时钟监视系统, 监视 HSE_Osc 是否正常工作,若 外部时钟源异常则将 SYSCLK 切换为 HSI_RC

![时钟系统框图](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/%E6%88%AA%E5%B1%8F2024-01-04%2010.03.07.png)

#### RTCCLK时钟源选择

- LSE_Osc: 低速外部时钟源, 频率为36.768KHz
- LSI_RC: 低速内部时钟源, 频率约为40KHz, 由 RC 震荡产生

##### RTC_CLK(RTC 时钟)的选择

1. HSE_Osc 128 分频后
2. LSE_Osc
3. LSI_RC

#### IWDGCLK独立看门狗时钟源

IWDGCLK独立看门狗时钟源由LSI_RC 提供

![IWDGCLK独立看门狗时钟源](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401291156077.png)

#### MCO 的选择

MCO是一个引脚来输出内部时钟

![系统时钟框图](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/%E6%88%AA%E5%B1%8F2024-01-04%2010.13.53.png)

1. SYSCLK
2. HSI
3. HSE
4. PLLCLK 二分频

#### 各类总线时钟

![时钟系统框图](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/%E6%88%AA%E5%B1%8F2024-01-04%2010.26.21.png)

1. USBCLK_48MHz (USB 时钟): 由 PLLCLK经USB_Prescaler预分频至 48MHz
2. HCLK: SYSCLK->AHB_Prescaler 最高 72MHz
3. PCLK1: SYSCLK->AHB_Prescaler->APB1_Prescaler 最高36MHz
4. TIMxCLK(通用定时器时钟): SYSCLK->AHB_Prescaler->APB1_Prescaler->TIM2,3,4_Multiplier
5. PCKL2: SYSCLK->AHB_Prescaler->APB2_Prescaler 最高72MHz
6. TIM1CLK(TIM1 时钟): SYSCLK->AHB_Prescal->APB2_Prescaler->TIM1_Multiplier
7. ADCCLK(ADC 时钟): SYSCLK->AHB_Prescaler->APB2_Prescaler->ADC_Prescaler

#### 总结

![知识总结](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/%E6%88%AA%E5%B1%8F2024-01-04%2011.09.39.png)

### 系统时钟配置函数 SetSysClockTo72()分析

在启动文件startup_stm32f10x_hd.s中执行SystemInit函数, 如下

```assembly
; Reset handler
Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  __main
                IMPORT  SystemInit
                LDR     R0, =SystemInit
                BLX     R0               
                LDR     R0, =__main
                BX      R0
                ENDP
```

在system_stm32f10x.c文件中调用SystemInit函数, SystemInit函数在末尾调用SetSysClock()函数

```c
void SystemInit (void)
{
  /* Reset the RCC clock configuration to the default reset state(for debug purpose) */
  /* Set HSION bit */
  RCC->CR |= (uint32_t)0x00000001;

  /* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
#ifndef STM32F10X_CL
  RCC->CFGR &= (uint32_t)0xF8FF0000;
#else
  RCC->CFGR &= (uint32_t)0xF0FF0000;
#endif /* STM32F10X_CL */   
  
  /* Reset HSEON, CSSON and PLLON bits */
  RCC->CR &= (uint32_t)0xFEF6FFFF;

  /* Reset HSEBYP bit */
  RCC->CR &= (uint32_t)0xFFFBFFFF;

  /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
  RCC->CFGR &= (uint32_t)0xFF80FFFF;

#ifdef STM32F10X_CL
  /* Reset PLL2ON and PLL3ON bits */
  RCC->CR &= (uint32_t)0xEBFFFFFF;

  /* Disable all interrupts and clear pending bits  */
  RCC->CIR = 0x00FF0000;

  /* Reset CFGR2 register */
  RCC->CFGR2 = 0x00000000;
#elif defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL) || (defined STM32F10X_HD_VL)
  /* Disable all interrupts and clear pending bits  */
  RCC->CIR = 0x009F0000;

  /* Reset CFGR2 register */
  RCC->CFGR2 = 0x00000000;      
#else
  /* Disable all interrupts and clear pending bits  */
  RCC->CIR = 0x009F0000;
#endif /* STM32F10X_CL */
    
#if defined (STM32F10X_HD) || (defined STM32F10X_XL) || (defined STM32F10X_HD_VL)
  #ifdef DATA_IN_ExtSRAM
    SystemInit_ExtMemCtl(); 
  #endif /* DATA_IN_ExtSRAM */
#endif 

  /* Configure the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers */
  /* Configure the Flash Latency cycles and enable prefetch buffer */
  SetSysClock(); // 末尾调用SetSysClock()函数 
```

调用system_stm32f10x.c中SetSysClock()

默认情况下定义SYSCLK_FREQ_72MHz宏, 调用SetSysClockTo72()函数

```c
/**
  * @brief  Configures the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers.
  * @param  None
  * @retval None
  */
static void SetSysClock(void)
{
#ifdef SYSCLK_FREQ_HSE
  SetSysClockToHSE();
#elif defined SYSCLK_FREQ_24MHz
  SetSysClockTo24();
#elif defined SYSCLK_FREQ_36MHz
  SetSysClockTo36();
#elif defined SYSCLK_FREQ_48MHz
  SetSysClockTo48();
#elif defined SYSCLK_FREQ_56MHz
  SetSysClockTo56();  
#elif defined SYSCLK_FREQ_72MHz
  SetSysClockTo72();
#endif
 
 /* If none of the define above is enabled, the HSI is used as System clock
    source (default after reset) */ 
}
```

在system_stm32f10x.c中宏定义, 默认宏定义SYSTEMCLK_FREQ_72MHz

```c
#if defined (STM32F10X_LD_VL) || (defined STM32F10X_MD_VL) || (defined STM32F10X_HD_VL)
/* #define SYSCLK_FREQ_HSE    HSE_VALUE */
 #define SYSCLK_FREQ_24MHz  24000000
#else
/* #define SYSCLK_FREQ_HSE    HSE_VALUE */
/* #define SYSCLK_FREQ_24MHz  24000000 */ 
/* #define SYSCLK_FREQ_36MHz  36000000 */
/* #define SYSCLK_FREQ_48MHz  48000000 */
/* #define SYSCLK_FREQ_56MHz  56000000 */
#define SYSCLK_FREQ_72MHz  72000000
#endif
```

在system_stem32f10x.c中定义SetSysClockTo72()函数

```c
#elif defined SYSCLK_FREQ_72MHz
/**
  * @brief  Sets System clock frequency to 72MHz and configure HCLK, PCLK2 
  *         and PCLK1 prescalers. 
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo72(void)
{
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
  
  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/    
  /* Enable HSE */    
  // 使能HSE
  RCC->CR |= ((uint32_t)RCC_CR_HSEON);
  
 
  /* Wait till HSE is ready and if Time out is reached exit */
  // 等待 HSE 就绪并作超时处理
  do
  {
    HSEStatus = RCC->CR & RCC_CR_HSERDY;
    StartUpCounter++;  
  } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

  if ((RCC->CR & RCC_CR_HSERDY) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }  

  // 如果 HSE启动成功, 程序则继续往下执行
  if (HSEStatus == (uint32_t)0x01)
  {
    /* Enable Prefetch Buffer */
    // 启用 Flsh  预取缓冲区
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 2 wait state */
    // flash 时延两个等待状态
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;    

 
    /* HCLK = SYSCLK */
    // 72MHz
    RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
      
    /* PCLK2 = HCLK */
    // 72MHz
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
    
    /* PCLK1 = HCLK */
    // 36MHz
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;

/*----------------------------------------------------------------
 * 互联型芯片 F105, F107 以下代码不进行分析
 *---------------------------------------------------------------*/

/**********************************************************************/
#ifdef STM32F10X_CL
    /* Configure PLLs ------------------------------------------------------*/
    /* PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz */
    /* PREDIV1 configuration: PREDIV1CLK = PLL2 / 5 = 8 MHz */
        
    RCC->CFGR2 &= (uint32_t)~(RCC_CFGR2_PREDIV2 | RCC_CFGR2_PLL2MUL |
                              RCC_CFGR2_PREDIV1 | RCC_CFGR2_PREDIV1SRC);
    RCC->CFGR2 |= (uint32_t)(RCC_CFGR2_PREDIV2_DIV5 | RCC_CFGR2_PLL2MUL8 |
                             RCC_CFGR2_PREDIV1SRC_PLL2 | RCC_CFGR2_PREDIV1_DIV5);
  
    /* Enable PLL2 */
    RCC->CR |= RCC_CR_PLL2ON;
    /* Wait till PLL2 is ready */
    while((RCC->CR & RCC_CR_PLL2RDY) == 0)
    {
    }
    
   
    /* PLL configuration: PLLCLK = PREDIV1 * 9 = 72 MHz */ 
    // 锁相环配置
    RCC->CFGR &= (uint32_t)~(RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL);
    RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLXTPRE_PREDIV1 | RCC_CFGR_PLLSRC_PREDIV1 | 
                            RCC_CFGR_PLLMULL9); 
#else    

    /* Enable PLL */
    // 使能 PLL
    RCC->CR |= RCC_CR_PLLON;

    /* Wait till PLL is ready */
    //  等待 PLL 稳定
    while((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
    }
    
    /* Select PLL as system clock source */
    // 选择 PLLCLK 作为系统时钟
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    

    /* Wait till PLL is used as system clock source */
    // 等待 PLLCLK 切换为系统时钟
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08)
    {
    }
  }
  else
  { /* If HSE fails to start-up, the application will have wrong clock 
         configuration. User can add here some code to deal with this error */
    // 如果 HSE 启动失败,用户可以在这里添加处理错误的代码
  }
}
#endif
```

### HSE配置系统时钟

项目地址: **16-使用HSE配置系统时钟并使用MCO输出监控系统时钟**

#### 在bsp_rccclkconfig.c中写入HSE的配置函数

```c
/**
 * @brief 设置系统时钟为外部高速晶振（HSE）时钟，并配置PLL倍频系数。
 * 
 * @param RCC_PLLMul_x PLL倍频系数，范围为2-16。
 * @note 该函数会将RCC模块复位，并使能HSE。如果HSE启动成功，则设置FLASH预取指令使能、FLASH等待周期、AHB总线时钟、APB1总线时钟、APB2总线时钟、PLL倍频系数，并等待PLL稳定后将系统时钟设置为PLL时钟。
 *       如果HSE启动失败，则用户可以在函数中添加处理错误的代码。
 */
void HSE_SetSysClk(uint32_t RCC_PLLMul_x)
{
    RCC_DeInit(); // RCC复位
    ErrorStatus HSEStatus;
    RCC_HSEConfig(RCC_HSE_ON); // 使能HSE
    HSEStatus = RCC_WaitForHSEStartUp(); // 获取HSE启动状态

    if(HSEStatus == SUCCESS)
    {
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); // 使能预取指
        FLASH_SetLatency(FLASH_ACR_LATENCY_2); // 设置等待
        RCC_HCLKConfig(RCC_SYSCLK_Div1); //HCLK = SYSCLK = 72MHz
        RCC_PCLK1Config(RCC_SYSCLK_Div2); //PCLK1 = HCLK / 2 = 36MHz
        RCC_PCLK2Config(RCC_SYSCLK_Div1); //PCLK2 = HCLK / 1 = 72MHz
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_x); // RCC_RLLMul_x 用来超频 频率:(8*x)MHz
        RCC_PLLCmd(ENABLE); // 使能PLL
        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
        {
            // 等待PLL稳定
            ;
        }
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); // 设置系统时钟为PLL时钟
        while(RCC_GetSYSCLKSource() != 0x08)
        {
            // 等待设置系统时钟
            ;
        }
    }
    else
    {
        // 如果HSE启动失败, 用户在此添加处理错误代码
    }
}
```

#### 在bsp_rccclkconfig.c中编写MCO的GPIO初始化函数

```c
/**
 * @brief Configures the GPIO for MCO (Microcontroller Clock Output).
 * 
 * This function initializes the GPIO pin for MCO and configures it as an alternate function push-pull output.
 * The GPIO pin used for MCO is GPIOA Pin 8.
 * 
 * @param None
 * @return None
 */
void MCO_GPIO_Config()
{
    // MCO的GPIO初始化
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}
```

#### 在bsp_rccclkconfig.h中添加函数声明

```c
#ifndef __BSP_RCCCLKCONFIG_H
#define __BSP_RCCCLKCONFIG_H

#include "stm32f10x.h"

void HSE_SetSysClk(uint32_t RCC_PLLMul_x);
void MCO_GPIO_Config();

#endif // !__BSP_RCCCLKCONFIG_H
```

#### 在main.c中调用HSE配置系统时钟函数和MCO的GPIO初始化函数

```c
#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_rccclkconfig.h"

// 延时函数Delay()
void Delay(uint32_t count)
{
    uint32_t i = 0;
    for(; count != 0; count--)
    {
        for(i = 0; i < 0x2AFF; i++)
        {
            ;
        }
    }
}

int main(void)
{
    HSE_SetSysClk(RCC_PLLMul_9); // 72MHz
    // HSE_SetSysClk(RCC_PLLMul_16); // 128MHz
    MCO_GPIO_Config();
    RCC_MCOConfig(RCC_MCO_SYSCLK); // 配置MCO选择系统时钟
    LED_GPIO_Config();

    while(1)
    {
        LED_B(OFF);
        Delay(50); // 延时
        LED_B(ON);
        Delay(50); // 延时
    }
}

```

### 使用HSI配置系统时钟并用MCO监控系统时钟

项目地址: **16-使用HSI配置系统时钟并用MCO监控系统时钟**

#### 在bsp_rccclkconfig.c中编写HSI配置系统时钟函数

```c
/**
 * @brief 设置系统时钟为HSI，并配置PLL倍频系数
 * 
 * @param RCC_PLLMul_x PLL倍频系数，范围为2-16
 * 
 * @note 该函数将系统时钟设置为HSI，并根据传入的PLL倍频系数配置PLL，以实现超频功能。
 *       如果HSI启动失败，用户可以在函数的else分支中添加处理错误的代码。
 */
void HSI_SetSysClk(uint32_t RCC_PLLMul_x)
{
    // Function implementation
    __IO uint32_t HSIStatus = 0; // 参考固件库源码
    RCC_DeInit(); // RCC复位
    RCC_HSICmd(ENABLE); // 使能HSI
    HSIStatus = RCC->CR & RCC_CR_HSIRDY; // 获取HSI启动状态, 参考固件库源码

    if(HSIStatus == RCC_CR_HSIRDY)
    {
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); // 使能预取指
        FLASH_SetLatency(FLASH_ACR_LATENCY_2); // 设置等待
        RCC_HCLKConfig(RCC_SYSCLK_Div1); //HCLK = SYSCLK = 72MHz
        RCC_PCLK1Config(RCC_SYSCLK_Div2); //PCLK1 = HCLK / 2 = 36MHz
        RCC_PCLK2Config(RCC_SYSCLK_Div1); //PCLK2 = HCLK / 1 = 72MHz
        RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_x); // RCC_RLLMul_x 用来超频 频率:(8*x)MHz
        RCC_PLLCmd(ENABLE); // 使能PLL
        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
        {
            // 等待PLL稳定
            ;
        }
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); // 设置系统时钟为PLL时钟
        while(RCC_GetSYSCLKSource() != 0x08)
        {
            // 等待设置系统时钟
            ;
        }
    }
    else
    {
        // 如果HSI启动失败, 用户在此添加处理错误代码
    }
}
```

#### 在bsp_rccclkconfig.h中加入函数声明

```c
void HSI_SetSysClk(uint32_t RCC_PLLMul_x);
```

#### 在main.c中调用HSI配置系统时钟函数

```c
HSI_SetSysClk(RCC_PLLMul_12); // 4*12=48MHz
MCO_GPIO_Config();
RCC_MCOConfig(RCC_MCO_SYSCLK); // 配置MCO选择系统时钟
LED_GPIO_Config();
```

## 中断

### STM32中断应用概览

#### 中断类型

- 系统异常: 体现在内核水平
- 外部中断: 体现在外设水平

#### NVIC

NVIC负责管理中断

在core_cm3.h中的定义  

```c
/** @addtogroup CMSIS_CM3_NVIC CMSIS CM3 NVIC
  memory mapped structure for Nested Vectored Interrupt Controller (NVIC)
  @{
 */
typedef struct
{
  // 中断使能寄存器
  __IO uint32_t ISER[8];                      /*!< Offset: 0x000  Interrupt Set Enable Register           */
       uint32_t RESERVED0[24];                                   

  // 中断清除寄存器
  __IO uint32_t ICER[8];                      /*!< Offset: 0x080  Interrupt Clear Enable Register         */
       uint32_t RSERVED1[24];                                    

  // 中断使能悬起寄存器
  __IO uint32_t ISPR[8];                      /*!< Offset: 0x100  Interrupt Set Pending Register          */
       uint32_t RESERVED2[24];                                   
  
  // 中断清除悬起寄存器 
  __IO uint32_t ICPR[8];                      /*!< Offset: 0x180  Interrupt Clear Pending Register        */
       uint32_t RESERVED3[24];                                   

  // 中断有效位寄存器
  __IO uint32_t IABR[8];                      /*!< Offset: 0x200  Interrupt Active bit Register           */
       uint32_t RESERVED4[56];                                   

  // 中断优先级寄存器
  __IO uint8_t  IP[240];                      /*!< Offset: 0x300  Interrupt Priority Register (8Bit wide) */
       uint32_t RESERVED5[644];                                  

  // 软件触发中断寄存器
  __O  uint32_t STIR;                         /*!< Offset: 0xE00  Software Trigger Interrupt Register     */
}  NVIC_Type;                                               
/*@}*/ /* end of group CMSIS_CM3_NVIC */
```

##### NVIC的优先级分组

通过**SCB->AIRCR寄存器的PRIGROUP部分(即bit[10:8])进行分组**

![NVIC优先级](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401140238595.png)

### 中断编程的顺序

1. 使能中断请求(**使能外设中断, 使能 NVIC 中断**)
2. 配置中断优先级分组(NVIC_PriorityGroupConfig)
3. 配置 NVIC 寄存器, 初始化NVIC_InitTypeDef
4. 编写中断服务函数

## EXTI

### EXTI 输入线

![EXTI 输入线](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/%E6%88%AA%E5%B1%8F2024-01-15%2015.13.32.png)

通过寄存器 AFIO_EXTICR1, 2, 3, 4配置

### EXTI 框图讲解

![EXTI 框图](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/%E6%88%AA%E5%B1%8F2024-01-15%2015.18.42.png)

#### 外部中断流程

1. 通过 EXTI_RTSR 和 EXTI_FTSR 来配置上升沿/下降沿触发, 触发后边沿检测电路为 1
2. 通过 EXTI_SWIER 来配置软件中断, 配置后为 1
3. 经过逻辑与门后, 进入请求挂起寄存器
4. 通过 EXTI_PR 配置挂起
5. 通过 EXTI_IMR 配置中断屏蔽
6. 请求挂起寄存器的逻辑值与中断屏蔽寄存器的逻辑值做逻辑与至 NVIC 中断控制器

#### 外部事件流程

1. 通过 EXTI_RTSR 和 EXTI_FTSR 来配置上升沿/下降沿触发, 触发后边沿检测电路为 1
2. 通过 EXTI_SWIER 来配置软件中断, 配置后为 1
3. 经过逻辑与门后, 向下跟事件屏蔽寄存器相与
4. 通过 EXTI_EMR 配置事件屏蔽
5. 若为 1 产生脉冲

### EXTI 结构体

EXTI_InitTypeDef

- EXTI_Line : 用于产生中断/事件线
- EXTI_Mode : EXTI 模式(中断/事件)
- EXTI_Trigger : 触发(上/下/上下)
- EXTI_LineCmd :  使能或者失能(IMR/EMR)

#### EXTI 的结构体定义

```c
/** 
  * @brief  EXTI Init Structure definition  
  */

typedef struct
{
  uint32_t EXTI_Line;               /*!< Specifies the EXTI lines to be enabled or disabled.
                                         This parameter can be any combination of @ref EXTI_Lines */
   
  EXTIMode_TypeDef EXTI_Mode;       /*!< Specifies the mode for the EXTI lines.
                                         This parameter can be a value of @ref EXTIMode_TypeDef */

  EXTITrigger_TypeDef EXTI_Trigger; /*!< Specifies the trigger signal active edge for the EXTI lines.
                                         This parameter can be a value of @ref EXTIMode_TypeDef */

  FunctionalState EXTI_LineCmd;     /*!< Specifies the new state of the selected EXTI lines.
                                         This parameter can be set either to ENABLE or DISABLE */ 
}EXTI_InitTypeDef;

/**
  * @}
  */
```

##### EXTI_Line 的定义

```c
/** @defgroup EXTI_Lines 
  * @{
  */

#define EXTI_Line0       ((uint32_t)0x00001)  /*!< External interrupt line 0 */
#define EXTI_Line1       ((uint32_t)0x00002)  /*!< External interrupt line 1 */
#define EXTI_Line2       ((uint32_t)0x00004)  /*!< External interrupt line 2 */
#define EXTI_Line3       ((uint32_t)0x00008)  /*!< External interrupt line 3 */
#define EXTI_Line4       ((uint32_t)0x00010)  /*!< External interrupt line 4 */
#define EXTI_Line5       ((uint32_t)0x00020)  /*!< External interrupt line 5 */
#define EXTI_Line6       ((uint32_t)0x00040)  /*!< External interrupt line 6 */
#define EXTI_Line7       ((uint32_t)0x00080)  /*!< External interrupt line 7 */
#define EXTI_Line8       ((uint32_t)0x00100)  /*!< External interrupt line 8 */
#define EXTI_Line9       ((uint32_t)0x00200)  /*!< External interrupt line 9 */
#define EXTI_Line10      ((uint32_t)0x00400)  /*!< External interrupt line 10 */
#define EXTI_Line11      ((uint32_t)0x00800)  /*!< External interrupt line 11 */
#define EXTI_Line12      ((uint32_t)0x01000)  /*!< External interrupt line 12 */
#define EXTI_Line13      ((uint32_t)0x02000)  /*!< External interrupt line 13 */
#define EXTI_Line14      ((uint32_t)0x04000)  /*!< External interrupt line 14 */
#define EXTI_Line15      ((uint32_t)0x08000)  /*!< External interrupt line 15 */
#define EXTI_Line16      ((uint32_t)0x10000)  /*!< External interrupt line 16 Connected to the PVD Output */
#define EXTI_Line17      ((uint32_t)0x20000)  /*!< External interrupt line 17 Connected to the RTC Alarm event */
#define EXTI_Line18      ((uint32_t)0x40000)  /*!< External interrupt line 18 Connected to the USB Device/USB OTG FS
                                                   Wakeup from suspend event */                                    
#define EXTI_Line19      ((uint32_t)0x80000)  /*!< External interrupt line 19 Connected to the Ethernet Wakeup event */
```

##### EXTI_Mode 的定义

```c
/** 
  * @brief  EXTI mode enumeration  
  */

typedef enum
{
  EXTI_Mode_Interrupt = 0x00,
  EXTI_Mode_Event = 0x04
}EXTIMode_TypeDef;

#define IS_EXTI_MODE(MODE) (((MODE) == EXTI_Mode_Interrupt) || ((MODE) == EXTI_Mode_Event))
```

##### EXTI_Trigger 的定义

```c
/** 
  * @brief  EXTI Trigger enumeration  
  */

typedef enum
{
  EXTI_Trigger_Rising = 0x08,
  EXTI_Trigger_Falling = 0x0C,  
  EXTI_Trigger_Rising_Falling = 0x10
}EXTITrigger_TypeDef;

#define IS_EXTI_TRIGGER(TRIGGER) (((TRIGGER) == EXTI_Trigger_Rising) || \
                                  ((TRIGGER) == EXTI_Trigger_Falling) || \
                                  ((TRIGGER) == EXTI_Trigger_Rising_Falling))
```

### GPIO 作为 EXTI 输入线的配置

在 stm32f10x_gpio.c 中, 使用 GPIO_EXTILineConfig 函数进行配置

```c
/**
  * @brief  Selects the GPIO pin used as EXTI Line.
  * @param  GPIO_PortSource: selects the GPIO port to be used as source for EXTI lines.
  *   This parameter can be GPIO_PortSourceGPIOx where x can be (A..G).
  * @param  GPIO_PinSource: specifies the EXTI line to be configured.
  *   This parameter can be GPIO_PinSourcex where x can be (0..15).
  * @retval None
  */
void GPIO_EXTILineConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource)
{
  uint32_t tmp = 0x00;
  /* Check the parameters */
  assert_param(IS_GPIO_EXTI_PORT_SOURCE(GPIO_PortSource));
  assert_param(IS_GPIO_PIN_SOURCE(GPIO_PinSource));
  
  tmp = ((uint32_t)0x0F) << (0x04 * (GPIO_PinSource & (uint8_t)0x03));
  AFIO->EXTICR[GPIO_PinSource >> 0x02] &= ~tmp;
  AFIO->EXTICR[GPIO_PinSource >> 0x02] |= (((uint32_t)GPIO_PortSource) << (0x04 * (GPIO_PinSource & (uint8_t)0x03)));
}
```

### EXTI中断实验

项目地址: **18-EXTI**

**项目需求:**

1. PA0 连接到 EXTI 用于产生中断, PA0 的电平变化通过按键来控制
2. 产生一次中断, LED 反转一次

#### 在bsp_exti.c中初始化要连接到EXTI的GPIO

```c
// 初始化 Key1(PA0)
RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK, ENABLE);
GPIO_InitStruct.GPIO_Pin = KEY1_INT_GPIO_PIN;
GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStruct);
```

#### 在bsp_exti.c中初始化EXTI用于产生中断/事件

```c
RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0); // 选择输入线
EXTI_InitStruct.EXTI_Line = EXTI_Line0;                     // 选择EXTI线路
EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;            // 选择中断模式
EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;         // 选择触发模式
EXTI_InitStruct.EXTI_LineCmd = ENABLE;                          // 使能EXTI线路
EXTI_Init(&EXTI_InitStruct);
```

#### 在bsp_exti.c中初始化NVIC, 用于处理中断

```c
NVIC_InitTypeDef NVIC_InitStruct;

NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); // 配置中断优先级分组

NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn; // 选择中断源
NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; // 抢占优先级
NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1; // 子优先级
NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; // 使能中断
NVIC_Init(&NVIC_InitStruct);
```

#### 在stm32f10x_it.c中编写中断服务函数

```c
/**
 * @brief EXTI0_IRQHandler: Interrupt handler for EXTI Line 0
 *
 * This function is the interrupt handler for EXTI Line 0. It toggles the state of the blue LED.
 * It checks the interrupt status of EXTI Line 0 and clears the interrupt pending bit.
 */
void EXTI0_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line0) != RESET) // 判断中断位
  {
    LED_B_TOGGLE;
  }
  EXTI_ClearITPendingBit(EXTI_Line0); // 清除中断标志位
}
```

#### 在bsp_led.h中编写电平反转函数

```c
#define LED_B_TOGGLE {LED_B_GPIO_PORT->ODR ^= LED_B_GPIO_PIN;}
```

### 补充: 使能AFIO时钟

在STM32微控制器系列中，使用外部中断（EXTI）时需要开启AFIO（Alternate Function IO）时钟的原因与STM32的硬件设计和引脚复用功能有关。

#### AFIO的作用

1. **引脚复用**：STM32的GPIO（通用输入输出）引脚具有多功能性。一个物理引脚可以用作普通的I/O，也可以被配置为特殊功能，如USART、SPI、I2C通信或外部中断（EXTI）等。AFIO（Alternate Function IO）模块负责管理这些引脚的复用功能。
2. **EXTI配置**：在STM32中，外部中断线（EXTI）可以映射到不同的GPIO引脚上。AFIO模块提供了这种映射功能。例如，如果你想将EXTI0配置为由PA0、PB0、PC0等其中一个引脚触发，就需要通过AFIO模块来设置这种映射。

#### 开启AFIO时钟的原因

**由于AFIO模块负责处理引脚的复用功能，包括EXTI的引脚映射，因此在使用EXTI功能之前，必须确保AFIO模块的时钟是使能的**如果没有使能AFIO时钟，对AFIO寄存器的任何配置操作都不会生效，这意味着EXTI线路无法正确地映射到相应的GPIO引脚上，从而导致外部中断功能无法正常工作。

#### AFIO的实际操作

在STM32的标准固件库或HAL（硬件抽象层）库中，通常会看到类似以下的代码片段，用于使能AFIO时钟：

```c
RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
```

或在使用HAL库时：

```c
__HAL_RCC_AFIO_CLK_ENABLE();
```

这些函数调用确保了AFIO模块的时钟被使能，从而使得外部中断的相关配置（如引脚映射）能够正确执行。

#### AFIO的总结

开启AFIO时钟是使用STM32的EXTI功能的必要步骤，因为AFIO模块控制着GPIO引脚的复用功能，包括将外部中断线路映射到特定的GPIO引脚。未使能AFIO时钟可能导致外部中断配置无效，进而影响整个中断处理机制的正常工作。

## SysTick

### SysTick简介

SysTick: 系统定时器, **24位, 只能递减, 存在于内核中**, 嵌套在NVIC中, 所有的Cotex-M内核的单片机都具有这个定时器.

### SysTick 功能框图

![框图](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401170017620.png)

重装载寄存器把值写入递减计数器, 可通过STK_VAL实时查询其中的值, 递减计数器从reload值开始递减, 减为0后可产生中断并且置位COUNTFLAG标志位, 置位后从reload获取值重复以上操作

### SysTick 寄存器描述

![SysTick 寄存器描述](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401170023320.png)

### SysTick 定时时间计算

需要计算的参数

![计算参数](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401170025237.png)

计算过程

![计算过程](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401170025314.png)

- Clk = 72M时
- reload = 72, t = 1us
- reload = 72000, t = 1ms

### 补充: SysTick 介绍

SysTick（System Tick Timer）是ARM Cortex-M微控制器内核的一个内置组件，用于提供一个简单但高效的系统定时器。这个定时器通常用于实现操作系统的节拍（tick），也可以用于简单的延时功能。

#### SysTick的主要特点

1. 24位递减计数器：SysTick包含一个24位的递减计数器，当计数器值递减到零时，定时器溢出并触发一个中断。
2. 可编程重载值：可以设置计数器的重载值，这决定了定时器的溢出时间间隔。
3. 可配置的时钟源：SysTick定时器可以配置为使用内核时钟或外部时钟（通常是内核时钟的一半）。
4. 自动重载：在计数到零时，计数器会自动重新加载预设的重载值，从而实现周期性定时。
5. 中断功能：当计数器达到零时，SysTick定时器可以产生一个中断。这个中断可以用于各种定时任务，如操作系统的任务调度。

#### SysTick的应用场景

1. 操作系统节拍：在实时操作系统（RTOS）中，SysTick常用于生成操作系统的节拍，这对于任务调度和时间管理非常重要。
2. 延时功能：在不需要RTOS的简单应用中，SysTick可用于生成精确的延时，例如在两个事件之间等待固定的时间。
3. 时间基准：SysTick还可以作为程序中的时间基准，用于测量时间间隔或产生定时事件。

#### SysTick的配置和使用

在使用SysTick时，一般需要进行以下配置：

1. 设置重载值：根据所需的定时周期和时钟源频率设置重载值。
2. 选择时钟源：选择使用内核时钟还是外部时钟作为SysTick的时钟源。
3. 启用中断（可选）：如果需要在定时器溢出时执行特定操作，可以启
用SysTick中断。
4. 启动定时器：启用SysTick定时器开始计数

#### SysTick的编程示例

在STM32等ARM Cortex-M微控制器上，SysTick的配置和使用通常涉及直接操作其控制和状态寄存器。以下是一个简单的示例：

```c
SysTick_Config(SystemCoreClock / 1000);  // 配置SysTick产生
```

### SysTick 源码分析

SysTick_Type定义在core_cm3.h中

```c
/** @addtogroup CMSIS_CM3_SysTick CMSIS CM3 SysTick
  memory mapped structure for SysTick
  @{
 */
typedef struct
{
  __IO uint32_t CTRL;                         /*!< Offset: 0x00  SysTick Control and Status Register */
  __IO uint32_t LOAD;                         /*!< Offset: 0x04  SysTick Reload Value Register       */
  __IO uint32_t VAL;                          /*!< Offset: 0x08  SysTick Current Value Register      */
  __I  uint32_t CALIB;                        /*!< Offset: 0x0C  SysTick Calibration Register        */
} SysTick_Type;
```

SysTick_Config函数在core_cm3.h中定义

```c
/**
 * @brief  Initialize and start the SysTick counter and its interrupt.
 *
 * @param   ticks   number of ticks between two interrupts
 * @return  1 = failed, 0 = successful
 *
 * Initialise the system tick timer and its interrupt and start the
 * system tick timer / counter in free running mode to generate 
 * periodical interrupts.
 */
static __INLINE uint32_t SysTick_Config(uint32_t ticks)
{ 
  // 判断ticks的值是否大于2^24, 若大于则违法
  if (ticks > SysTick_LOAD_RELOAD_Msk)  return (1);            /* Reload value impossible */
                                                               
  // 初始化reaload寄存器的值
  SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;      /* set reload register */

  // 配置中断优先级, 配置为15, 默认为最低的优先级
  /*-------------------------------------------------------------
   * 注: 
   * 内核优先级的判断方式:
   * 将内核外设的中断优先级的四个位按照外设的中断优先级进行分组
   * 分组后可判断内核的抢占优先级和响应优先级
   * 即人为分出抢占和响应优先级
   * 
   * 例:
   * 这里SysTick的中断优先级为15, 二进制为1111
   * 若分组为2位抢占, 2位响应
   * 则SysTick的抢占优先级为11即3, 响应优先级为11即3
   * 若分组为1位抢占, 3位响应
   * 则SysTick的抢占优先级为1即1, 响应优先级为111即7
   * 通过该方法可以比较内核优先级与外设的优先级谁更高
   * ----------------------------------------------------------*/
  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);  /* set Priority for Cortex-M0 System Interrupts */

  // 初始化counter的值为0
  SysTick->VAL   = 0;                                          /* Load the SysTick Counter Value */

  // 配置 SysTick的时钟为 72M
  // 使能中断
  // 使能 SysTick 
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | 
                   SysTick_CTRL_TICKINT_Msk   | 
                   SysTick_CTRL_ENABLE_Msk;                    /* Enable SysTick IRQ and SysTick Timer */
  return (0);                                                  /* Function successful */
}
```

### SysTick 实验

项目地址: **19-SysTick**

实验要求:

1. 编写一个微妙延时函数
2. 编写一个毫秒延时函数

#### 在bsp_systick.c中编写微妙延时函数

```c
/**
 * @brief 延时指定的微秒数
 * @param us 延时的微秒数
 * @retval None
 */
void SysTick_Delay_us(uint32_t us)
{
    SysTick_Config(SystemCoreClock / 1000000); // reload 设置为 72, t = 1us
    
    for(int i = 0; i < us; i++)
    {
        while(!(SysTick->CTRL & (1 << 16)))
        {
            ; // 等待CTRL的Bit16置1
        }
    }

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // 状态位清除
}
```

#### 在bsp_systick.c中编写毫秒延时函数

```c
/**
 * @brief 延时指定的毫秒数
 * @param ms 延时的毫秒数
 * @return 无
 */
void SysTick_Delay_ms(uint32_t ms)
{
    SysTick_Config(SystemCoreClock / 1000); // reload 设置为 72000, t = 1ms
    
    for(int i = 0; i < ms; i++)
    {
        while(!(SysTick->CTRL & (1 << 16)))
        {
            ; // 等待CTRL的Bit16置1
        }
    }

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // 状态位清除
}
```

#### 在bsp_systick.h中引用库文件和进行函数声明

```c
#ifndef __BSP_SYSTICK_H
#define __BSP_SYSTICK_H

#include "stm32f10x.h"
#include "core_cm3.h"

void SysTick_Delay_ms(uint32_t ms);
void SysTick_Delay_us(uint32_t us);

#endif // !__BSP_SYSTICK_H

```

#### 在main.c中调用延时函数,实现LED闪烁

```c
/**
 * @brief Main function of the program.
 * 
 * This function initializes the LED GPIO and enters an infinite loop. 
 * In each iteration of the loop, it turns off the blue LED, delays for 0.5 seconds,
 * turns on the blue LED, and delays for 0.5 seconds again.
 * 
 * @return int The exit status of the program.
 */
int main(void)
{
    LED_GPIO_Config(); // Initialize the LED GPIO

    while(1)
    {
        LED_B(OFF); // Turn off the blue LED
        SysTick_Delay_ms(500); // Delay for 0.5 seconds
        LED_B(ON); // Turn on the blue LED
        SysTick_Delay_us(500000); // Delay for 0.5 seconds
    }
}

```

## 通信的基本概念

### 串行和并行通信

![串行和并行通信](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171542012.png)

- 串行协议: USART, I2C, SPI, W500, CAN, LIN
- 并行协议: FSMC, SDIO

![对比](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171546066.png)

### 全双工, 半双工和单工

![全双工,半双工和单工](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171548657.png)

### 同步与异步

同步传输通过时钟信号进行同步, 保证数据传输的准确性

![同步](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171550768.png)

异步传输通过加入辅助的标识符, 保证数据传输的准确性

![异步](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171552733.png)

#### 同步与异步的区别

![区别](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171554763.png)

### 通信的速率

![通信的速率](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171555519.png)

当用一个二进制位表示一个码元时, 比特率和波特率相等

## USART-串口通信

### 串口通信协议简介

![USART](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171610065.png)

#### 物理层的常用标准

![USART](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171610887.png)

##### 232和TTL电平区别

![USART](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171611637.png)

- TTL: 从芯片出来的基本是TTL电平
- 232: 负逻辑, 压差大

###### 232通信通讯结构图

![232](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171631235.png)

DB9接口图

![DB9接口](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171634288.png)

###### USB转串口通讯结构图

![USB转串口](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171644660.png)

##### 串口到串口通讯结构图

![串口到串口](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171655718.png)

#### 串口数据包的组成

![串口数据包](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171658813.png)

![串口数据包](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171659831.png)

![串口数据包](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171702232.png)

![串口数据包](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171703446.png)

![串口数据包](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171703050.png)

![串口数据包](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171704956.png)

### STM32串口功能框图讲解

#### 引脚部分讲解

![STM32串口功能框图](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171708669.png)

![STM32串口功能框图](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171708578.png)

##### 引脚对应

![引脚对应](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171710068.png)

#### 数据寄存器部分

![数据寄存器部分](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171723621.png)

##### 数据格式

![数据格式](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171725627.png)

###### USART_CR1的bit12 M控制字长

![寄存器](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171727509.png)

###### USART_CR2的bit[13:12] STOP控制停止位的位数

![寄存器](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171727238.png)

###### USART_CR1的bit10(PSE), bit9(PS)来使能校验和选择校验模式

![寄存器](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171730822.png)

###### USART_CR1的bit8(PEIE)来使能中断

![寄存器](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171731175.png)

###### USART_SR的bit0(PE)来检测校验错误

![寄存器](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171732400.png)

#### 发送数据部分

![发送数据](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171739676.png)

1. 先将USART_CR1的UE位置1(*使能USART模块*), 再将USART_CR1的TE位置1(*使能发送*)
2. 数据从CPU或DMA中写入发送数据寄存器(TDR), TDR发送完毕后, USART_SR的TXE位置1(*数据已经被转移到移位寄存器中*)
3. 发送移位寄存器发送完毕后, USART_SR的TC位置1(*表示发送完成*)

#### 接收数据部分

![接收数据部分](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171900970.png)

1. 先将USART_CR1的UE位置1(*使能USART模块*), 再将USART_CR1的RE位置1(*使能接收*)
2. 数据从RX到接收移位寄存器到接收数据寄存器(RDR), 接收完毕后, USART_SR的RXNE位置1(*收到数据, 可以读出*)

#### 波特率设置

##### 使用USART_BRR进行配置

![USART_BRR](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171906798.png)

##### 波特率的计算公式

![波特率的计算公式](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171909589.png)

- APB2时钟: 72MHz, 挂载USART1
- APB1时钟: 36MHz, 挂载USART2, 3, 4, 5

![波特率](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171910703.png)

### 串口初始化结构体和固件库讲解

#### 串口初始化结构体

在stm32f10x_usart.h中定义串口初始化结构体(异步)

```c
/** 
  * @brief  USART Init Structure definition  
  */ 
  
typedef struct
{
  // 设置波特率
  uint32_t USART_BaudRate;            /*!< This member configures the USART communication baud rate.
                                           The baud rate is computed using the following formula:
                                            - IntegerDivider = ((PCLKx) / (16 * (USART_InitStruct->USART_BaudRate)))
                                            - FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 16) + 0.5 */

  // 设置字长
  /*-----------------------------------------------------------------------------
   * 参数如下:
   * #define USART_WordLength_8b                  ((uint16_t)0x0000)
   * #define USART_WordLength_9b                  ((uint16_t)0x1000)
   * ---------------------------------------------------------------------------*/
  uint16_t USART_WordLength;          /*!< Specifies the number of data bits transmitted or received in a frame.
                                           This parameter can be a value of @ref USART_Word_Length */

  // 设置停止位
  /*-----------------------------------------------------------------------------
   * 参数如下:
   * #define USART_StopBits_1                     ((uint16_t)0x0000)
   * #define USART_StopBits_0_5                   ((uint16_t)0x1000)
   * #define USART_StopBits_2                     ((uint16_t)0x2000)
   * #define USART_StopBits_1_5                   ((uint16_t)0x3000)
   * ---------------------------------------------------------------------------*/
  uint16_t USART_StopBits;            /*!< Specifies the number of stop bits transmitted.
                                           This parameter can be a value of @ref USART_Stop_Bits */

  // 设置校验
  /*-----------------------------------------------------------------------------
   * 参数如下:
   * #define USART_Parity_No                      ((uint16_t)0x0000)
   * #define USART_Parity_Even                    ((uint16_t)0x0400)
   * #define USART_Parity_Odd                     ((uint16_t)0x0600)
   * ---------------------------------------------------------------------------*/
  uint16_t USART_Parity;              /*!< Specifies the parity mode.
                                           This parameter can be a value of @ref USART_Parity
                                           @note When parity is enabled, the computed parity is inserted
                                                 at the MSB position of the transmitted data (9th bit when
                                                 the word length is set to 9 data bits; 8th bit when the
                                                 word length is set to 8 data bits). */
 
  // 设置模式
  /*-----------------------------------------------------------------------------
   * 参数如下:
   * #define USART_Mode_Rx                        ((uint16_t)0x0004)
   * #define USART_Mode_Tx                        ((uint16_t)0x0008)
   * ---------------------------------------------------------------------------*/
  uint16_t USART_Mode;                /*!< Specifies wether the Receive or Transmit mode is enabled or disabled.
                                           This parameter can be a value of @ref USART_Mode */

  // 设置硬件控制流
  /*-----------------------------------------------------------------------------
   * 参数如下:
   * #define USART_HardwareFlowControl_None       ((uint16_t)0x0000)
   * #define USART_HardwareFlowControl_RTS        ((uint16_t)0x0100)
   * #define USART_HardwareFlowControl_CTS        ((uint16_t)0x0200)
   * #define USART_HardwareFlowControl_RTS_CTS    ((uint16_t)0x0300)
   * ---------------------------------------------------------------------------*/
  uint16_t USART_HardwareFlowControl; /*!< Specifies wether the hardware flow control mode is enabled
                                           or disabled.
                                           This parameter can be a value of @ref USART_Hardware_Flow_Control */
} USART_InitTypeDef;
```

在stm32f10x_usart.h中定义串口初始化结构体(同步)

```c
/** 
  * @brief  USART Clock Init Structure definition  
  */ 
  
typedef struct
{

  // 设置使能时钟
  /*-----------------------------------------------------------------------------
   * 参数如下:
   * #define USART_Clock_Disable                  ((uint16_t)0x0000)
   * #define USART_Clock_Enable                   ((uint16_t)0x0800)
   * ---------------------------------------------------------------------------*/
  uint16_t USART_Clock;   /*!< Specifies whether the USART clock is enabled or disabled.
                               This parameter can be a value of @ref USART_Clock */

  // 设置时钟的极性, 即总线空闲时CK引脚保持低电平还是高电平
  /*-----------------------------------------------------------------------------
   * 参数如下:
   * #define USART_CPOL_Low                       ((uint16_t)0x0000)
   * #define USART_CPOL_High                      ((uint16_t)0x0400)
   * ---------------------------------------------------------------------------*/
  uint16_t USART_CPOL;    /*!< Specifies the steady state value of the serial clock.
                               This parameter can be a value of @ref USART_Clock_Polarity */

  // 设置时钟的相位, 即数据采样的时机为第一个边沿还是第二个边沿
  /*-----------------------------------------------------------------------------
   * 参数如下:
   * #define USART_CPHA_1Edge                     ((uint16_t)0x0000)
   * #define USART_CPHA_2Edge                     ((uint16_t)0x0200)
   * ---------------------------------------------------------------------------*/
  uint16_t USART_CPHA;    /*!< Specifies the clock transition on which the bit capture is made.
                               This parameter can be a value of @ref USART_Clock_Phase */

  // 设置时钟的最后一个数据位的时钟脉冲是否输出到SCLK引脚
  /*-----------------------------------------------------------------------------
   * 参数如下:
   * #define USART_LastBit_Disable                ((uint16_t)0x0000)
   * #define USART_LastBit_Enable                 ((uint16_t)0x0100)
   * ---------------------------------------------------------------------------*/
  uint16_t USART_LastBit; /*!< Specifies whether the clock pulse corresponding to the last transmitted
                               data bit (MSB) has to be output on the SCLK pin in synchronous mode.
                               This parameter can be a value of @ref USART_Last_Bit */
} USART_ClockInitTypeDef;
```

#### 串口库函数

- **串口初始化函数**: void USART_Init(USART_TypeDef*USARTx, USART_InitTypeDef* USART_InitStruct);
- **中断配置函数**: void USART_ITConfig(USART_TypeDef* USARTx, uint16_t USART_IT, FunctionalState NewState);
- **串口使能函数**: void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
- **数据发送函数**: void USART_SendData(USART_TypeDef* USARTx, uint16_t Data);
- **数据接收函数**: void USART_ReceiveData(USART_TypeDef* USARTx);
- **中断状态位获取函数**: ITStatus USART_GetITStatus(USART_TypeDef* USARTx, uint16_t USART_IT);

### USB转串口的硬件原理图

![硬件原理图](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401172002602.png)

### 串口GPIO汇总

![串口GPIO](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401220859886.png)

### 补充: 外设的GPIO配置

在STM32F10x参考手册中的8.1.11节可找到外设的GPIO配置, 其中关于USART部分的GPIO配置如下图

![USART的GPIO配置](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401220904826.png)

### 配置串口助手

本项目使用的串口助手: 野火多功能调试助手V1.0.2.9

串口配置如下图(*串口配置参数与串口的初始化配置有关, 该配置符合下文代码的初始化*)

![串口助手配置](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401250242370.png)

### USART接收和发送实验

项目地址: **21-USART-接收和发送**

**实验需求**: 单片机给电脑发送数据, 电脑上位机把数据打印出来; 电脑上位机给单片机发数据, 单片机接收到数据之后立马发回给电脑, 并打印出来.

#### 在bsp_usart.h中进行串口的宏定义, 并使用条件编译来选择串口

```c
/** 
  * 串口宏定义，不同的串口挂载的总线和IO不一样，移植时需要修改这几个宏
  * 1-修改总线时钟的宏，uart1挂载到apb2总线，其他uart挂载到apb1总线
  * 2-修改GPIO的宏
  */

 // 通过条件编译选择串口, 使用的串口置1，其余置0
 #define DEBUG_USART1 1
 #define DEBUG_USART2 0
 #define DEBUG_USART3 0
 #define DEBUG_USART4 0
 #define DEBUG_USART5 0
 
#if DEBUG_USART1
// 串口1-USART1
#define  DEBUG_USARTx                   USART1
#define  DEBUG_USART_CLK                RCC_APB2Periph_USART1
#define  DEBUG_USART_APBxClkCmd         RCC_APB2PeriphClockCmd
#define  DEBUG_USART_BAUDRATE           115200

// USART GPIO 引脚宏定义
#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  DEBUG_USART_TX_GPIO_PORT       GPIOA   
#define  DEBUG_USART_TX_GPIO_PIN        GPIO_Pin_9
#define  DEBUG_USART_RX_GPIO_PORT       GPIOA
#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_10

#define  DEBUG_USART_IRQ                USART1_IRQn
#define  DEBUG_USART_IRQHandler         USART1_IRQHandler

#elif DEBUG_USART2
// 串口2-USART2
#define  DEBUG_USARTx                   USART2
#define  DEBUG_USART_CLK                RCC_APB1Periph_USART2
#define  DEBUG_USART_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  DEBUG_USART_BAUDRATE           115200

// USART GPIO 引脚宏定义
#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
   
#define  DEBUG_USART_TX_GPIO_PORT       GPIOA   
#define  DEBUG_USART_TX_GPIO_PIN        GPIO_Pin_2
#define  DEBUG_USART_RX_GPIO_PORT       GPIOA
#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_3

#define  DEBUG_USART_IRQ                USART2_IRQn
#define  DEBUG_USART_IRQHandler         USART2_IRQHandler

#elif DEBUG_USART3
// 串口3-USART3
#define  DEBUG_USARTx                   USART3
#define  DEBUG_USART_CLK                RCC_APB1Periph_USART3
#define  DEBUG_USART_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  DEBUG_USART_BAUDRATE           115200

// USART GPIO 引脚宏定义
#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOB)
#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
   
#define  DEBUG_USART_TX_GPIO_PORT       GPIOB   
#define  DEBUG_USART_TX_GPIO_PIN        GPIO_Pin_10
#define  DEBUG_USART_RX_GPIO_PORT       GPIOB
#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_11

#define  DEBUG_USART_IRQ                USART3_IRQn
#define  DEBUG_USART_IRQHandler         USART3_IRQHandler

#elif DEBUG_USART4
//串口4-UART4
#define  DEBUG_USARTx                   UART4
#define  DEBUG_USART_CLK                RCC_APB1Periph_UART4
#define  DEBUG_USART_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  DEBUG_USART_BAUDRATE           115200

// USART GPIO 引脚宏定义
#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOC)
#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
   
#define  DEBUG_USART_TX_GPIO_PORT       GPIOC   
#define  DEBUG_USART_TX_GPIO_PIN        GPIO_Pin_10
#define  DEBUG_USART_RX_GPIO_PORT       GPIOC
#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_11

#define  DEBUG_USART_IRQ                UART4_IRQn
#define  DEBUG_USART_IRQHandler         UART4_IRQHandler

#elif DEBUG_UART5
// 串口5-UART5
#define  DEBUG_USARTx                   UART5
#define  DEBUG_USART_CLK                RCC_APB1Periph_UART5
#define  DEBUG_USART_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  DEBUG_USART_BAUDRATE           115200

// USART GPIO 引脚宏定义
#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD)
#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
   
#define  DEBUG_USART_TX_GPIO_PORT       GPIOC   
#define  DEBUG_USART_TX_GPIO_PIN        GPIO_Pin_12
#define  DEBUG_USART_RX_GPIO_PORT       GPIOD
#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_2

#define  DEBUG_USART_IRQ                UART5_IRQn
#define  DEBUG_USART_IRQHandler         UART5_IRQHandler

#endif
```

#### 在bsp_usart.c中编写usart的初始化函数

```c
 /**
  * @brief  USART GPIO 配置,工作参数配置
  * @param  无
  * @retval 无
  */
void USART_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    // 打开串口GPIO的时钟
    DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
    
    // 打开串口外设的时钟
    DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);
    
    // 将USART Tx的GPIO配置为推挽复用模式
    GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);
    
     // 将USART Rx的GPIO配置为浮空输入模式
    GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
    
    // 配置串口的工作参数
    // 配置波特率
    USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
    // 配置 针数据字长
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    // 配置停止位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    // 配置校验位
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    // 配置硬件流控制
    USART_InitStructure.USART_HardwareFlowControl = 
    USART_HardwareFlowControl_None;
    // 配置工作模式，收发一起
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    // 完成串口的初始化配置
    USART_Init(DEBUG_USARTx, &USART_InitStructure);
    
    // 串口中断优先级配置
    NVIC_Configuration();
    
    // 使能串口接收中断
    USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE); 
    
    // 使能串口
    USART_Cmd(DEBUG_USARTx, ENABLE);     
}
```

#### 在bsp_usart.c中编写串口中断优先级配置函数

```c
 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 嵌套向量中断控制器组选择 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
  /* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
}
```

#### 在bsp_usart.c中编写发送一个字节到串口的函数

```c
/**
 * @brief 发送一个字节到指定的USART外设
 * 
 * @param pUSARTx USART外设指针
 * @param ch 要发送的字节
 */
void Usart_SendByte(USART_TypeDef* pUSARTx, uint8_t ch)
{
    // 发送一个字节
    USART_SendData(pUSARTx, ch);
    
    // 等待发送数据寄存器为空
    while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET)
    {
     ;
    }
}
```

#### 在bsp_usart.c中编写发送两个字节到串口的函数

```c
/**
 * @brief 发送两个字节的数据
 * 
 * @param pUSARTx USART外设指针
 * @param ch 要发送的16位数据
 */
void Usart_SendHalfWord(USART_TypeDef* pUSARTx, uint16_t ch)
{
    uint8_t tmp_h, tmp_l;

    tmp_h = (ch & 0xFF00) >> 8; // 取出高八位
    tmp_l = (ch & 0xFF) >> 0; // 取出低八位

    USART_SendData(pUSARTx, tmp_h); // 发送高八位
    while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET)
    {
        ;
    }

    USART_SendData(pUSARTx, tmp_l); // 发送低八位
    while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET)
    {
        ;
    }
}
```

#### 在bsp_usart.c中编写发送数组的函数

```c
/**
 * @brief Sends an array of bytes over USART.
 * 
 * This function sends an array of bytes over the specified USART peripheral.
 * 
 * @param pUSARTx The USART peripheral to use.
 * @param array Pointer to the array of bytes to send.
 * @param num The number of bytes to send.
 */
void Usart_SendArray(USART_TypeDef* pUSARTx, uint8_t* array, uint16_t num)
{
    for(uint16_t i = 0; i < num; i++)
    {
     Usart_SendByte(pUSARTx, array[i]);
    }
    while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET)
    {
     ;
    }
}
```

#### 在bsp_usart.c中编写发送字符串的函数

```c
/**
 * @brief 发送字符串到USART外设
 * 
 * @param pUSARTx USART外设指针
 * @param str 要发送的字符串
 */
void Usart_SendString(USART_TypeDef* pUSARTx, uint8_t* str)
{
    // 发送数据
    uint8_t i = 0;
    do
    {
     Usart_SendByte(pUSARTx, *(str + i));
     i++;
    } while (*(str + i) != '\0');

    // 等待发送完成
    while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET)
    {
     ;
    }
}
```

#### 在bsp_usart.c中编写重定向标准输出输入函数, 使得串口可使用scanf printf等函数

```c
// 重定向c库函数printf, putchar到串口，重定向后可使用printf, putchar函数
/**
 * @brief 重定向标准输出函数
 * @param ch 要发送的字符
 * @param f 文件指针
 * @retval 发送的字符
 */
int fputc(int ch, FILE* f)
{
    USART_SendData(DEBUG_USARTx, (uint8_t)ch);

    while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET)
    {
     ;
    }

    return (ch);
}

/**
 * @brief 重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
 * 
 * @param f 文件指针
 * @return int 从串口接收到的数据
 */
int fgetc(FILE *f)
{
    /* 等待串口输入数据 */
    while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);

    return (int)USART_ReceiveData(DEBUG_USARTx);
}

```

#### 在main.c函数中进行测试

```c
#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_usart.h"

int main(void)
{
    USART_Config(); // 初始化USART

    // 发送1字节数据
    Usart_SendByte(DEBUG_USARTx, 'a');
    Usart_SendByte(DEBUG_USARTx, '\n');

    // 发送2字节数据
    Usart_SendHalfWord(DEBUG_USARTx, 0xFF56);

    // 发送数组
    Usart_SendArray(DEBUG_USARTx, (uint8_t*)"Hello World!", 11);
    uint8_t array[11] = {"Hello World!"};
    Usart_SendArray(DEBUG_USARTx, array, 11);

    // 发送字符串
    Usart_SendString(DEBUG_USARTx, "\nString: Hello World\n");

    // 重定向printf函数
    printf("printf: Hello World\n");

    // 重定向putchar函数
    putchar('p');
    putchar('u');
    putchar('t');
    putchar('c');
    putchar('h');
    putchar('a');
    putchar('r');
    putchar('\n');
    
    while(1)
    {
        ;
    }
}

```

#### 在stm32f10x_it.c中编写中断服务函数实现串口数据的接收并发送

```c
/**
 * @brief Interrupt handler for the DEBUG_USART.
 *
 * This function is called when there is a receive interrupt from the DEBUG_USART.
 * It receives data from the DEBUG_USART and sends it back.
 */
void DEBUG_USART_IRQHandler(void)
{
  uint8_t ucTemp;

  if(USART_GetITStatus(DEBUG_USARTx, USART_IT_RXNE) != RESET)
  {
    ucTemp = USART_ReceiveData(DEBUG_USARTx); // Receive data into ucTemp
    USART_SendData(DEBUG_USARTx, ucTemp); // Send data
  }
}
```

### 补充: 通过重写fputc函数重定向C库函数printf到串口

通过重写 fputc 函数可以实现重定向 printf 到串口的效果。这是因为 printf 函数实际上是通过 C 标准库中的输出函数 fputc 来将字符一个个地发送到输出设备的。当你重写了 fputc 函数，实际上就改变了字符的输出方式，使得字符被发送到你所定义的输出设备，比如串口。

下面是一个简单的示例，演示了如何通过重写 fputc 函数来重定向 printf 到串口。这里假设你已经在系统中初始化了串口的硬件。

```c
#include <stdio.h>

// 串口初始化函数，假设已经在系统中实现
void initSerialPort() {
    // 串口初始化的相关代码
}

// 重定向标准输出函数
int fputc(int ch, FILE *f) {
    // 将字符发送到串口
    // 你需要在这里添加实际的串口发送代码
    // 例如：sendCharacterToSerialPort(ch);
    
    return ch;
}

int main() {
    // 初始化串口
    initSerialPort();

    // 在这之后，调用printf将输出信息发送到串口
    printf("Hello, Serial Port!\n");

    // 其他代码...

    return 0;
}

```

在这个示例中，我们重写了 fputc 函数，使其将字符发送到串口。当 printf 调用 fputc 函数时，字符就会被发送到串口。这样就实现了将 printf 输出重定向到串口的效果。

需要注意的是，具体的串口发送函数实现（比如 sendCharacterToSerialPort）需要根据你的具体硬件和系统来编写。这个示例只是演示了重定向的基本原理。

### USART控制RGB灯实验

项目地址: **21-USART-控制RGB灯**

**实验需求**: 电脑给单片机发命令, 用于控制开发板上的RGB灯.

#### 在bsp_led.h中定义RGB灯的宏

```c
#ifndef __LED_H
#define __LED_H


#include "stm32f10x.h"


/* 定义LED连接的GPIO端口, 用户只需要修改下面的代码即可改变控制的LED引脚 */
// R-红色
#define LED1_GPIO_PORT     GPIOB                 /* GPIO端口 */
#define LED1_GPIO_CLK      RCC_APB2Periph_GPIOB  /* GPIO端口时钟 */
#define LED1_GPIO_PIN  GPIO_Pin_5           /* 连接到SCL时钟线的GPIO */

// G-绿色
#define LED2_GPIO_PORT     GPIOB                 /* GPIO端口 */
#define LED2_GPIO_CLK      RCC_APB2Periph_GPIOB  /* GPIO端口时钟 */
#define LED2_GPIO_PIN  GPIO_Pin_0           /* 连接到SCL时钟线的GPIO */

// B-蓝色
#define LED3_GPIO_PORT     GPIOB                 /* GPIO端口 */
#define LED3_GPIO_CLK      RCC_APB2Periph_GPIOB  /* GPIO端口时钟 */
#define LED3_GPIO_PIN  GPIO_Pin_1           /* 连接到SCL时钟线的GPIO */


/** the macro definition to trigger the led on or off 
  * 1 - off
  *0 - on
  */
#define ON  0
#define OFF 1

/* 使用标准的固件库控制IO*/
#define LED1(a) if (a) \
     GPIO_SetBits(LED1_GPIO_PORT,LED1_GPIO_PIN);\
     else  \
     GPIO_ResetBits(LED1_GPIO_PORT,LED1_GPIO_PIN)

#define LED2(a) if (a) \
     GPIO_SetBits(LED2_GPIO_PORT,LED2_GPIO_PIN);\
     else  \
     GPIO_ResetBits(LED2_GPIO_PORT,LED2_GPIO_PIN)

#define LED3(a) if (a) \
     GPIO_SetBits(LED3_GPIO_PORT,LED3_GPIO_PIN);\
     else  \
     GPIO_ResetBits(LED3_GPIO_PORT,LED3_GPIO_PIN)


/* 直接操作寄存器的方法控制IO */
#define digitalHi(p,i)   {p->BSRR=i;}  //输出为高电平  
#define digitalLo(p,i)   {p->BRR=i;}  //输出低电平
#define digitalToggle(p,i) {p->ODR ^=i;} //输出反转状态


/* 定义控制IO的宏 */
#define LED1_TOGGLE   digitalToggle(LED1_GPIO_PORT,LED1_GPIO_PIN)
#define LED1_OFF     digitalHi(LED1_GPIO_PORT,LED1_GPIO_PIN)
#define LED1_ON      digitalLo(LED1_GPIO_PORT,LED1_GPIO_PIN)

#define LED2_TOGGLE   digitalToggle(LED2_GPIO_PORT,LED2_GPIO_PIN)
#define LED2_OFF     digitalHi(LED2_GPIO_PORT,LED2_GPIO_PIN)
#define LED2_ON      digitalLo(LED2_GPIO_PORT,LED2_GPIO_PIN)

#define LED3_TOGGLE   digitalToggle(LED3_GPIO_PORT,LED3_GPIO_PIN)
#define LED3_OFF     digitalHi(LED3_GPIO_PORT,LED3_GPIO_PIN)
#define LED3_ON      digitalLo(LED3_GPIO_PORT,LED3_GPIO_PIN)

/* 基本混色，后面高级用法使用PWM可混出全彩颜色,且效果更好 */

//红
#define LED_RED  \
     LED1_ON;\
     LED2_OFF\
     LED3_OFF

//绿
#define LED_GREEN  \
     LED1_OFF;\
     LED2_ON\
     LED3_OFF

//蓝
#define LED_BLUE \
     LED1_OFF;\
     LED2_OFF\
     LED3_ON

     
//黄(红+绿)     
#define LED_YELLOW \
     LED1_ON;\
     LED2_ON\
     LED3_OFF
//紫(红+蓝)
#define LED_PURPLE \
     LED1_ON;\
     LED2_OFF\
     LED3_ON

//青(绿+蓝)
#define LED_CYAN \
     LED1_OFF;\
     LED2_ON\
     LED3_ON
     
//白(红+绿+蓝)
#define LED_WHITE \
     LED1_ON;\
     LED2_ON\
     LED3_ON
     
//黑(全部关闭)
#define LED_RGBOFF \
     LED1_OFF;\
     LED2_OFF\
     LED3_OFF

void LED_GPIO_Config(void);

#endif /* __LED_H */
```

#### 在bsp_led.c中编写led初始化函数

```c
/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   led应用函数接口
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 F103-霸道 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./led/bsp_led.h"   

 /**
  * @brief  初始化控制LED的IO
  * @param  无
  * @retval 无
  */
void LED_GPIO_Config(void)
{  
    /*定义一个GPIO_InitTypeDef类型的结构体*/
    GPIO_InitTypeDef GPIO_InitStructure;

    /*开启LED相关的GPIO外设时钟*/
    RCC_APB2PeriphClockCmd( LED1_GPIO_CLK | LED2_GPIO_CLK | LED3_GPIO_CLK, ENABLE);
    /*选择要控制的GPIO引脚*/
    GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN; 

    /*设置引脚模式为通用推挽输出*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

    /*设置引脚速率为50MHz */   
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

    /*调用库函数，初始化GPIO*/
    GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure); 

    /*选择要控制的GPIO引脚*/
    GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN;

    /*调用库函数，初始化GPIO*/
    GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);

    /*选择要控制的GPIO引脚*/
    GPIO_InitStructure.GPIO_Pin = LED3_GPIO_PIN;

    /*调用库函数，初始化GPIOF*/
    GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);

    /* 关闭所有led灯 */
    GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);

    /* 关闭所有led灯 */
    GPIO_SetBits(LED2_GPIO_PORT, LED2_GPIO_PIN);  
    
      /* 关闭所有led灯 */
    GPIO_SetBits(LED3_GPIO_PORT, LED3_GPIO_PIN);
}

void assert_failed(uint8_t* file, uint32_t line)
{
    // 断言错误时执行的代码
    LED1_ON;
}
/*********************************************END OF FILE**********************/
```

#### 在bsp_usart.c中关闭串口中断

```c
 /**
  * @brief  USART GPIO 配置,工作参数配置
  * @param  无
  * @retval 无
  */
void USART_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    // 打开串口GPIO的时钟
    DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
    
    // 打开串口外设的时钟
    DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);

    // 将USART Tx的GPIO配置为推挽复用模式
    GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

       // 将USART Rx的GPIO配置为浮空输入模式
    GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
    
    // 配置串口的工作参数
    // 配置波特率
    USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
    // 配置 针数据字长
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    // 配置停止位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    // 配置校验位
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    // 配置硬件流控制
    USART_InitStructure.USART_HardwareFlowControl = 
    USART_HardwareFlowControl_None;
    // 配置工作模式，收发一起
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    // 完成串口的初始化配置
    USART_Init(DEBUG_USARTx, &USART_InitStructure);
    
    // 将中断失能
    USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, DISABLE); 
    
    // 使能串口
    USART_Cmd(DEBUG_USARTx, ENABLE);     
}
```

#### 在main.c中编写测试程序

```c
int main(void)
{
    uint8_t ch = 0;

    USART_Config(); // 初始化USART
    LED_GPIO_Config(); // 初始化LED

    printf("USART-RGB\n");
    printf("1:RED, 2:GREEN, 3:BLUE, 4:YELLOW, 5:PURPLE, 6:CYAN, 7:WHITE\n");
    printf("Others: BLACK\n");
    

    while(1)
    {
        ch = getchar();
        printf("ch = %c\n", ch);

        switch(ch)
        {
        case '1': LED_RED;
            break;
        case '2': LED_GREEN;
            break;
        case '3': LED_BLUE;
            break;
        case '4': LED_YELLOW;
            break;
        case '5': LED_PURPLE;
            break;
        case '6': LED_CYAN;
            break;
        case '7': LED_WHITE;
            break;
        
        default: LED_RGBOFF;
            break;
        }
    }
}

```

## DMA

DMA: Direct Memory Access, 直接寄存器访问. 主要功能是可以把数据从一个地方搬到另一个地方, 而且不占用CPU

- DMA1: 有7个通道, 可实现P->M, M->P, M->M
- DMA2: 有5个通道, 可实现P->M, M->P, M->M(*只存在于大容量和互联型产品中*)

### 补充: DMA介绍

DMA（Direct Memory Access，直接内存访问）是计算机系统中的一种技术，**它允许外设或内存模块通过绕过中央处理器（CPU）直接与系统内存进行数据传输**。DMA的目标是提高数据传输效率，减轻CPU的负担，使CPU能够专注于执行其他任务。

以下是关于DMA的一些重要概念和特性：

#### DMA的工作原理

DMA通过在系统总线上控制数据传输而不涉及CPU来工作。它可以在CPU不介入的情况下，直接将数据从一个位置传输到另一个位置。

1. 配置： CPU负责配置DMA，确定源地址、目标地址、传输方向、传输大小等参数。
2. 启动： 一旦DMA被配置，CPU就可以启动DMA控制器，它将负责管理数据传输。
3. 传输： DMA控制器在总线上控制数据传输，无需CPU的干预。数据在源和目标之间直接传输。
4. 中断通知： DMA传输完成后，通常会发出一个中断信号，以通知CPU或其他系统组件。

#### DMA的优点

1. 提高性能： 通过绕过CPU，减轻了CPU的负担，使其能够执行其他任务，提高了整体系统性能。
2. 实时数据传输： 特别适用于实时数据传输，如音频、视频流等。
3. 高效处理大量数据： 对于大量数据的块传输，DMA比CPU执行这样的传输更为高效。

#### DMA的应用领域

DMA在多种应用场景中都得到了广泛应用，包括但不限于：

1. 嵌入式系统： 用于处理外设和内存之间的数据传输，例如，处理音频、图像等。
2. 网络通信： 在网络接口控制器和系统内存之间快速传输数据。
3. 存储系统： 用于在磁盘、固态硬盘等存储设备和系统内存之间进行数据传输。
4. 图形处理： 在图形卡和系统内存之间进行大规模图形数据的传输。

#### DMA控制器

DMA通常由专门的硬件单元，称为DMA控制器，来管理。DMA控制器的设计和功能因芯片架构而异，但通常包括寄存器用于配置、启动和监视传输。

总的来说，DMA是一项重要的技术，对于需要高效数据传输的系统是至关重要的。通过减轻CPU的负担，DMA提高了系统的整体性能和响应速度。

### DMA功能框图讲解

![DMA功能框图讲解](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401261122722.png)

#### DMA请求映射

DMA1请求映射

![DMA1请求映射](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401261126729.png)

DMA2请求映射

![DMA2请求映射](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401261127579.png)

#### DMA仲裁器

![DMA仲裁器](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401261128690.png)

软件配置在寄存器DMA_CCRx:PL[1:0]进行通道优先级配置

### DMA固件库-初始化结构体

初始化结构体在stm32f10x_dma.h文件中

```c
/** 
  * @brief  DMA Init structure definition
  */

typedef struct
{
  /*--------------------------------------------------------------------------------
   * 外设地址
   * 由寄存器 DMA_CPARx 进行配置
   *---------------------------------------------------------------------------- */
  uint32_t DMA_PeripheralBaseAddr; /*!< Specifies the peripheral base address for DMAy Channelx. */

  /*--------------------------------------------------------------------------------
   * 存储器地址
   * 由寄存器 DMA_CMARx 进行配置
   *---------------------------------------------------------------------------- */
  uint32_t DMA_MemoryBaseAddr;     /*!< Specifies the memory base address for DMAy Channelx. */

  /*--------------------------------------------------------------------------------
   * 传输方向
   * P->M 和 M->P 由寄存器 DMA_CCRx:DIR[4] 进行配置
   * M->M 由寄存器 DMA_CCRx:MEM2MEM[14] 进行配置
   *--------------------------------------------------------------------------------*/
  uint32_t DMA_DIR;                /*!< Specifies if the peripheral is the source or destination.
                                        This parameter can be a value of @ref DMA_data_transfer_direction */

  /*--------------------------------------------------------------------------------
   * 缓冲区大小, 传输数目
   * 由寄存器 DMA_CNDTRx 进行配置
   *-------------------------------------------------------------------------------*/
  uint32_t DMA_BufferSize;         /*!< Specifies the buffer size, in data unit, of the specified Channel. 
                                        The data unit is equal to the configuration set in DMA_PeripheralDataSize
                                        or DMA_MemoryDataSize members depending in the transfer direction. */

  /*--------------------------------------------------------------------------------
   * 外设增量模式
   * 由寄存器 DMA_CCRx:PINC[6] 进行配置
   *--------------------------------------------------------------------------------*/
  uint32_t DMA_PeripheralInc;      /*!< Specifies whether the Peripheral address register is incremented or not.
                                        This parameter can be a value of @ref DMA_peripheral_incremented_mode */

  /*--------------------------------------------------------------------------------
   * 存储器增量模式
   * 由寄存器 DMA_CCRx:MINC[7] 进行配置
   *--------------------------------------------------------------------------------*/
  uint32_t DMA_MemoryInc;          /*!< Specifies whether the memory address register is incremented or not.
                                        This parameter can be a value of @ref DMA_memory_incremented_mode */

  /*--------------------------------------------------------------------------------
   * 外设数据宽度
   * 由寄存器 DMA_CCRx:PSIZE[9:8] 进行配置
   *--------------------------------------------------------------------------------*/
  uint32_t DMA_PeripheralDataSize; /*!< Specifies the Peripheral data width.
                                        This parameter can be a value of @ref DMA_peripheral_data_size */

  /*--------------------------------------------------------------------------------
   * 存储器数据宽度
   * 由寄存器 DMA_CCRx:MSIZE[11:10] 进行配置
   *--------------------------------------------------------------------------------*/
  uint32_t DMA_MemoryDataSize;     /*!< Specifies the Memory data width.
                                        This parameter can be a value of @ref DMA_memory_data_size */

  /*--------------------------------------------------------------------------------
   * 传输模式
   * 由寄存器 DMA_CCRx:CIRC[5] 进行配置
   * 通过 DMA_ISR 判断传输状态来判断传输完成, 传输一半, 传输错误
   *--------------------------------------------------------------------------------*/
  uint32_t DMA_Mode;               /*!< Specifies the operation mode of the DMAy Channelx.
                                        This parameter can be a value of @ref DMA_circular_normal_mode.
                                        @note: The circular buffer mode cannot be used if the memory-to-memory
                                              data transfer is configured on the selected Channel */

  /*--------------------------------------------------------------------------------
   * 优先级
   * 由寄存器 DMA_CCRx:PL[1:0] 进行配置
   *--------------------------------------------------------------------------------*/
  uint32_t DMA_Priority;           /*!< Specifies the software priority for the DMAy Channelx.
                                        This parameter can be a value of @ref DMA_priority_level */

  /*--------------------------------------------------------------------------------
   * 存储器到存储器模式
   * 由寄存器 DMA_CCRx:MEM2MEM[14] 进行配置
   *--------------------------------------------------------------------------------*/
  uint32_t DMA_M2M;                /*!< Specifies if the DMAy Channelx will be used in memory-to-memory transfer.
                                        This parameter can be a value of @ref DMA_memory_to_memory */
}DMA_InitTypeDef;
```

### DMA固件库-固件库函数

在stm32f10x_dma.h文件中可以找到DMA固件库函数的声明, 以下是常用的函数

```c
void DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_InitTypeDef* DMA_InitStruct); // 初始化函数
void DMA_Cmd(DMA_Channel_TypeDef* DMAy_Channelx, FunctionalState NewState); // 使能DMA
FlagStatus DMA_GetFlagStatus(uint32_t DMAy_FLAG); // 判断标志位
```

### DMA实验1: M to M

项目地址: **22-DMA-MtoM**

**实验需求**: FLASH to SRAM, 把内部FLASH的数据传输到内部的SRAM

#### 在bsp_dma_m2m.h增加宏定义

```c
// 当使用存储器到存储器模式时候，通道可以随便选，没有硬性的规定
#define M2M_DMA_CHANNEL     DMA1_Channel6
#define M2M_DMA_CLOCK       RCC_AHBPeriph_DMA1
// 传输完成标志
#define M2M_DMA_FLAG_TC     DMA1_FLAG_TC6
// 要发送的数据大小
#define BUFFER_SIZE     32
```

#### 在bsp_dma_m2m.c中定义源和目标变量

```c
/* 定义aSRC_Const_Buffer数组作为DMA传输数据源
 * const关键字将aSRC_Const_Buffer数组变量定义为常量类型
 * 表示数据存储在内部的FLASH中
 */
const uint32_t aSRC_Const_Buffer[BUFFER_SIZE]= {
                                    0x01020304,0x05060708,0x090A0B0C,0x0D0E0F10,
                                    0x11121314,0x15161718,0x191A1B1C,0x1D1E1F20,
                                    0x21222324,0x25262728,0x292A2B2C,0x2D2E2F30,
                                    0x31323334,0x35363738,0x393A3B3C,0x3D3E3F40,
                                    0x41424344,0x45464748,0x494A4B4C,0x4D4E4F50,
                                    0x51525354,0x55565758,0x595A5B5C,0x5D5E5F60,
                                    0x61626364,0x65666768,0x696A6B6C,0x6D6E6F70,
                                    0x71727374,0x75767778,0x797A7B7C,0x7D7E7F80};

/**
 * 定义DMA传输目标存储器
 * 存储在内部的SRAM中                  
 */
uint32_t aDST_Buffer[BUFFER_SIZE];

```

#### 在bsp_dma_m2m.c中增加DMA初始化函数

```c
/**
 * @brief 配置存储器到存储器的DMA传输
 * 
 * @param None
 * @return None
 */
void M2M_DMA_Config(void)
{
    DMA_InitTypeDef DMA_InitStructure; // 定义DMA初始化结构体变量
    
    RCC_AHBPeriphClockCmd(M2M_DMA_CLOCK, ENABLE); // 打开DMA时钟

    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)aSRC_Const_Buffer; // 配置外设地址, 实际将FLASH的数据配置成了外设
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)aDST_Buffer; // 配置存储器地址
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; // 配置传输方向，从外设读取数据发送到存储器
    DMA_InitStructure.DMA_BufferSize = BUFFER_SIZE; // 配置传输数据大小
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable; // 配置外设地址自增
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; // 配置存储器地址自增
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word; // 配置外设数据大小
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word; // 配置存储器数据大小
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; // 配置传输模式，非循环模式
    DMA_InitStructure.DMA_Priority = DMA_Priority_High; // 配置传输通道优先级
    DMA_InitStructure.DMA_M2M = DMA_M2M_Enable; // 配置存储器到存储器模式

    DMA_Init(M2M_DMA_CHANNEL, &DMA_InitStructure); // 初始化DMA通道
    DMA_ClearFlag(M2M_DMA_FLAG_TC); // 清除DMA通道传输完成标志位
    DMA_Cmd(M2M_DMA_CHANNEL, ENABLE); // 使能DMA通道
}
```

#### 在bsp_dma_m2m.c中增加判断数据相等的函数

```c
/**
 * @brief 比较两个缓冲区的数据是否相等
 * 
 * @param pBuffer 指向第一个缓冲区的指针
 * @param pBuffer1 指向第二个缓冲区的指针
 * @param BufferLength 缓冲区的长度
 * @return uint8_t 如果两个缓冲区的数据相等，则返回1；否则返回0
 */
uint8_t Buffercmp(const uint32_t* pBuffer, uint32_t* pBuffer1, uint16_t BufferLength)
{
    /* 数据长度递减 */
    while(BufferLength--)
    {
        /* 判断两个数据源是否对应相等 */
        if(*pBuffer != *pBuffer1)
        {
            /* 对应数据源不相等马上退出函数，并返回0 */
            return 0;
        }
        /* 递增两个数据源的地址指针 */
        pBuffer++;
        pBuffer1++;
    }
    /* 完成判断并且对应数据相对 */
    return 1;  
}
```

#### 在main.c函数中进行DMA测试

```c
// 声明以下变量来自外部文件
extern const uint32_t aSRC_Const_Buffer[BUFFER_SIZE];
extern uint32_t aDST_Buffer[BUFFER_SIZE];

/**
 * @brief Delays the execution for a specified number of milliseconds.(Not Sure)
 * @param ms The number of milliseconds to delay.
 * @return None.
 */
void Delay_ms(uint32_t ms)
{
    uint32_t i = 0;
    for(i = 0; i < ms; i++)
    {
        uint16_t j = 0;
        for(j = 0; j < 1000; j++)
        {
            ;
        }
    }
}

int main(void)
{
    uint8_t status = 0; // 接收比较的结构

    LED_GPIO_Config(); // 初始化LED
    M2M_DMA_Config(); // 初始化DMA
     
    // 等待DMA1传送完毕
    while(DMA_GetFlagStatus(M2M_DMA_FLAG_TC) == RESET)
    {
        ;
    }

    LED_YELLOW;
    Delay_ms(10000); // DMA初始化完成后亮黄灯

    status = Buffercmp(aSRC_Const_Buffer, aDST_Buffer, BUFFER_SIZE); // 比较两个数组的数据是否相等
    if(status == 0)
    {
        LED_RED; // 数据不相等亮红灯
    }
    else
    {
        LED_GREEN; // 数据相等亮绿灯
    }

    while(1)
    {
        ;
    }
}
```

### DMA实验2: M to P

项目地址: **22-DMA-MtoP**

**实验需求**: SRAM to 串口, 同时LED灯闪烁, 演示DMA数据不需占用CPU

### 在bsp_dma_m2p.h中加入宏定义

```c
// 串口工作参数宏定义
#define  DEBUG_USARTx                   USART1
#define  DEBUG_USART_CLK                RCC_APB2Periph_USART1
#define  DEBUG_USART_APBxClkCmd         RCC_APB2PeriphClockCmd
#define  DEBUG_USART_BAUDRATE           115200

// USART GPIO 引脚宏定义
#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
#define  DEBUG_USART_TX_GPIO_PORT       GPIOA   
#define  DEBUG_USART_TX_GPIO_PIN        GPIO_Pin_9
#define  DEBUG_USART_RX_GPIO_PORT       GPIOA
#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_10

#define USART_TX_DMA_CLK RCC_AHBPeriph_DMA1 // 串口DMA时钟
#define  USART_TX_DMA_CHANNEL     DMA1_Channel4 // 串口对应的DMA请求通道
#define  USART_DR_ADDRESS        (USART1_BASE+0x04) // 外设寄存器地址
#define  SENDBUFF_SIZE            5000 // 一次发送的数据量
#define  USART_TX_DMA_FLAG_TC DMA1_FLAG_TC4 // 标志位
```

#### 在bsp_dma_m2p.c中加入USART的初始化函数

```c
/**
  * @brief  USART GPIO 配置,工作参数配置
  * @param  无
  * @retval 无
  */
void USART_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    // 打开串口GPIO的时钟
    DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);

    // 打开串口外设的时钟
    DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);

    // 将USART Tx的GPIO配置为推挽复用模式
    GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

       // 将USART Rx的GPIO配置为浮空输入模式
    GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);

    // 配置串口的工作参数
    // 配置波特率
    USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
    // 配置 针数据字长
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    // 配置停止位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    // 配置校验位
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    // 配置硬件流控制
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    // 配置工作模式，收发一起
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    // 完成串口的初始化配置
    USART_Init(DEBUG_USARTx, &USART_InitStructure); 

    // 使能串口
    USART_Cmd(DEBUG_USARTx, ENABLE);     
}
```

#### 在bsp_dma_m2p.c中加入USARTx_TX DMA配置

实现内存到外设(USART1->DR)

```c
/**
  * @brief  USARTx TX DMA 配置，内存到外设(USART1->DR)
  * @param  无
  * @retval 无
  */
void USARTx_DMA_Config(void)
{
    DMA_InitTypeDef DMA_InitStructure;
    
    // 开启DMA时钟
    RCC_AHBPeriphClockCmd(USART_TX_DMA_CLK, ENABLE);
    // 设置DMA源地址：串口数据寄存器地址*/
       DMA_InitStructure.DMA_PeripheralBaseAddr = USART_DR_ADDRESS;
    // 内存地址(要传输的变量的指针)
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)SendBuff;
    // 方向：从内存到外设 
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    // 传输大小 
    DMA_InitStructure.DMA_BufferSize = SENDBUFF_SIZE;
    // 外设地址不增     
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    // 内存地址自增
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    // 外设数据单位 
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    // 内存数据单位
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  
    // DMA模式，一次或者循环模式
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;
    // DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; 
    // 优先级：中 
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; 
    // 禁止内存到内存的传输
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    // 配置DMA通道     
    DMA_Init(USART_TX_DMA_CHANNEL, &DMA_InitStructure);  
    // 清除TC标志位
    DMA_ClearFlag(USART_TX_DMA_FLAG_TC);
    // 使能DMA
    DMA_Cmd (USART_TX_DMA_CHANNEL, ENABLE);
    
```

#### 在bsp_dma_m2p.c中声明在内存的变量

```c
uint8_t SendBuff[SENDBUFF_SIZE];
```

#### 在main.c中声明外部变量

```c
extern uint8_t SendBuff[SENDBUFF_SIZE];
```

#### 在main.c中测试DMA

实现DMA将储存器中的数据发送到USART->DR, 并实现LED1闪烁

```c
/**
 * @brief 实现DMA将储存器中的数据发送到USART->DR, 并实现LED1闪烁
 * 
 * @return int 
 */
int main(void)
{

    LED_GPIO_Config(); // 初始化LED
    USART_Config(); // 串口初始化

    for(uint16_t i = 0; i < SENDBUFF_SIZE; i++)
    {
        SendBuff[i] = 'P';
    }

    USARTx_DMA_Config(); // 初始化DMA
    USART_DMACmd(DEBUG_USARTx, USART_DMAReq_Tx, ENABLE); // 使能DMA发送

    while(1)
    {
        LED1_TOGGLE;
        Delay_ms(10000);
    }
}
```

## 常用存储器

### 存储器的种类

易失性和非易失性区别在于**掉电数据是否会丢失**, 易失性存储器**读写速度相对较快**

- 易失性存储器(RAM)
  - DRAM(动态RAM, 常用于PC机)
    - SDRAM(STM32F429)
    - DDR SDRAM
    - DDRII SDRAM
    - DDRIII SDRAM(常用于PC机)
  - SRAM(静态RAM, STM32F103)
- 非易失性存储器
  - ROM(半导体类)
    - MASK ROM(对于STM32可读不可写)
    - PROM(可编程ROM)
      - OTPROM(可写一次的ROM)
      - EPROM(可用高电压擦除的ROM)
      - EEPROM(STM32F103, 可用较低电压3.3V擦除的ROM)
    - FLASH(半导体类)
    - NOR FLASH(一般用来存储程序)
    - NAND FLASH(一般用来存储数据)
    - 光盘
    - 软盘
    - 机械硬盘

### RAM存储器(易失性存储器)

#### RAM介绍

![RAM介绍](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401262322421.png)

#### DRAM的存储单元结构

![DRAM的存储单元结构](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401262327533.png)

**DRAM通过电容充放电与MOS管配合产生高低电平**, 需要配合电平检测阈值来减少电容漏电带来的影响

#### SRAM的存储单元结构

![SRAM的存储单元结构](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401262328328.png)

**SRAM以锁存器结构来存储数据**, 锁存器结构在没有输入的情况下会一直保持原来的状态

#### SRAM和DRAM的比较

![SRAM和DRAM的比较](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401262336065.png)

SDRAM使用同步通信方式

![SDRAM同步通信](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401262341860.png)

SRAM使用异步方式通信

![SRAM异步通信](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270000903.png)

### 非易失性存储器

#### ROM简介

![ROM简介](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270001764.png)

#### FLASH简介

![FLASH简介](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270007166.png)

在嵌入式开发中选择 NOR FLASH 主要因为坏区较少, 基于字节读写可以支持XIP

XIP(Execute In Place，就地执行)功能，它是一种特性，允许直接从 Flash 存储器中执行代码，而无需将代码首先复制到RAM中。XIP功能在嵌入式系统中很常见，它带来了一些优势，包括更少的RAM使用和更快的启动速度

与ROM不同, FLASH必须先按块擦除数据后才能写入数据

## I2C-读写EEPROM

### 补充: I2C简介

I2C（Inter-Integrated Circuit）是一种串行通信协议，**用于在集成电路之间进行短距离通信** I2C 由飞利浦公司（Philips）于1982年开发，并且现在由多家公司支持和采用。该协议通常用于连接芯片、传感器、存储器、外设等设备。

以下是 I2C 协议的一些关键特点和基本概念：

1. 总线结构
    - 主从结构： I2C 使用主从结构，其中一个设备充当主设备（通常是微控制器或处理器），而其他设备则充当从设备。主设备负责发起通信和生成时钟信号。
    - 双线制： I2C 使用两根线，一根是数据线（SDA），另一根是时钟线（SCL）。这两根线上都有上拉电阻，以便在设备不主动拉低时保持高电平。
2. 数据传输：
    - 起始和停止条件： 数据传输始于主设备发送起始条件（Start Condition），并以主设备发送停止条件（Stop Condition）结束。这两个条件都是由主设备在总线上生成的。
    - 地址帧： 每个数据传输都以地址帧开始，其中包含目标设备的地址和读写位。地址帧由主设备发送。
    - 数据帧： 在地址帧之后是一个或多个数据帧，其中包含实际的数据。数据帧的传输由主设备和从设备之间交替进行。
    - 应答（Acknowledge）： 在每个数据帧之后，接收方发送一个应答信号，通常是一个低电平，以确认数据的接收。
3. 速率和模式：
    - 速率： I2C 支持不同的传输速率，常见的有 100 kHz、400 kHz 和 1 MHz 等。
    - 模式： I2C 支持标准模式（100 kHz），快速模式（400 kHz），高速模式（1 MHz）等不同的工作模式。
4. 多主设备和重复启动：
    - 多主设备： I2C 支持多主设备共享同一总线。主设备之间通过仲裁（Arbitration）来确定哪个主设备能够继续发送。
    - 重复启动： 主设备可以在一个传输结束后发送重复启动条件，而无需先发送停止条件，从而在同一次通信中与另一个从设备建立连接。
5. I2C设备地址：
   - 7位或10位地址： I2C 设备使用 7 位或 10 位地址来识别自己。大多数设备使用 7 位地址。

I2C 协议的简洁性和灵活性使得它在连接各种设备和传感器时非常有用，尤其是在嵌入式系统中。

### 补充: 高阻态

在嵌入式领域中，高阻态的概念同样非常重要，并涉及到数字电路设计和信号完整性的方面。以下是在嵌入式系统中高阻态的一些关键应用和概念：

1. 输入端口的高阻态： 很多嵌入式系统包括微控制器或微处理器，**其输入端口通常具有高阻抗特性。这意味着当输入端口未连接到任何外部设备时，输入端口会处于高阻态状态。这有助于避免在未连接设备时引入不必要的电流，同时防止信号线上的悬空状态(floating)**。
2. 悬空输入的高阻态： 在数字电路中，当一个输入端未连接时，它被称为悬空输入。在悬空输入的情况下，该输入端常常设计为高阻态，以减少对电路的干扰和功耗。
3. 总线冲突的高阻态： **在多主设备共享总线的系统中，当多个主设备尝试在同一时刻传输数据时可能会发生总线冲突。为了避免冲突设备之间的干扰，某些设备在冲突时会将总线设置为高阻态，以允许其他设备继续操作**。
4. 三态逻辑门： 一些数字逻辑门（如三态门）具有高阻态输出。这允许将多个门连接到同一总线上，当其中一个门处于高阻态时，其他门仍能够正常工作。
5. 输入缓冲器的高阻态： 在输入缓冲器中，当输入未被有效驱动时，输入缓冲器通常进入高阻态，以避免对电路产生负面影响。

在这些情况下，高阻态的概念有助于确保电路在非活动状态时不引入不必要的电流，提高系统的稳定性和可靠性。这对于嵌入式系统中对功耗、信号完整性和总线冲突等方面的考虑非常重要。

### I2C物理层

![I2C物理层](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270111246.png)

![I2C物理层](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270140896.png)

#### I2C物理层主要特点

- I2C是支持多设备的总线, 可支持多个通讯主机和从机
- I2C使用两条线路, 一条SDA(双向串行数据线)来表示数据, 一条SCL(串行时钟线)来同步数据, 属于半双工同步通信
- 连接到总线的设备分配独立地址(7位或10位)
- 总线接上拉电阻到电源(一般4.7KΩ, 具体看手册)
    1. 当设备空闲时输出高阻态*防止短路总线上的其他接地设备*
    2. 当所有设备都空闲时全部输出高阻态, 可通过上拉电阻把总线拉到高电平
    3. 输出高阻态的特性需要GPIO的开漏输出
- 多设备占用总线会仲裁
- 具有三种传输速度模式, **实际开发中可使用低于最高速的速度, 协调总线设备速度一致即可**
- I2C可接入的设备数量受到最大电容负载的限制, 一般为400pF, *也就是说总线上的设备数量越多, 传输速度越慢*

### I2C协议层

I2C协议定义了**通讯的起始和停止信号, 数据有效性, 响应, 仲裁, 时钟同步和地址广播等环节**

#### I2C基本读写过程

##### 主机写数据到从机

![I2C基本读写过程](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270157626.png)

1. S: 主机传输开始信号
2. SLAVE ADDRESS: 主机传输需要通信的从机地址
3. R/!W: 主机传输读或写信号, *若为1(写)则主机向从机发送数据, 若为0(读)则从机向主机发送数据*
4. A: 从机传输响应
5. DATA: 主机传输数据段
6. A: 从机响应
7. DATA: 主机继续发送数据段
8. A/!A: 从机响应是否继续接收
9. P: 若从机响应不继续接收, 则主机传输停止位

##### 主机由从机读数据

![I2C基本读写过程](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270207508.png)

1. S: 主机传输开始信号
2. SLAVE ADDRESS: 主机传输需要通信的从机地址
3. R/!W: 主机传输读或写信号, *若为1(写)则主机向从机发送数据, 若为0(读)则从机向主机发送数据*
4. A: 从机传输响应
5. DATA: 从机传输数据段
6. A: 主机响应
7. DATA: 从机继续发送数据段
8. A/!A: 主机响应是否继续接收
9. P: 若主机响应不继续接收, 则主机传输停止位

注意:

- S: 开始信号只能由主机产生
- SLAVE ADDRESS: 进行通信的从机地址只能由主机产生
- R/!W: 读/写信号只能由主机产生
- P: 停止信号只能由主机产生
- DATA 和 A: 数据段和响应段由主机和从机交替产生, 具体由主机和从机的读写决定

##### 通信复合格式

![通信复合格式](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270209992.png)

常用的复合通信的方法, **即先写入外设地址后将外设的寄存器地址返回进行读取**

- S: 主机传输开始信号
- SLAVE ADDRESS: 进行通信的从机地址(一般为外设)
- R/W!: 一般为写操作
- DATA: 写入的外设地址
- A/A!: 从机响应
- Sr: 主机传输开始信号
- SLAVE ADDRESS: 进行通信的从机地址(一般为同一个外设)
- R/W!: 一般为读操作
- DATA: 读取外设的寄存器的具体地址
- A/A!: 逐个字节进行读取外设每个寄存器的地址并做出响应
- P: 全部读取完毕后主机传输停止信号

#### 通讯的起始和停止信号

![通讯的起始和停止信号](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270225648.png)

- 起始信号: **SCL高电平, SDA由高电平向低电平转换**
- 停止信号: **SCL高电平, SDA由低电平向高电平转换**

#### 数据的有效性

![数据有效性](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270237788.png)

- SDA: 负责传输数据
- SCL: 高电平时采集SDA上1bit数据, 低电平时SDA进行电平转换

#### 地址及数据方向

![地址及数据方向](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270243764.png)

I2C采用高位先行, 由高位到低位进行传输

一般使用7位表示I2C上的设备地址, 设备地址加上其后的读写位可以凑成8位即1字节方便传输

例如, 某设备在I2C上的设备地址为7位的0x78(0b01111000), 可加入读写位凑到八位

- 8位设备的读地址位为0xF1(0b11110001)
- 8位设备的写地址位为0xF0(0b11110000)

#### 响应

![响应](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270254565.png)

1. 1-8个时钟信号中: 数据发送端控制SDA传输7位设备地址和1位读写信号
2. 在第9个时钟信号时: 数据接收端获得SDA控制权, 发送应答信号(低电平表示应答)

### STM32的I2C特性及架构

![STM32的I2C特性及架构](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270305500.png)

- 软件模拟协议: 较为繁琐
- 硬件模拟协议: 较为方便, 减轻CPU负担

注: *STM32硬件的I2C逻辑可能会有问题*

#### STM32的I2C架构分析

![STM32的I2C架构分析](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270315440.png)

##### I2C的通讯引脚

![I2C的通讯引脚](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270346561.png)

![I2C的通讯引脚](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270316720.png)

勘误: *I2C1_SCL默认映射到PB5, I2C1_SDA默认映射到PB7, 图片中有误*

STM32兼容smbus协议

##### I2C时钟控制逻辑

![时钟控制逻辑](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270347794.png)
![时钟控制逻辑](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270325594.png)

注: *Tpck1: 指的是APB1时钟周期(1/36MHz)*

###### 计算时钟频率的方法

![计算时钟频率的方法](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270333989.png)

实际就是解未知数CCR的一元一次方程

##### I2C数据控制逻辑

![数据控制逻辑](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270347332.png)

![数据控制逻辑](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270337311.png)

1. 将8位数据写入数据寄存器(DR)
2. 数据寄存器里面的数据会被发送到数据移位寄存器

##### 整体控制逻辑

![整体控制逻辑](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270348369.png)

![整体控制逻辑](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270355991.png)

### STM32硬件I2C的通讯过程

#### STM32作为主发送器的通讯过程

![STM32作为主发送器的通讯过程](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270357886.png)

勘误: *EV8_2: TxE=1, BTF=1, 请求设置停止位. TxE和BTF位由硬件在产生停止条件时清除*

- EV5: 在正常产生S起始信号后会产生EV5事件(I2C_SRx:SB[0]置1表示起始条件已发送)
- EV6: 在正常发送SLAVE ADDRESS和R/!W位后会产生EV6事件(I2C_SRx:ADDR[1]置1表示地址发送结束)
- EV8: 在正常数据发送完毕后会产生EV8事件(I2C_SRx:TxE[7]置1表示数据寄存器空)
- EV8_2: 在从机发送结束应答后会产生EV8_2事件(I2C_SRx:TxE[7]置1表示数据寄存器空, I2C_SRx:BTF[2]置1表示字节发送结束, I2C_CRx:STOP[9]置1表示在当前字节传输或在当前起始条件发出后产生停止条件, 产生停止条件后由硬件清除TxE和BTF位)

#### STM32作为主接收器的通讯过程

![STM32作为主接收器的通讯过程](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270423471.png)

勘误: *EV7_1: RxNE=1, 读DR寄存器清除该事件. 设置ACK=0和STOP请求*

- EV5: 在正常产生S起始信号后会产生EV5事件(I2C_SRx:SB[0]置1表示起始条件已发送)
- EV6: 在正常发送SLAVE ADDRESS和R/!W位后会产生EV6事件(I2C_SRx:ADDR[1]置1表示地址发送结束)
- EV7: 在正常数据发送完毕后会产生EV7事件(I2C_SRx:RxNE[6]置1表示数据寄存器(接收时)非空)
- EV7_1: 在主机发送结束应答后会产生EV7_1事件(I2C_SRx:RxNE[6]置1表示数据寄存器(接收时)非空, I2C_CRx:ACK[10]置0表示设置为无应答返回, I2C_CRx:STOP[9]置1表示在当前字节传输或释放SCL和SDA线)

每个状态标志位的清除方法各不相同, 使用库函数的方法可以较方便的清除寄存器的标志位

### I2C初始化结构体

在stm32f10x_i2c.h中定义I2C初始化结构体

```c
/** 
  * @brief  I2C Init structure definition  
  */

typedef struct
{
  /*---------------------------------------------------------------------------------
   * 设置时钟频率
   * 设置I2C的传输速率, 函数根据该值经过运算后写入I2C_CCR寄存器
   * 不得高于400kHz, 即400 000
   * 由于I2C_CCR寄存器不能写入浮点数, 可能会导致实际速率小于设定的传输速率参数
   * 使得通讯稍慢, 但是并不会对I2C的通讯造成其他影响
   *-------------------------------------------------------------------------------*/
  uint32_t I2C_ClockSpeed;          /*!< Specifies the clock frequency.
                                         This parameter must be set to a value lower than 400kHz */

  /*---------------------------------------------------------------------------------
   * 设置I2C的模式
   * I2C_Mode_I2C: 标准I2C模式
   * I2C_Mode_SMBusDevice: SMBus设备模式
   * I2C_Mode_SMBusHost: SMBus主机模式
   *-------------------------------------------------------------------------------*/
  uint16_t I2C_Mode;                /*!< Specifies the I2C mode.
                                         This parameter can be a value of @ref I2C_mode */

  /*---------------------------------------------------------------------------------
   * 设置I2C的SCL时钟的占空比
   * I2C_DutyCycle_16_9: Tlow/Thigh = 16:9
   * I2C_DutyCycle_2: Tlow/Thigh = 2:1
   * 这两个选项差别不大, 开发中一般不会进行严格区分
   *-------------------------------------------------------------------------------*/
  uint16_t I2C_DutyCycle;           /*!< Specifies the I2C fast mode duty cycle.
                                         This parameter can be a value of @ref I2C_duty_cycle_in_fast_mode */

  /*---------------------------------------------------------------------------------
   * 配置STM32的I2C设备自己的地址
   * 此参数可以是 7 位或 10 位地址
   * 第二个地址可以通过函数I2C_OwnAddress2Config进行配置, 只能是7位地址
   *-------------------------------------------------------------------------------*/
  uint16_t I2C_OwnAddress1;         /*!< Specifies the first device own address.
                                         This parameter can be a 7-bit or 10-bit address. */

  /*---------------------------------------------------------------------------------
   * 配置I2C应答是否使能
   * I2C_Ack_Enable: 允许应答使能
   * I2C_Ack_Disable: 禁止应答使能
   * 一般配置为允许应答使能, 改为禁止应答使能往往会导致通讯错误
   *-------------------------------------------------------------------------------*/
  uint16_t I2C_Ack;                 /*!< Enables or disables the acknowledgement.
                                         This parameter can be a value of @ref I2C_acknowledgement */

  /*---------------------------------------------------------------------------------
   * 配置I2C的寻址长度
   * I2C_AcknowledgedAddress_7bit: 7位地址
   * I2C_AcknowledgedAddress_10bit: 10位地址
   * 需要根据连接到I2C总线上的设备进行选择, 确保地址长度一致, 才能进行通信
   * 只有I2C_OwnAddress1才能配置10位地址, I2C_OwnAddress2只支持7位地址 *-------------------------------------------------------------------------------*/
  uint16_t I2C_AcknowledgedAddress; /*!< Specifies if 7-bit or 10-bit address is acknowledged.
                                         This parameter can be a value of @ref I2C_acknowledged_address */
}I2C_InitTypeDef;
```

### I2C库函数

#### I2C_GenerateSTART函数, 用于产生起始条件

![I2C库函数](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271607885.png)

#### I2C_GetFlagStatus函数, 用于获取状态位

![I2C库函数](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271610721.png)

I2C_FLAG参数列表对应I2C_SRx状态寄存器的各个位, 可通过查询手册查看其含义

返回值说明

![返回值说明](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271612900.png)

```c
typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;
```

- RESET: 0, 返回RESET表示该状态位为0
- SET: 1, 返回SET表示该状态位为1

#### I2C_Send7bitAddress函数, 用于发送7位地址

![I2C库函数](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271616560.png)

参数Address为八位读/写地址, 通过I2C_Direction实际配置读写方向, 最终方向以I2C_Direction配置为准, 参数Address的读写位失效

#### I2C_SendDate函数, 通过I2Cx外设发送数据字节

![I2C库函数](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271618557.png)

#### I2C_ReceiveData函数, 返回 I2Cx 外设最近接收的数据

![I2C库函数](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271622473.png)

#### AcknowledgeConfig函数, 使能或禁用I2C的应答

![I2C库函数](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271623317.png)

#### I2C_Cmd函数, 使能或禁用I2Cx外设

![I2C库函数](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271625131.png)

#### I2C_CheckEvent函数, I2C状态监测函数

监测的事件发生则返回SUCCESS

![I2C库函数](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401280036252.png)

![I2C_CheckEvent函数](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401280037103.png)

![I2C_CheckEvent函数](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401280037758.png)

![I2C_CheckEvent函数](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401280038783.png)

![I2C_CheckEvent函数](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401280038105.png)

### EEPROM硬件结构

![EEPROM](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271630443.png)

#### 引脚说明

- VCC: 电源引脚, 接3V3
- GND: 地引脚, 接地
- SCL: 时钟线, 经2.2K上拉电阻接3V3, 接PB6引脚(默认映射I2C1_SCL)
- SDA: 数据线, 经2,2K上拉电阻接3V3, 接PB7引脚(默认映射I2C1_SDA)
- HOLD: WP引脚, 接地, 不启用写保护(即可向AT24C02写数据)
- A0-A2: 地址引脚, 接地, A0:A2为000, 如需拓展EEPROM则可通过配置A0-A2的地址引脚来进行区分(如: 配置A0:A2为001, 则可对两EEPROM进行区分)

### AT24C02介绍

![AT24C02](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271642465.png)

AT24C02可存储256字节数据

#### AT24C02引脚说明

![AT24C02](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271648925.png)

- A0-A2: AT24C02用来区分不同AT24C0x芯片的设备地址
- SDA: 数据线
- SCL: 时钟线
- WP: 写保护, 置1启用写保护
- NC: 不连接

#### AT24C02设备地址

![设备地址](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271702961.png)

![设备地址](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271702718.png)

AT24C02有256字节, 即属于2K(256*8)

![设备地址](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271701248.png)

根据原理图, 将A2-A0均接地, 则A2 = A1 = A0 = 0

AT24C02的地址为0b1010000R/W, Bit0为R/!W位

- AT24C02在A2:A1[000]情况下读地址: 0b10100001(0xA1)
- AT24C02在A2:A1[000]情况下写地址: 0b10100000(0xA0)

#### AT24C02的Byte Write(以字节方式写数据)操作

![Byte Write](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271719435.png)

第一个传输的数据段(DATA)为WORD ADDRESS(需要写入的字节所在的地址), 第二次传输数据段(DATA)才为真正需要写入的内容

![Byte Write](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271723653.png)

```tex
翻译: Byte Write的工作流程

1. 在发送完SLAVE ADDRESS和W/!R后, 需要发送一个字节的数据地址(WORD ADDRESS)(即需要写入的字节所在的地址)
2. 收到地址(WORD ADDRESS)后, EEPROM会响应ACK, 然后接收一个字节的数据(DATA)(真正要写入的内容)
3. 接收到数据(DATA)后, EEPROM响应ACK, 单片机必须发送STOP信号, 不能继续传输第二段数据(给EEPROM预留写入时间)
4. 接收到停止信号后, EEPROM在tWR的周期时间内进行向内部写入数据
5. 在此写入周期中, 所有输入被禁用, EEPROM不进行响应
```

#### AT24C02的Page Write(以页方式写数据)操作

又称突发写入(即仅发送一个地址可写入多个数据)

Page Write解决了Byte Write不能连续写入的缺陷

![Page Write](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271734727.png)

- WORD ADDRESS(n): 数据的起始地址
- DATA(n): 写入到WORD ADDRESS(n)中
- DATA(n+1): 写入到WORD ADDRESS(n+1)中
- DATA(n+x): 写入到WORD ADDRESS(n+x)中

![Page Write](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271741445.png)

```tex
翻译: Page Write工作流程

1. AT24C02能以8字节进行Page Write
2. 与Byte Write类似, 第一个字节是数据地址(WORD ADDRESS)(即需要写入的字节所在的地址), 在接受到第二个字节(DATA)后不会要求单片机发送STOP信号
3. 相反, EEPROM在接收到第一个DATA(真正要写入的数据)后, 对于AT24C02来说, 能再最多传输7个DATA
4. EEPROM每接收到一个数据位都会响应ACK, 单片机必须发送停止信号来结束Page Writting
5. 收到每个DATA后, 对于AT24C02来说, 数据地址(WORD ADDRESS)的低三位会递增(低三位的取值情况为2^3 = 8, 即8字节)
6. 高位地址不会递增, 从而保证原来的初始数据地址不发生改变(确保低三位正确递增)
7. 当递增的地址到达Page的界限后, 剩下的8位数据会覆盖Page的开头
8. 如果向EEPROM传输的DATA超过8个字节(对于AT24C02), 则数据会从头覆盖
```

#### AT24C02的ACKNOWLEDGE POLLING(确认轮询)

![ACKNOWLEDGE POLLING](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401280423663.png)

```tex
一旦内部定时写周期开始并且EEPROM输入被禁用，可以启动确认轮询。
这涉及发送一个启动条件，后跟设备地址。读/写位是代表所需的操作。
仅当内部写周期完成时EEPROM 会响应“0”，允许继续读取或写入序列
```

需要在向AT24C02写入数据操作后, 进行确认询问, 主机需要发送启动条件, 设备地址, 读写位, 如果AT24C02准备完毕会响应0才能继续进行操作

以I2C1为例, 软件编程实现如下

```c
/**
 * @brief ACKNOWLEDGE POLLING 对EEPROM进行确认询问 
 *   STM32向EEPROM写入数据后, EEPROM需要时间向内部存储期间进行写入
 *   此时EEPROM不应答, 所以在发送下一次I2C请求之前,应等待EEPROM写入完成
 *   以上步骤称为ACKNOWLEDGE POLLING
 * @param None
 * @retval None
 */
void EEPROM_ACK_Polling(void)
{
    do
    {
    /* STM32产生START信号 */
    I2C_GenerateSTART(EEPROM_I2C, ENABLE);
    /* 等待EV5事件完成, SB=1(未设置检测时间超时, 不严谨) */
    while(I2C_GetFlagStatus(EEPROM_I2C, I2C_FLAG_SB) == RESET)
    {
       ;
    }
    /* STM32发送EEPROM的写地址 */
    I2C_Send7bitAddress(EEPROM_I2C, EEPROM_I2C_WRITE_ADDRESS, I2C_Direction_Transmitter);
    } while (I2C_GetFlagStatus(EEPROM_I2C, I2C_FLAG_ADDR) == RESET); 
    /* 循环监测EV6事件(ADDR=1)(接收)完成(未设置检测时间超时, 不严谨) */
    /* 结束询问 */
    I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
}

```

#### AT24C02的Current Address Read(从当前地址读数据)操作

![Current Address Read](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271810617.png)

一般不用, 因为在开发中不好确定当前地址的位置

#### AT24C02的Random Read(随机读数据)操作

![Random Read](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271813901.png)

1. 产生起始信号, 向EEPROM发送要读取数据的数据地址(写方向)
2. 再次产生起始信号, 从EEPROM中读取数据(读方向)
3. EEPROM在被写入要读取数据的数据地址后会进行确认并输出该数据内容

![Random Read](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271821179.png)

```tex
翻译: Random Read流程

1. Random Read需要"dummy"来写入要读取数据(DATA)的数据地址(WORD ADDRESS)
2. 一旦DEVICE ADDRESS和WORD ADDRESS被EEPROM响应, 单片机必须生成另一个START信号
3. 单片机发送读信号来读取当前地址(DEVICE ADDRESS)
4. EEPROM响应DEVICE ADDRESS并串行输出数据(DATA)
5. 单片机响应NO ACK并紧跟生成STOP信号
```

#### AT24C02的Sequential Read(顺序读数据)操作

![Sequential Read](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271838678.png)

与Page Write类似

![Sequential Read](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271841941.png)

```tex
翻译: Sequential Read流程

1. Sequntial Read从当前地址读取或随机地址开始读取
2. 单片机收到DATA后，会响应ACK
3. 只要EEPROM收到ACK响应，它就会继续递增数据地址，并顺序串行输出DATA
4. 当达到内存地址限制时，数据地址将"roll over"，顺序读取将继续从头开始重新读取数据
5. 当单片机NO ACK响应并生成STOP，则终止Sequential Read
```

### 硬件I2C实验

项目地址: **24-I2C-Hard**

#### 操作流程

1. 初始化I2C相关的GPIO
2. 配置I2C外设的工作模式
3. 编写I2C写入EEPROM的Byte Write函数
4. 编写I2C读取EEPROM的Random Read函数
5. 使用read函数和write函数进行读写校验
6. 编写Page Write和Sequential Read函数进行校验

#### 在bsp_i2c.h中定义相关宏

```c
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
```

#### 在bsp_i2c.h中进行函数声明

```c
/**
 * @defgroup EEPROM_I2C_Functions 
 * @{
 */

void I2C_EEPROM_Config(void);
void EEPROM_Byte_Writting(uint8_t WordAddress, uint8_t Data);
void EEPROM_Page_Writting(uint8_t WordAddress, uint8_t* Data, uint8_t NumByteToWrite);
void EEPROM_Random_Read(uint8_t WordAddress, uint8_t* Data);
void EEPROM_Sequential_Read(uint8_t WordAddress, uint8_t* Data, uint8_t NumByteToRead);
void EEPROM_ACK_Polling(void);

/**
 * @} 
 * 
 */
```

#### 在bsp_i2c.c中编写I2C_EEPROM配置函数

```c
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
    /* STM32主机地址 */
    I2C_InitStructure.I2C_OwnAddress1 = STM32_I2C_OWN_ADDR;
    /* 初始化I2C */
    I2C_Init(EEPROM_I2C, &I2C_InitStructure); 
    /* 使能I2C */
    I2C_Cmd(EEPROM_I2C, ENABLE);
}
```

#### 在bsp_i2c.c中编写Byte Writting方式的函数

```c
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
    /* STM32使能ACK信号, 恢复到默认状态 */
    I2C_AcknowledgeConfig(EEPROM_I2C, ENABLE);
}
```

#### 在bsp_i2c.c中编写Page Writting方式的函数

```c
/**
 * @brief 函数实现了STM32作为主发送器向EEPROM以Page Writting的方式写数据(每次不超过8字节) 
 * @param WordAddress: 需要写入的字节所在的地址
 * @param Data: 真正要写入的数据的指针
 * @param NumByteToWrite: 要写入数据的个数小于8
 * @retval None
 */
void EEPROM_Page_Writting(uint8_t WordAddress, uint8_t* Data, uint8_t NumByteToWrite)
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
    /* 循环写入数据 */
    while(NumByteToWrite)
    {
        /* STM32向EEPROM发送Data */
        I2C_SendData(EEPROM_I2C, *Data);
        /* 数据指针自增 */
        Data++;
        /* 等待EV8_2事件完成(未设置检测时间超时, 不严谨) */
        while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED) == ERROR)
        {
        ;
        }
        NumByteToWrite--;
    }
    /* STM32产生STOP信号 */
    I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
    /* STM32使能ACK信号, 恢复到默认状态 */
    I2C_AcknowledgeConfig(EEPROM_I2C, ENABLE);
}
```

#### 在bsp_i2c.c中编写Random Read方式的函数

```c
/**
 * @brief 函数实现STM32从EEPROM以Random Read方式读取数据
 * @param WordAddress: 要读取数据的地址
 * @param Data: 读取数据要写入到的变量
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
```

#### 在bsp_i2c.c中编写Sequential Read方式的函数

```c
/**
 * @brief 函数实现STM32从EEPROM以Sequential Read方式读取数据
 * @param WordAddress: 要读取数据的地址
 * @param Data: 读取数据要写入到的变量
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
```

#### 在bsp_i2c.c中编写确认询问函数

```c
/**
 * @brief ACKNOWLEDGE POLLING 对EEPROM进行确认轮询
 *   一旦内部定时写周期开始并且EEPROM输入被禁用，可以启动确认轮询。
 *   这涉及发送一个启动条件，后跟设备地址。
 *   读/写位是代表所需的操作。
 *   仅当内部写周期完成时EEPROM 会响应“0”，允许继续读取或写入序列
 *   以上步骤称为ACKNOWLEDGE POLLING
 * @param None
 * @retval None
 */
void EEPROM_ACK_Polling(void)
{
    do
    {
    /* STM32产生START信号 */
    I2C_GenerateSTART(EEPROM_I2C, ENABLE);
    /* 等待EV5事件完成, SB=1(未设置检测时间超时, 不严谨) */
    while(I2C_GetFlagStatus(EEPROM_I2C, I2C_FLAG_SB) == RESET)
    {
       ;
    }
    /* STM32发送EEPROM的写地址 */
    I2C_Send7bitAddress(EEPROM_I2C, EEPROM_I2C_WRITE_ADDRESS, I2C_Direction_Transmitter);
    } while (I2C_GetFlagStatus(EEPROM_I2C, I2C_FLAG_ADDR) == RESET); 
    /* 循环监测EV6事件(ADDR=1)(接收)完成(未设置检测时间超时, 不严谨) */
    /* 结束轮询 */
    I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
}
```

#### 在main.c中进行读写测试

```c
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

uint8_t ReadData[20] = {0};
uint8_t WriteData[3] = {3, 4, 5};

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
    /* STM32向EEPROM 地址1写入数据0x01 */
    EEPROM_Byte_Writting(1, 0x01);
    /* ACKNOWLEDGE POLLING 确认询问 */
    EEPROM_ACK_Polling();
    /* STM32向EEPROM 地址2写入数据0x02 */
    EEPROM_Byte_Writting(2, 0x02);
    /* ACKNOWLEDGE POLLING 确认询问 */
    EEPROM_ACK_Polling();
    /*----------------------------------------
     * Page Writting的地址对齐
     * 为保证数据无误需addr%8 == 0
     *----------------------------------------*/ 
    /* STM32向EEPROM 地址3-5写入数据0x03-0x05 */
    EEPROM_Page_Writting(0x03, WriteData, 3);
    /* ACKNOWLEDGE POLLING 确认询问 */
    EEPROM_ACK_Polling();
    /* STM32从EEPROM以SequentialRead方式读取地址1-4的数据 */ 
    EEPROM_Sequential_Read((uint8_t)1, ReadData, 4);
    /* STM32从EEPROM以RandomRead方式读取地址5的数据 */ 
    EEPROM_Random_Read((uint8_t)5, &ReadData[4]);
    /* 将读出的数据循环打印 */
    for (uint8_t i = 0; i < 5; i++)
    {
        printf("ReadData[%d] = 0x%x\n", i, ReadData[i]);
    }
    
    /* 空循环 */
    while(1)
    {
        ;
    }
}

```

#### 串口实验现象

![实验现象](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401280831099.png)

#### 完善功能

以下函数是对实验中出现函数的进一步完善, 源文件不在工程中

##### 增加的宏定义

```c
/* STM32 I2C 快速模式 */
#define I2C_Speed              400000  //*

/* 这个地址只要与STM32外挂的I2C器件地址不一样即可 */
#define I2Cx_OWN_ADDRESS7      0X0A   

/* AT24C01/02每页有8个字节 */
#define I2C_PageSize           8

/* AT24C04/08A/16A每页有16个字节 */
//#define I2C_PageSize           16

/*等待超时时间*/
#define I2CT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT         ((uint32_t)(10 * I2CT_FLAG_TIMEOUT)
```

##### 调试功能

```c
#define EEPROM_DEBUG_ON         0

#define EEPROM_INFO(fmt,arg...)           printf("<<-EEPROM-INFO->> "fmt"\n",##arg)
#define EEPROM_ERROR(fmt,arg...)          printf("<<-EEPROM-ERROR->> "fmt"\n",##arg)
#define EEPROM_DEBUG(fmt,arg...)          do{\
                                          if(EEPROM_DEBUG_ON)\
                                          printf("<<-EEPROM-DEBUG->> [%s][%d]"fmt"\n", __FILE__, __LINE__, ##arg);\
                                          }while(0)
```

##### 超时处理函数

完善了对于超时的处理

###### 超时处理相关宏定义

```c
/*等待超时时间*/
#define I2CT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT         ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))
```

###### 超时处理相关变量声明

```c
static __IO uint32_t  I2CTimeout = I2CT_LONG_TIMEOUT;

static uint32_t I2C_TIMEOUT_UserCallback(uint8_t errorCode);
```

###### 超时状态函数

```c
/**
  * @brief  Basic management of the timeout situation.
  * @param  errorCode：错误代码，可以用来定位是哪个环节出错.
  * @retval 返回0，表示IIC读取失败.
  */
static  uint32_t I2C_TIMEOUT_UserCallback(uint8_t errorCode)
{
  /* Block communication and all processes */
  EEPROM_ERROR("I2C 等待超时!errorCode = %d",errorCode);
  
  return 0;
}
```

##### 多字节写入函数

完善了在Page Write中字节对齐的情况

```c
/**
  * @brief   将缓冲区中的数据写到I2C EEPROM中
  * @param   
  *  @arg pBuffer:缓冲区指针
  *  @arg WriteAddr:写地址
  *     @arg NumByteToWrite:写的字节数
  * @retval  无
  */
void I2C_EE_BufferWrite(u8* pBuffer, u8 WriteAddr, u16 NumByteToWrite)
{
  u8 NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0;

  Addr = WriteAddr % I2C_PageSize;
  count = I2C_PageSize - Addr;
  NumOfPage =  NumByteToWrite / I2C_PageSize;
  NumOfSingle = NumByteToWrite % I2C_PageSize;
 
  /* If WriteAddr is I2C_PageSize aligned  */
  if(Addr == 0) 
  {
    /* If NumByteToWrite < I2C_PageSize */
    if(NumOfPage == 0) 
    {
      I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);
      I2C_EE_WaitEepromStandbyState();
    }
    /* If NumByteToWrite > I2C_PageSize */
    else  
    {
      while(NumOfPage--)
      {
        I2C_EE_PageWrite(pBuffer, WriteAddr, I2C_PageSize); 
     I2C_EE_WaitEepromStandbyState();
        WriteAddr +=  I2C_PageSize;
        pBuffer += I2C_PageSize;
      }

      if(NumOfSingle!=0)
      {
        I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);
        I2C_EE_WaitEepromStandbyState();
      }
    }
  }
  /* If WriteAddr is not I2C_PageSize aligned  */
  else 
  {
    /* If NumByteToWrite < I2C_PageSize */
    if(NumOfPage== 0) 
    {
      I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);
      I2C_EE_WaitEepromStandbyState();
    }
    /* If NumByteToWrite > I2C_PageSize */
    else
    {
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / I2C_PageSize;
      NumOfSingle = NumByteToWrite % I2C_PageSize; 
      
      if(count != 0)
      {  
        I2C_EE_PageWrite(pBuffer, WriteAddr, count);
        I2C_EE_WaitEepromStandbyState();
        WriteAddr += count;
        pBuffer += count;
      } 
      
      while(NumOfPage--)
      {
        I2C_EE_PageWrite(pBuffer, WriteAddr, I2C_PageSize);
        I2C_EE_WaitEepromStandbyState();
        WriteAddr +=  I2C_PageSize;
        pBuffer += I2C_PageSize;  
      }
      if(NumOfSingle != 0)
      {
        I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle); 
        I2C_EE_WaitEepromStandbyState();
      }
    }
  }  
}
```

##### 单字节写入函数

增加超时处理

```c
/**
  * @brief   写一个字节到I2C EEPROM中
  * @param   
  * @arg pBuffer:缓冲区指针
  * @arg WriteAddr:写地址 
  * @retval  无
  */
uint32_t I2C_EE_ByteWrite(u8* pBuffer, u8 WriteAddr) 
{
  /* Send START condition */
  I2C_GenerateSTART(EEPROM_I2Cx, ENABLE);

  I2CTimeout = I2CT_FLAG_TIMEOUT;  
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_MODE_SELECT))  
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(0);
  } 
  
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Send EEPROM address for write */
  I2C_Send7bitAddress(EEPROM_I2Cx, EEPROM_ADDRESS, I2C_Direction_Transmitter);
  
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(1);
  }  
  /* Send the EEPROM's internal address to write to */
  I2C_SendData(EEPROM_I2Cx, WriteAddr);
  
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(2);
  } 
  
  /* Send the byte to be written */
  I2C_SendData(EEPROM_I2Cx, *pBuffer); 
  
  I2CTimeout = I2CT_FLAG_TIMEOUT;  
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(3);
  } 
  
  /* Send STOP condition */
  I2C_GenerateSTOP(EEPROM_I2Cx, ENABLE);
  
  return 1;
}
```

##### 单页写入函数

```c
/**
  * @brief   在EEPROM的一个写循环中可以写多个字节，但一次写入的字节数
  *          不能超过EEPROM页的大小，AT24C02每页有8个字节
  * @param   
  *     @arg pBuffer:缓冲区指针
  *     @arg WriteAddr:写地址
  *     @arg NumByteToWrite:写的字节数
  * @retval  无
  */
uint32_t I2C_EE_PageWrite(u8* pBuffer, u8 WriteAddr, u8 NumByteToWrite)
{
  I2CTimeout = I2CT_LONG_TIMEOUT;

  while(I2C_GetFlagStatus(EEPROM_I2Cx, I2C_FLAG_BUSY))   
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(4);
  } 
  
  /* Send START condition */
  I2C_GenerateSTART(EEPROM_I2Cx, ENABLE);
  
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_MODE_SELECT))  
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(5);
  } 
  
  /* Send EEPROM address for write */
  I2C_Send7bitAddress(EEPROM_I2Cx, EEPROM_ADDRESS, I2C_Direction_Transmitter);
  
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))  
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(6);
  } 
  
  /* Send the EEPROM's internal address to write to */    
  I2C_SendData(EEPROM_I2Cx, WriteAddr);  

  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV8 and clear it */
  while(! I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(7);
  } 

  /* While there is data to be written */
  while(NumByteToWrite--)  
  {
    /* Send the current byte */
    I2C_SendData(EEPROM_I2Cx, *pBuffer); 

    /* Point to the next byte to be written */
    pBuffer++; 
  
    I2CTimeout = I2CT_FLAG_TIMEOUT;

    /* Test on EV8 and clear it */
    while (!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
    {
      if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(8);
    } 
  }

  /* Send STOP condition */
  I2C_GenerateSTOP(EEPROM_I2Cx, ENABLE);
  
  return 1;
}
```

##### 读取数据函数

```c
/**
  * @brief   从EEPROM里面读取一块数据 
  * @param   
  *     @arg pBuffer:存放从EEPROM读取的数据的缓冲区指针
  *     @arg WriteAddr:接收数据的EEPROM的地址
  *     @arg NumByteToWrite:要从EEPROM读取的字节数
  * @retval  无
  */
uint32_t I2C_EE_BufferRead(u8* pBuffer, u8 ReadAddr, u16 NumByteToRead)
{  
  
  I2CTimeout = I2CT_LONG_TIMEOUT;
  
  //*((u8 *)0x4001080c) |=0x80; 
  while(I2C_GetFlagStatus(EEPROM_I2Cx, I2C_FLAG_BUSY))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(9);
   }
  
  /* Send START condition */
  I2C_GenerateSTART(EEPROM_I2Cx, ENABLE);
  //*((u8 *)0x4001080c) &=~0x80;
  
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(10);
   }
  
  /* Send EEPROM address for write */
  I2C_Send7bitAddress(EEPROM_I2Cx, EEPROM_ADDRESS, I2C_Direction_Transmitter);

  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(11);
   }
    
  /* Clear EV6 by setting again the PE bit */
  I2C_Cmd(EEPROM_I2Cx, ENABLE);

  /* Send the EEPROM's internal address to write to */
  I2C_SendData(EEPROM_I2Cx, ReadAddr);  

   
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(12);
   }
    
  /* Send START condition a second time */  
  I2C_GenerateSTART(EEPROM_I2Cx, ENABLE);
  
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(13);
   }
    
  /* Send EEPROM address for read */
  I2C_Send7bitAddress(EEPROM_I2Cx, EEPROM_ADDRESS, I2C_Direction_Receiver);
  
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(14);
   }
  
  /* While there is data to be read */
  while(NumByteToRead)  
  {
    if(NumByteToRead == 1)
    {
      /* Disable Acknowledgement */
      I2C_AcknowledgeConfig(EEPROM_I2Cx, DISABLE);
      
      /* Send STOP Condition */
      I2C_GenerateSTOP(EEPROM_I2Cx, ENABLE);
    }

    /* Test on EV7 and clear it */    
    I2CTimeout = I2CT_LONG_TIMEOUT;
    
    while(I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED)==0)  
    {
        if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(3);
    } 
    {      
      /* Read a byte from the EEPROM */
      *pBuffer = I2C_ReceiveData(EEPROM_I2Cx);

      /* Point to the next location where the byte read will be saved */
      pBuffer++; 
      
      /* Decrement the read bytes counter */
      NumByteToRead--;        
    }   
  }

  /* Enable Acknowledgement to be ready for another reception */
  I2C_AcknowledgeConfig(EEPROM_I2Cx, ENABLE);
  
    return 1;
}
```

##### 等待EEPROM函数

```c
/**
  * @brief  Wait for EEPROM Standby state 
  * @param  无
  * @retval 无
  */
void I2C_EE_WaitEepromStandbyState(void)      
{
  vu16 SR1_Tmp = 0;

  do
  {
    /* Send START condition */
    I2C_GenerateSTART(EEPROM_I2Cx, ENABLE);
    /* Read I2C1 SR1 register */
    SR1_Tmp = I2C_ReadRegister(EEPROM_I2Cx, I2C_Register_SR1);
    /* Send EEPROM address for write */
    I2C_Send7bitAddress(EEPROM_I2Cx, EEPROM_ADDRESS, I2C_Direction_Transmitter);
  }while(!(I2C_ReadRegister(EEPROM_I2Cx, I2C_Register_SR1) & 0x0002));
  
  /* Clear AF flag */
  I2C_ClearFlag(EEPROM_I2Cx, I2C_FLAG_AF);
    /* STOP condition */    
    I2C_GenerateSTOP(EEPROM_I2Cx, ENABLE); 
}
```

### 软件I2C

STM32硬件I2C有时会出现错误, 使用软件I2C实际上就是**通过GPIO模拟SCL和SDA的电平变换实现I2C协议**

#### 在bsp_i2c_ee.h中增加宏定义

```c
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

```

#### 在bsp_i2c_ee.c中写EEPROM的应用函数

```c
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

```

#### 在bsp_i2c_gpio.h中增加宏定义

```c
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

```

#### 在bsp_i2c_gpio.c中编写函数

```c
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

```

#### 在main.c函数中进行软件模拟I2C测试

```c
/**
  ******************************************************************************
  * @file    main.c
  * @author  eric
  * @version V0.0.1
  * @date    31-January-2024
  * @brief   STM32与EEPROM通过软件I2C进行读写测试
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FUCTIONS WHICH IS FOR GUIDANCE ONLY
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_i2c_ee.h"
#include "bsp_i2c_gpio.h"


/**
 * @brief 进行软件模拟I2C与EEPROM通信的读写测试 
 * @param None
 * @retval None 
 */
int main(void)
{
    /* LED_GPIO配置*/
    LED_GPIO_Config();
    /* 亮蓝灯 */
    LED_BLUE;
    /* USART初始化 */
    USART_Config();
    /* 打印测试开始信息 */
    printf("EEPROM Software Test Begin \r\n");
    if (ee_Test() == 1) /* 测试成功 */
    {
        /* 亮绿灯 */
        LED_GREEN;
    }
    else /* 测试不通过 */
    {
        /* 亮红灯 */
        LED_RED;
    }
    
    /* 空循环 */
    while(1)
    {
        ;
    }
}

```

### I2C读写小数

I2C读写小数在例程中有, 下面为例程中的代码(未进行分析)

#### 在bsp_i2c.h中

```c
#ifndef __I2C_EE_H
#define __I2C_EE_H


#include "stm32f10x.h"


/**************************I2C参数定义，I2C1或I2C2********************************/
#define             EEPROM_I2Cx                                I2C1
#define             EEPROM_I2C_APBxClock_FUN                   RCC_APB1PeriphClockCmd
#define             EEPROM_I2C_CLK                             RCC_APB1Periph_I2C1
#define             EEPROM_I2C_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define             EEPROM_I2C_GPIO_CLK                        RCC_APB2Periph_GPIOB     
#define             EEPROM_I2C_SCL_PORT                        GPIOB   
#define             EEPROM_I2C_SCL_PIN                         GPIO_Pin_6
#define             EEPROM_I2C_SDA_PORT                        GPIOB 
#define             EEPROM_I2C_SDA_PIN                         GPIO_Pin_7


/*等待超时时间*/
#define I2CT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT         ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))


/*信息输出*/
#define EEPROM_DEBUG_ON         0

#define EEPROM_INFO(fmt,arg...)           printf("<<-EEPROM-INFO->> "fmt"\n",##arg)
#define EEPROM_ERROR(fmt,arg...)          printf("<<-EEPROM-ERROR->> "fmt"\n",##arg)
#define EEPROM_DEBUG(fmt,arg...)          do{\
                                          if(EEPROM_DEBUG_ON)\
                                          printf("<<-EEPROM-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
                                          }while(0)


/* 
 * AT24C02 2kb = 2048bit = 2048/8 B = 256 B
 * 32 pages of 8 bytes each
 *
 * Device Address
 * 1 0 1 0 A2 A1 A0 R/W
 * 1 0 1 0 0  0  0  0 = 0XA0
 * 1 0 1 0 0  0  0  1 = 0XA1 
 */

/* EEPROM Addresses defines */
#define EEPROM_Block0_ADDRESS 0xA0   /* E2 = 0 */
//#define EEPROM_Block1_ADDRESS 0xA2 /* E2 = 0 */
//#define EEPROM_Block2_ADDRESS 0xA4 /* E2 = 0 */
//#define EEPROM_Block3_ADDRESS 0xA6 /* E2 = 0 */


void I2C_EE_Init(void);
void I2C_EE_BufferWrite(u8* pBuffer, u8 WriteAddr, u16 NumByteToWrite);
uint32_t I2C_EE_ByteWrite(u8* pBuffer, u8 WriteAddr);
uint32_t I2C_EE_PageWrite(u8* pBuffer, u8 WriteAddr, u8 NumByteToWrite);
uint32_t I2C_EE_BufferRead(u8* pBuffer, u8 ReadAddr, u16 NumByteToRead);
void I2C_EE_WaitEepromStandbyState(void);


#endif /* __I2C_EE_H */

```

#### 在bsp_i2c_ee.c中

```c
/**
  ******************************************************************************
  * @file    bsp_i2c_ee.c
  * @author  STMicroelectronics
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   i2c EEPROM(AT24C02)应用函数bsp
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 F103-霸道 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 

#include "./i2c/bsp_i2c_ee.h"
#include "./usart/bsp_usart.h"  

/* STM32 I2C 快速模式 */
#define I2C_Speed              400000  //*

/* 这个地址只要与STM32外挂的I2C器件地址不一样即可 */
#define I2Cx_OWN_ADDRESS7      0X0A   

/* AT24C01/02每页有8个字节 */
#define I2C_PageSize           8

/* AT24C04/08A/16A每页有16个字节 */
//#define I2C_PageSize           16 


uint16_t EEPROM_ADDRESS;

static __IO uint32_t  I2CTimeout = I2CT_LONG_TIMEOUT;   


static uint32_t I2C_TIMEOUT_UserCallback(uint8_t errorCode);


/**
  * @brief  I2C I/O配置
  * @param  无
  * @retval 无
  */
static void I2C_GPIO_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure; 

    /* 使能与 I2C 有关的时钟 */
    EEPROM_I2C_APBxClock_FUN ( EEPROM_I2C_CLK, ENABLE );
    EEPROM_I2C_GPIO_APBxClock_FUN ( EEPROM_I2C_GPIO_CLK, ENABLE );

    
    /* I2C_SCL、I2C_SDA*/
    GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SCL_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;       // 开漏输出
    GPIO_Init(EEPROM_I2C_SCL_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SDA_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;       // 开漏输出
    GPIO_Init(EEPROM_I2C_SDA_PORT, &GPIO_InitStructure);
}


/**
  * @brief  I2C 工作模式配置
  * @param  无
  * @retval 无
  */
static void I2C_Mode_Configu(void)
{
    I2C_InitTypeDef  I2C_InitStructure; 

    /* I2C 配置 */
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;

    /* 高电平数据稳定，低电平数据变化 SCL 时钟线的占空比 */
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;

    I2C_InitStructure.I2C_OwnAddress1 =I2Cx_OWN_ADDRESS7; 
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable ;

    /* I2C的寻址模式 */
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;

    /* 通信速率 */
    I2C_InitStructure.I2C_ClockSpeed = I2C_Speed;

    /* I2C 初始化 */
    I2C_Init(EEPROM_I2Cx, &I2C_InitStructure);
  
    /* 使能 I2C */
    I2C_Cmd(EEPROM_I2Cx, ENABLE);   
}


/**
  * @brief  I2C 外设(EEPROM)初始化
  * @param  无
  * @retval 无
  */
void I2C_EE_Init(void)
{

  I2C_GPIO_Config(); 
 
  I2C_Mode_Configu();

/* 根据头文件i2c_ee.h中的定义来选择EEPROM要写入的地址 */
#ifdef EEPROM_Block0_ADDRESS
  /* 选择 EEPROM Block0 来写入 */
  EEPROM_ADDRESS = EEPROM_Block0_ADDRESS;
#endif

#ifdef EEPROM_Block1_ADDRESS  
    /* 选择 EEPROM Block1 来写入 */
  EEPROM_ADDRESS = EEPROM_Block1_ADDRESS;
#endif

#ifdef EEPROM_Block2_ADDRESS  
    /* 选择 EEPROM Block2 来写入 */
  EEPROM_ADDRESS = EEPROM_Block2_ADDRESS;
#endif

#ifdef EEPROM_Block3_ADDRESS  
    /* 选择 EEPROM Block3 来写入 */
  EEPROM_ADDRESS = EEPROM_Block3_ADDRESS;
#endif
}


/**
  * @brief   将缓冲区中的数据写到I2C EEPROM中
  * @param   
  *   @arg pBuffer:缓冲区指针
  *   @arg WriteAddr:写地址
  *   @arg NumByteToWrite:写的字节数
  * @retval  无
  */
void I2C_EE_BufferWrite(u8* pBuffer, u8 WriteAddr, u16 NumByteToWrite)
{
  u8 NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0;

  Addr = WriteAddr % I2C_PageSize;
  count = I2C_PageSize - Addr;
  NumOfPage =  NumByteToWrite / I2C_PageSize;
  NumOfSingle = NumByteToWrite % I2C_PageSize;
 
  /* If WriteAddr is I2C_PageSize aligned  */
  if(Addr == 0) 
  {
    /* If NumByteToWrite < I2C_PageSize */
    if(NumOfPage == 0) 
    {
      I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);
      I2C_EE_WaitEepromStandbyState();
    }
    /* If NumByteToWrite > I2C_PageSize */
    else  
    {
      while(NumOfPage--)
      {
        I2C_EE_PageWrite(pBuffer, WriteAddr, I2C_PageSize); 
        I2C_EE_WaitEepromStandbyState();
        WriteAddr +=  I2C_PageSize;
        pBuffer += I2C_PageSize;
      }

      if(NumOfSingle!=0)
      {
        I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);
        I2C_EE_WaitEepromStandbyState();
      }
    }
  }
  /* If WriteAddr is not I2C_PageSize aligned  */
  else 
  {
    /* If NumByteToWrite < I2C_PageSize */
    if(NumOfPage== 0) 
    {
      I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);
      I2C_EE_WaitEepromStandbyState();
    }
    /* If NumByteToWrite > I2C_PageSize */
    else
    {
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / I2C_PageSize;
      NumOfSingle = NumByteToWrite % I2C_PageSize;
      
      if(count != 0)
      {  
        I2C_EE_PageWrite(pBuffer, WriteAddr, count);
        I2C_EE_WaitEepromStandbyState();
        WriteAddr += count;
        pBuffer += count;
      } 
      
      while(NumOfPage--)
      {
        I2C_EE_PageWrite(pBuffer, WriteAddr, I2C_PageSize);
        I2C_EE_WaitEepromStandbyState();
        WriteAddr +=  I2C_PageSize;
        pBuffer += I2C_PageSize;  
      }
      if(NumOfSingle != 0)
      {
        I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle); 
        I2C_EE_WaitEepromStandbyState();
      }
    }
  }  
}


/**
  * @brief   写一个字节到I2C EEPROM中
  * @param   
  *   @arg pBuffer:缓冲区指针
  *   @arg WriteAddr:写地址 
  * @retval  无
  */
uint32_t I2C_EE_ByteWrite(u8* pBuffer, u8 WriteAddr) 
{
  /* Send STRAT condition */
  I2C_GenerateSTART(EEPROM_I2Cx, ENABLE);

  I2CTimeout = I2CT_FLAG_TIMEOUT;  
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_MODE_SELECT))  
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(0);
  } 
  
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Send EEPROM address for write */
  I2C_Send7bitAddress(EEPROM_I2Cx, EEPROM_ADDRESS, I2C_Direction_Transmitter);
  
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(1);
  }  
  /* Send the EEPROM's internal address to write to */
  I2C_SendData(EEPROM_I2Cx, WriteAddr);
  
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(2);
  } 
  
  /* Send the byte to be written */
  I2C_SendData(EEPROM_I2Cx, *pBuffer); 
  
  I2CTimeout = I2CT_FLAG_TIMEOUT;  
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(3);
  } 
  
  /* Send STOP condition */
  I2C_GenerateSTOP(EEPROM_I2Cx, ENABLE);
  
  return 1;
}


/**
  * @brief   在EEPROM的一个写循环中可以写多个字节，但一次写入的字节数
  *          不能超过EEPROM页的大小，AT24C02每页有8个字节
  * @param   
  *   @arg pBuffer:缓冲区指针
  *   @arg WriteAddr:写地址
  *   @arg NumByteToWrite:写的字节数
  * @retval  无
  */
uint32_t I2C_EE_PageWrite(u8* pBuffer, u8 WriteAddr, u8 NumByteToWrite)
{
  I2CTimeout = I2CT_LONG_TIMEOUT;

  while(I2C_GetFlagStatus(EEPROM_I2Cx, I2C_FLAG_BUSY))   
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(4);
  } 
  
  /* Send START condition */
  I2C_GenerateSTART(EEPROM_I2Cx, ENABLE);
  
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_MODE_SELECT))  
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(5);
  } 
  
  /* Send EEPROM address for write */
  I2C_Send7bitAddress(EEPROM_I2Cx, EEPROM_ADDRESS, I2C_Direction_Transmitter);
  
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))  
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(6);
  } 
  
  /* Send the EEPROM's internal address to write to */    
  I2C_SendData(EEPROM_I2Cx, WriteAddr);  

  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV8 and clear it */
  while(! I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(7);
  } 

  /* While there is data to be written */
  while(NumByteToWrite--)  
  {
    /* Send the current byte */
    I2C_SendData(EEPROM_I2Cx, *pBuffer); 

    /* Point to the next byte to be written */
    pBuffer++; 
  
    I2CTimeout = I2CT_FLAG_TIMEOUT;

    /* Test on EV8 and clear it */
    while (!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
    {
      if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(8);
    } 
  }

  /* Send STOP condition */
  I2C_GenerateSTOP(EEPROM_I2Cx, ENABLE);
  
  return 1;
}


/**
  * @brief   从EEPROM里面读取一块数据 
  * @param   
  *   @arg pBuffer:存放从EEPROM读取的数据的缓冲区指针
  *   @arg WriteAddr:接收数据的EEPROM的地址
  *   @arg NumByteToWrite:要从EEPROM读取的字节数
  * @retval  无
  */
uint32_t I2C_EE_BufferRead(u8* pBuffer, u8 ReadAddr, u16 NumByteToRead)
{  
  
  I2CTimeout = I2CT_LONG_TIMEOUT;
  
  //*((u8 *)0x4001080c) |=0x80; 
  while(I2C_GetFlagStatus(EEPROM_I2Cx, I2C_FLAG_BUSY))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(9);
   }
  
  /* Send START condition */
  I2C_GenerateSTART(EEPROM_I2Cx, ENABLE);
  //*((u8 *)0x4001080c) &=~0x80;
  
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(10);
   }
  
  /* Send EEPROM address for write */
  I2C_Send7bitAddress(EEPROM_I2Cx, EEPROM_ADDRESS, I2C_Direction_Transmitter);

  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(11);
   }
    
  /* Clear EV6 by setting again the PE bit */
  I2C_Cmd(EEPROM_I2Cx, ENABLE);

  /* Send the EEPROM's internal address to write to */
  I2C_SendData(EEPROM_I2Cx, ReadAddr);  

   
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(12);
   }
    
  /* Send STRAT condition a second time */  
  I2C_GenerateSTART(EEPROM_I2Cx, ENABLE);
  
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(13);
   }
    
  /* Send EEPROM address for read */
  I2C_Send7bitAddress(EEPROM_I2Cx, EEPROM_ADDRESS, I2C_Direction_Receiver);
  
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(14);
   }
  
  /* While there is data to be read */
  while(NumByteToRead)  
  {
    if(NumByteToRead == 1)
    {
      /* Disable Acknowledgement */
      I2C_AcknowledgeConfig(EEPROM_I2Cx, DISABLE);
      
      /* Send STOP Condition */
      I2C_GenerateSTOP(EEPROM_I2Cx, ENABLE);
    }

    /* Test on EV7 and clear it */    
    I2CTimeout = I2CT_LONG_TIMEOUT;
    
    while(I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED)==0)  
    {
        if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(3);
    } 
    {      
      /* Read a byte from the EEPROM */
      *pBuffer = I2C_ReceiveData(EEPROM_I2Cx);

      /* Point to the next location where the byte read will be saved */
      pBuffer++; 
      
      /* Decrement the read bytes counter */
      NumByteToRead--;        
    }   
  }

  /* Enable Acknowledgement to be ready for another reception */
  I2C_AcknowledgeConfig(EEPROM_I2Cx, ENABLE);
  
    return 1;
}


/**
  * @brief  Wait for EEPROM Standby state 
  * @param  无
  * @retval 无
  */
void I2C_EE_WaitEepromStandbyState(void)      
{
  vu16 SR1_Tmp = 0;

  do
  {
    /* Send START condition */
    I2C_GenerateSTART(EEPROM_I2Cx, ENABLE);
    /* Read I2C1 SR1 register */
    SR1_Tmp = I2C_ReadRegister(EEPROM_I2Cx, I2C_Register_SR1);
    /* Send EEPROM address for write */
    I2C_Send7bitAddress(EEPROM_I2Cx, EEPROM_ADDRESS, I2C_Direction_Transmitter);
  }while(!(I2C_ReadRegister(EEPROM_I2Cx, I2C_Register_SR1) & 0x0002));
  
  /* Clear AF flag */
  I2C_ClearFlag(EEPROM_I2Cx, I2C_FLAG_AF);
    /* STOP condition */    
    I2C_GenerateSTOP(EEPROM_I2Cx, ENABLE); 
}




/**
  * @brief  Basic management of the timeout situation.
  * @param  errorCode：错误代码，可以用来定位是哪个环节出错.
  * @retval 返回0，表示IIC读取失败.
  */
static  uint32_t I2C_TIMEOUT_UserCallback(uint8_t errorCode)
{
  /* Block communication and all processes */
  EEPROM_ERROR("I2C 等待超时!errorCode = %d",errorCode);
  
  return 0;
}
/*********************************************END OF FILE**********************/


```

#### 在main.c中

```c
/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   I2C EEPROM(AT24C02)测试，存储小数
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 F103-霸道 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f10x.h"
#include "./usart/bsp_usart.h"
#include "./i2c/bsp_i2c_ee.h"
#include "./led/bsp_led.h"
#include <string.h>


uint8_t cal_flag = 0;
uint8_t k;

/*存储小数和整数的数组，各7个*/
long double double_buffer[7] = {0};
int int_bufffer[7] = {0};

#define DOUBLE_ADDR       10
#define LONGINT_ADDR      70

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{ 
  LED_GPIO_Config();

  /* 串口初始化 */
    USART_Config();

    printf("\r\n 这是一个EEPROM 读写小数和长整数实验 \r\n");

    /* I2C 外设初(AT24C02)始化 */
    I2C_EE_Init();

    /*读取数据标志位*/
    I2C_EE_BufferRead(&cal_flag, 0, 1);
  
    if( cal_flag != 0xCD ) /*若标志等于0xcd，表示之前已有写入数据*/
    {      
        printf("\r\n没有检测到数据标志，FLASH没有存储数据，即将进行小数写入实验\r\n");
        cal_flag =0xCD;
        
        /*写入标志到0地址*/
        I2C_EE_BufferWrite(&cal_flag, 0, 1); 
        
        /*生成要写入的数据*/
        for( k=0; k<7; k++ )
        {
           double_buffer[k] = k +0.1;
           int_bufffer[k]=k*500+1 ;
        }

        /*写入小数数据到地址10*/
        I2C_EE_BufferWrite((void*)double_buffer,DOUBLE_ADDR, sizeof(double_buffer));
        /*写入整数数据到地址60*/
        I2C_EE_BufferWrite((void*)int_bufffer, LONGINT_ADDR, sizeof(int_bufffer));
              
        printf("向芯片写入数据：");
        /*打印到串口*/
        for( k=0; k<7; k++ )
        {
          printf("小数tx = %LF\r\n",double_buffer[k]);
          printf("整数tx = %d\r\n",int_bufffer[k]);
        }
        
        printf("\r\n请复位开发板，以读取数据进行检验\r\n");      
    }    
    else
    {
        printf("\r\n检测到数据标志\r\n");

        /*读取小数数据*/
        I2C_EE_BufferRead((void*)double_buffer, DOUBLE_ADDR, sizeof(double_buffer));

        /*读取整数数据*/
        I2C_EE_BufferRead((void*)int_bufffer, LONGINT_ADDR, sizeof(int_bufffer));
        printf("\r\n从芯片读到数据：\r\n");
        for( k=0; k<7; k++ )
        {
            printf("小数 rx = %LF \r\n",double_buffer[k]);
            printf("整数 rx = %d \r\n",int_bufffer[k]);
        }
      
    }   

  
  while (1)
  {      
  }
}

/*********************************************END OF FILE**********************/

```

## SPI-FLASH

### SPI协议

SPI（Serial Peripheral Interface）是一种**同步的串行通信协议**，用于在多个设备之间进行数据传输。SPI通常用于连接微控制器（MCU）与外设，例如传感器、存储器、显示器、无线模块等。

#### SPI协议的基本特征

- 主从结构： SPI通信通常包括一个主设备（Master）和一个或多个从设备（Slave）。主设备负责控制通信的时序和信号，而从设备则被动地响应主设备的指令。
- 全双工通信： SPI支持全双工通信，即主设备和从设备可以同时发送和接收数据。这通过使用两条数据线（MISO - Master In Slave Out 和 MOSI - Master Out Slave In）实现。
- 多设备选择： SPI总线通常有一个片选信号（Chip Select，CS）线，用于选择与主设备通信的特定从设备。每个从设备都有一个独立的片选线。
- 时钟信号： SPI通信使用一个时钟信号（SCLK）来同步主设备和从设备的数据传输。时钟的极性和相位可以配置，以适应不同设备的时钟要求。
- 数据格式： SPI支持多种数据格式，包括不同的数据位数和传输顺序。常见的有CPOL（时钟极性）和 CPHA（时钟相位）两个参数，它们决定了时钟信号的起始边沿和数据采样时机。

#### SPI的通信过程

1. 主设备拉低片选线，选择一个从设备。
2. 主设备通过时钟信号（SCLK）同步数据传输。
3. 主设备通过 MOSI 发送数据到从设备。
4. 从设备通过 MISO 返回数据到主设备。
5. 数据传输完成后，主设备拉高片选线，表示结束与从设备的通信。

**SPI通信速度通常较快，适用于需要高速数据传输的应用**, SPI协议是一种灵活、简单且广泛使用的串行通信协议，但它通常**局限于短距离通信，且没有内建的错误检测和纠正机制**

### STM32的SPI特性及框架

#### SPI物理层

![SPI物理层](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402032017786.png)

##### SS线

![SS线](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402032019762.png)

SS线一般用软件编程GPIO进行模拟

##### SCK线

![SCK线](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402032024467.png)

在STM32F103中SPI1挂载在APB2总线, 最大频率为fpclk2/2=35MHz

在STM32F103中SPI2,3挂载在APB1总线, 最大频率为fpclk1/2=18MHz

##### MOSI和MISO线

![MOSI和MISO线](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402032149125.png)

#### SPI协议层

##### SPI基本通讯过程

![SPI基本通讯过程](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402032151968.png)

1. NSS信号由高电平变为低电平时通讯开始
2. SCK的采样边沿需要根据CPOL/CPHA的配置进行确定
3. 在SCK触发阶段, MOSI和MISO电平进行变化
4. 在SCK采样阶段, MOSI和MISO电平进行采样

##### CPOL/CPHA配置

![CPOL/CPHA配置](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402032223490.png)

![CPOL](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402032224540.png)

CPOL为1时, SCK在空闲时为高电平, 为0时, SCK在空闲时为低电平

![CPHA](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402032226805.png)

CPHA为1时,MOSI/MISO信号在SCK的奇数边缘采样, 为0时, MOSI/MISO信号在SCK的偶数边缘采样

![CPOL/CPHA配置](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402032254718.png)

![SPI架构](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402071826806.png)

#### SPI通讯引脚

![SPI通讯引脚框图](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402071915673.png)

![通讯引脚](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402071828184.png)

NSS一般使用软件控制引脚

#### SPI时钟控制逻辑

![SPI时钟控制逻辑框图](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402071915991.png)

![时钟控制逻辑](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402071906446.png)

在SPI_CR1[5:3]BR控制波特率

![SPI_CR1](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402071908631.png)

#### SPI数据控制逻辑

![SPI数据控制逻辑框图](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402071914015.png)

![数据控制逻辑](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402071912928.png)

#### SPI整体控制逻辑

![SPI整体控制逻辑](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402071941301.png)

##### SPI_CR1寄存器

![SPI_CR1](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402071943925.png)

- BIDIMODE: 一般选择双线双向
- BIDIOE: 一般不使用
- CRCEN: 一般不使用

![SPI_CR1](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402071947289.png)

- DFF: 一般使用8位数据帧格式
- RXONLY: 一般使用全双工
- SSM: 一般使用软件从设备管理

![SPI_CR1](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402071950557.png)

- LSBFIRST: 需要与外设配合
- SPE: 使能SPI
- BR[2:0]: 控制波特率
- MSTR: 配置主从设备

![SPI_CR1](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402071953199.png)

- CPOL: 配置时钟极性
- CPHA: 配置时钟相位

##### SPI_SR寄存器

![SPI_SR](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402071955579.png)

![SPI_SR](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402071955069.png)

- TXE: 判断发送缓冲区是否为空
- RXNE: 判断接收缓冲是否为空

#### SPI通讯过程

![SPI通讯过程](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402071957471.png)

SPI发送数据流程

1. 软件向SPI_DR写入数据
2. 等待TXE标志位置1
3. 置1后再向SPI_DR中写入下一个字节的数据

SPI接收数据流程

1. 从外部接收数据
2. 等待RXNE标志位置1
3. 读取SPI_DR可获取接收到的数据
4. RXNE为1后继续从SPI_DR读取下一个接收到的数据

SPI发送和接收是同时进行的, 就算只接收数据也要往发送缓冲区写入数据, 才能触发SCL产生时钟, 才能正常接收数据

### SPI初始化结构体

#### SPI结构体成员

![SPI结构体](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402072019171.png)

##### SPI_BaudRatePrescaler

![SPI_BandRatePrescaler](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402072045060.png)

配置分频因子为2,4,8....分频

##### SPI_CPHA

![SPI_CPHA](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402072040368.png)

- SPI_CPHA_1Edge: 奇数边缘采样
- SPI_CPHA_2Edge: 偶数边缘采样

##### SPI_CPOL

![SPI_CPOL](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402072031998.png)

- SPI_CPOL_High: SPI空闲为高电平
- SPI_CPOL_Low: SPI空闲为低电平

##### SPI_CRCPolynomial

一般不使用CRC校验

##### SPI_DataSize

![SPI_DataSize](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402072029684.png)

- SPI_DataSize_16b: 配置数据帧长度为16位
- SPI_DataSize_8b: 配置数据帧长度为8位

##### SPI_Direction

![SPI_Direction](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402072020594.png)

- SPI_Direction_1Line_Rx: 单线只接收
- SPI_Direction_1Line_Tx: 单线只发送
- SPI_Direction_2Lines_FullDuplex: 双线全双工
- SPI_Direction_2Lines_RxOnly: 双线只接收

##### SPI_FirstBit

![SPI_FirstBit](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402072047473.png)

- SPI_FirstBit_LSB: 低位先行
- SPI_FirstBit_MSB: 高位先行

一般配置为高位先行

##### SPI_Mode

![SPI_Mode](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402072025148.png)

- SPI_Mode_Master: STM32作为主机
- SPI_Mode_Slave: STM32作为从机

二者区别在于, SPI的SCK时序是从主机中产生还是接收外来的SCK信号

##### SPI_NSS

![SPI_NSS](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402072043580.png)

- SPI_NSS_Hard: 硬件配置NSS
- SPI_NSS_Soft: 软件配置NSS

#### SPI初始化函数

##### SPI_Init

![SPI_Init](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402072050625.png)

使用SPI_Init函数进行初始化

##### SPI_Cmd

![SPI_Cmd](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402072051840.png)

使用SPI_Cmd函数进行使能

### W25Q64介绍

#### W25Q64引脚封装

![W25Q64引脚封装](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402072057650.png)

![W25Q64引脚封装](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402072100352.png)

- /CS: 相当于NSS
- DO(IO1): 相当于MISO
- /WP(I02): 输入写保护, 低电平有效
- DI(IO0): 相当于MOSI
- GND: 地
- VCC: 电源
- /HOLD(IO3): 暂停通讯, 低电平有效
- CLK: 相当于SCK

#### W25Q64框图

![W25Q64框图](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402072114893.png)

1. 将8M字节分为128个64KB的块(Block)
2. 将64KB分为16个4KB的扇区(Sector)

Flash的存储特性:

1. 在写入数据前必须先擦除
2. 擦除时会把数据位全部重置为1
3. 在写入数据时只能把为1的数据位改为0
4. 擦除时必须按照最小单位(一般为扇区Sector)进行擦除

#### W25Q64指令表

![W25Q64指令表](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402072201185.png)

![W25Q64指令表](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402072202647.png)

#### 开发板W25Q64原理图

![W25Q64](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202402101724960.png)

- /CE: 片选, 后续会使用软件方法
- SCK: 信号线, 接PA5
- SI_IO0: MOSI线, 接PA7
- SI_IO1: MISO中
- /WP_IO2: 写保护接高电平, 不使用
- /HOLD_IO3: 暂停通讯, 接高电平, 不使用

### SPI-FLASH读写测试

项目地址: **25-SPI-FLASH-RW**

注: 并未完全进行测试
