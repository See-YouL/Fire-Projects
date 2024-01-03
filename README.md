# 野火霸道V2开发板学习笔记

## 说明

**本库仅供学习交流使用**

- 编译器： ARM v5.06
- C编译版本: C99
- 固件库版本: V3.5.0
- MDK version: 538A
- 芯片包: Keil.STM32F1xx_DFP.2.4.1
- 芯片型号: STM32F103ZET6
- 参考视频: 【【单片机】野火STM32F103教学视频 (配套霸道/指南者/MINI)【全】(刘火良老师出品) (无字幕)】 https://www.bilibili.com/video/BV1yW411Y7Gw/?p=9&share_source=copy_web&vd_source=0db47c15b9f51dbaa4548ec2dc55dea4

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

- &= ~(1 << n); **将bitn清零,其他位保持不变**
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

**推挽输出的含义**

![推挽输出含义图](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/%E6%88%AA%E5%B1%8F2023-12-28%2015.23.18.png)

- PMOS导通时, OUT处电流向外称为**推**, 此时电流称为**灌电流**
- NMOS导通时, OUT处电流向里称为**挽**, 此时电流称为**拉电流**

推挽输出（Push-Pull Output）是一种常见的电子电路输出类型，特别是在数字电路和微控制器的GPIO（通用输入/输出）引脚中。这种输出类型的**主要特点是它使用两个晶体管（一个N型和一个P型）来控制输出引脚的电压状态。**

**原理**

在推挽配置中，通常有两个晶体管：

- N型晶体管：当被激活（或导通）时，它将输出引脚连接到地（GND），从而产生低电平（0）输出。
- P型晶体管：当被激活时，它将输出引脚连接到正电源（VCC），从而产生高电平（1）输出。

这两个晶体管不会同时导通，以避免短路。在任何给定的时刻，要么N型晶体管导通将输出拉低，要么P型晶体管导通将输出拉高。

**特点**

- 强驱动能力：**推挽输出可以提供较强的电流驱动能力**，无论是向输出引脚提供电流（高电平）还是从引脚吸收电流（低电平）。
- 确定的逻辑状态：输出要么明确地是高电平，要么是低电平，**不会处于悬空（高阻态）状态**。
- 无需外部上拉或下拉电阻：由于**推挽输出自身就可以明确地驱动高电平或低电平**，因此不需要外部的上拉或下拉电阻来确保稳定的输出状态。

**应用**

推挽输出广泛应用于各种数字电路，特别是**在需要驱动LED、继电器或其他需要较高电流的负载时**。由于其**强大的驱动能力和清晰的逻辑电平**，推挽输出是实现**数字信号传输**的理想选择。

**对比开漏（Open-Drain）/开集（Open-Collector）**

与推挽输出相对的是开漏（在MOSFET技术中）或开集（在双极晶体管技术中）输出，**这种类型的输出只有一个晶体管，要么将输出拉低，要么让它悬空（高阻态）**。开漏/开集输出**需要外部上拉电阻来确保高电平状态**，常用于需要多个设备共享同一输出线的应用，如I2C通信协议。

#### 开漏输出

**内部只能输出低电平,不能输出高电平**

![当ODR为1时开漏输出原理图](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/%E6%88%AA%E5%B1%8F2023-12-28%2015.23.18.png)

ODR=1, 经反相器为0, Vg=0V=Vs=0V, NMOS管截止, 此时OUT为高阻态悬空, 加入外部上拉电阻后, OUT=1

如果外部需要高电平驱动可以通过更换外部上拉电路来进行更换

![当ODR为0时开漏输出原理图](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/%E6%88%AA%E5%B1%8F2023-12-28%2016.06.58.png)

ODR=0, 经反相器为1, Vg=1 > Vs=0, NMOS管导通, 此时OUT=0V

开漏输出（Open-Drain Output，在使用MOSFET技术的情况下称为开漏，而在使用双极性晶体管的情况下称为开集（Open-Collector）输出）是一种常见的电子电路设计，特别是在数字电路和微控制器的GPIO（通用输入/输出）引脚中。这种输出类型的**主要特点是它使用单个晶体管来控制输出引脚的电压状态，而不是像推挽输出那样使用两个晶体管。**

**开漏输出的原理**

在开漏配置中，只有一个N型晶体管：

- N型晶体管：当晶体管导通（激活）时，它将输出引脚连接到地（GND），产生低电平（0）输出。当晶体管关闭（非激活）时，输出引脚不连接到任何东西，处于悬空状态。
- 由于输出在晶体管关闭时处于悬空状态，因此通常需要一个外部的上拉电阻连接到正电源（VCC），以确保当晶体管关闭时输出能够达到高电平（1）。

**特点**

- 单向驱动能力：开漏输出**只能将输出拉低，不能主动驱动高电平**。
- 需要外部上拉电阻：**为了确保输出能够达到高电平，需要外部上拉电阻**。
- 适合于总线和共享线路：开漏输出非常**适合于多个设备共享同一输出线的应用**，因为任何一个设备都可以将线路拉低，而不会对其他设备造成干扰。

**应用**

开漏输出**常用于需要多个设备共享同一通信线路的场合**，如I2C和1-Wire通信协议。在这些应用中，**多个设备可以连接到同一条线路上，每个设备都可以通过将线路拉低来发送信号，而不会影响其他设备。**

**对比推挽输出**

与开漏输出相对的是推挽输出，后者使用两个晶体管（一个N型和一个P型）来分别驱动高电平和低电平。推挽输出可以主动驱动高电平和低电平，而**开漏输出只能驱动低电平，需要外部上拉电阻来实现高电平状态。**

#### 补充: 高阻态与悬空

**高阻态（High-Impedance State），通常简称为Hi-Z**，是电子电路中的一个术语，用来描述一个电路节点在特定条件下呈现出非常高电阻的状态。在这种状态下，**电路节点既不明显地连接到电源（高电平），也不明显地连接到地（低电平）**。换句话说，这个节点处于一种“断开”或“浮空”的状态，对电路中的其他部分几乎没有任何电气影响。

**高阻态的应用**

- **三态逻辑（Tri-state Logic）**：在数字电路中，高阻态常用于三态逻辑，**允许多个输出连接到同一个线路或总线上，而不会相互干扰**只有被选中的设备会将其输出置于低电阻状态（高电平或低电平），其他设备的输出则处于高阻态。
- **总线系统**：在微处理器、微控制器和其他数字系统的总线（如数据总线、地址总线）上，高阻态用于控制哪个设备可以在特定时刻向总线发送数据。
- **输入/输出端口**：在可编程的微控制器的GPIO（通用输入/输出）端口中，**高阻态可以用来防止未使用的或被配置为输入的端口对电路造成影响**。

**高阻态的重要性**

- **避免冲突**：在多个设备共享同一通信线路时，高阻态可以防止输出冲突。
- **节能**：当端口处于高阻态时，它几乎不消耗电流，有助于降低功耗。
- **灵活性**：高阻态提供了电路设计的灵活性，特别是在需要多个设备共享同一资源的情况下。

**注意事项**

- **浮动电压**：当一个端口或线路处于高阻态时，它可能会因为电磁干扰或静电感应而捕获不确定的电压，**有时可能需要通过上拉或下拉电阻来确保稳定的逻辑状态**。
- **设计考虑**：在设计电路和编写程序时，需要考虑到高阻态的影响，确保在适当的时候启用或禁用高阻态。

在电子电路中，**“悬空”（Floating）是指一个电路节点没有被明确连接到电源（高电平）或地（低电平），也没有通过任何电阻或其他电子元件连接到其他电路节点的状态**这种状态下的节点电压是不确定的，因为它既不是被固定在逻辑高也不是逻辑低，而是可以随外部电磁场或附近电路的状态变化而变化。

**悬空状态的特点**

- 不确定的电压：悬空的节点可能会随机地捕获周围环境的电磁干扰，导致其电压处于不确定的状态。
- 易受干扰：由于没有明确的电气连接，悬空的节点容易受到外部电磁干扰的影响。
- 可能导致问题：在数字电路中，悬空的输入引脚可能导致不稳定的逻辑状态，从而引发电路的不可预测行为。

**高阻态与悬空的关系**

高阻态是一种特定的电路配置，**其中一个节点（如微控制器的GPIO引脚）被设置为非常高的电阻状态。这意味着该节点对电路的其他部分几乎没有电气影响，类似于断开连接**因此，**当一个引脚被设置为高阻态时，它实际上是在悬空状态**，因为它既不是明确地连接到高电平也不是低电平。

**区别和联系**

- 联系：**高阻态通常会导致节点悬空**当一个节点处于高阻态时，由于其极高的电阻值，它实际上与电路的其他部分隔离，从而处于悬空状态。
- 区别：**高阻态是一种有意设置的电路状态**，用于特定的目的（如防止总线冲突）。而**悬空可能是无意的**，可能是由于设计不当或电路未完成造成的。

**注意事项**

- 设计考虑：在设计电子电路和系统时，**应避免输入引脚悬空，因为这可能导致不稳定的行为**。通常**使用上拉或下拉电阻来确保这些引脚有一个确定的逻辑状态。**
- 高阻态应用：在某些情况下，如**多个设备共享一个通信总线，高阻态是必要的，以确保只有一个设备在任何时刻控制总线。**

#### 复用功能输出

![复用功能输出原理框图](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/%E6%88%AA%E5%B1%8F2023-12-28%2018.18.55.png)

通过片上外设如EXTI到引脚输出

#### 输入模式

**ISR读出**

![普通模式的输入](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/%E6%88%AA%E5%B1%8F2023-12-28%2018.24.03.png)

I/O引脚至上拉/下拉输入(通过BSRR寄存器软件配置), 经TTL肖特基触发器(>2V <1.2V), 至IDR寄存器读出

**复用功能输入**

![复用功能输入](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/%E6%88%AA%E5%B1%8F2023-12-28%2018.29.40.png)

以EXTI为例,RX数据经由TTL肖特基触发器到DR寄存器

**模拟输入**

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
3. 控制GPIO输出高低电平(ODR,BRR和BSRR)

## 手写库

### 通过地址使用寄存器

项目地址: **REG-LED**

main.c中的主要代码

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

定义在stm32f10x.h中

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

在main.c中的主函数代码改为

```c
RCC_APB2ENR |= ((1) << 3); // 开启GPIOB的时钟
GPIOB_CRL &= ~((0x0F) << (4*0)); // 将GPIOB状态清零
GPIOB_CRL |= ((1) << (4*0)); // 将GPIOB设置为推挽输出
GPIOB_ODR &= ~(1<<0); // PB0置0
```

 #### 补充: 关键字volatile的作用

在C语言中，尤其是在嵌入式领域，volatile 关键字用于告诉编译器，**定义为 volatile 的变量可能会以编译器不可预知的方式被改变**。这意味着编译器在处理这些变量时，**应避免进行某些优化，确保每次访问都直接从内存中读取变量的值**。

**含义**

当一个变量被声明为 volatile 时，编译器会对该变量的处理方式做出以下调整：

- **防止优化**：编译器不会对这些变量进行优化，这可能包括消除看似多余的读取或写入操作。
- **直接访问**：每次访问 volatile 变量时，都会直接从其内存地址读取数据，而不是使用可能存储在寄存器中的副本。

**应用场景**

在嵌入式编程中，volatile 关键字的使用场景主要包括：

- **硬件寄存器访问**：当编程与硬件寄存器交互时，如读取一个传感器的数据寄存器或写入一个控制寄存器。这些寄存器的值可能会在任何时候改变，因此需要使用 volatile 来确保每次读取或写入都是最新的值。
- **中断服务例程**：在中断服务例程（ISR）中使用的变量，这些变量可能在ISR中被改变，并在程序的其他部分被访问。使用 volatile 可以确保主程序中的代码能够看到在ISR中对这些变量所做的更改。
- **多线程和并发**：在多线程或并发环境中，一个线程可能修改另一个线程正在访问的变量。volatile 确保每个线程都能访问到最新的值。

**注意事项**

- **不是并发解决方案**：volatile 关键字不能替代互斥锁或其他并发控制机制。它不保证操作的原子性或内存可见性。
- **性能影响**：由于 volatile 防止了某些优化，过度使用它可能会降低程序的性能。
- **正确使用**：只有在上述特定场景中才应使用 volatile。错误地使用 volatile 可能会导致难以发现的错误。

### 通过结构体操作寄存器

项目地址: **FWlib-LED**

在stm32f10x.h中添加结构体定义(主要代码)

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

在stm32f10x.h中增加RCC的结构体定义,如下

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

在main.c中通过结构体访问RCC寄存器,代码如下

```c
RCC->APB2ENR |= ((1) << 3); // 开启GPIOB的时钟
```

#### 更换LED说明

由于我的开发板，PB0总是点亮蓝灯(本应该是绿灯), 以后的测试换为测试蓝灯，**PB0换为PB1进行测试**

### 增加端口置位/复位函数

项目地址: **FWlib-LED**

增加stm32f10x_gpio.c和stm32f10x_gpio.h文件

在stm32f10x_gpio.c中，增加置位/复位函数，如下

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

在stm32f10x_gpio.h中, 添加**16位PIN置1的宏定义,端口置位/复位函数的声明**

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

在main.c函数中使用置位/复位函数

```c
 // 增加复位/置位函数
RCC->APB2ENR  |=  ( (1) << 3 );
GPIOB->CRL &=  ~( (0x0f) << (4*0) );
GPIOB->CRL |=  ( (1) << (4*0) );
GPIO_SetBits(GPIOB,GPIO_Pin_1);
GPIO_ResetBits( GPIOB,GPIO_Pin_1 );
```

#### 补充: 在C语言中#ifndef的作用

在C语言中，#ifndef 是一种预处理指令，用于条件编译。它的全称是 "if not defined"，意思是“如果没有定义”。#ifndef 通常与 #define 和 #endif 一起使用，**用于防止头文件的内容被多次包含（重复包含）**。

**作用**

#ifndef 的主要作用是**确保一个头文件中的内容只被包含一次，防止因重复包含同一头文件而导致的编译错误**这种技术被称为“包含卫士”（Include Guards）或“头文件卫士”（Header Guards）。

**使用方式**

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

**重要性**

在C语言项目中，特别是在大型项目中，头文件经常被多个源文件包含，或者一个头文件包含其他头文件。如果没有包含卫士，头文件中的定义（如函数声明、宏定义、类型定义等）可能会被重复包含，导致编译错误（如重复定义错误）。使用 #ifndef 可以有效地避免这种情况。

#### 解决stm32f10x.h重复定义

在stm32f10x.h中增加#ifndef, 如下

```c
#ifndef __STM32F10X_H
#define __STM32F10X_H

// 中间代码省略

#endif // !__STM32F10X_H
```

#### 补充: #ifndef格式问题

在C语言中，当使用 #ifndef（和 #define、#endif）作为头文件的包含卫士时，通常会在文件名前加上双下划线 __ 或其他类似的前缀/后缀，**这是一种非正式的约定，用于减少命名冲突的风险**然而，需要注意的是，**使用双下划线作为前缀或后缀在某些情况下可能并不是最佳实践**。

**原因**

- **唯一性**：在大型项目中，可能会有许多不同的头文件。使用文件名作为宏的一部分可以帮助确保每个包含卫士的宏是唯一的。
- **减少冲突**：添加额外的字符（如双下划线）可以进一步减少不同头文件之间宏名称冲突的可能性。

**注意事项**

**保留标识符**：根据C和C++标准，**以双下划线开头或以单下划线后跟大写字母开头的标识符是保留给实现（编译器和标准库）使用的**。因此，使用这样的标识符作为宏名称**可能会导致与标准库或编译器的内部标识符冲突**。

建议的做法：更安全的做法是**使用文件名的大写形式加上一个后缀（如 _H），而不是使用双下划线**。例如，对于 example.h 头文件，可以使用 EXAMPLE_H 作为包含卫士的宏。

**示例**

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

**实际写入寄存器的是bit3-0,bit7-4并不写入寄存器**

*勘误：上拉输入和下拉输入两行的bit3-2应该为10*

- bit1-0: 置0, 配置输出速度，通过GPIOSpeed_TypeDef进行覆盖配置 
- bit3-2: 配置输入/输出模式
- bi4: **不写入寄存器**, 用来标志是输入还是输出
- bit6-5: **不写入寄存器**， 用来判断是上拉输入还是下拉输入
- bit7: **不写入寄存器**

在stm32f10x_gpio.h中增加宏定义

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

在stm32f10x_gpio.c中写入GPIO初始化函数(**从库函数中复制**)

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
		// // 先备份CRH寄存器的值
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

在main.c中使用GPIO初始化函数

```c
GPIO_InitTypeDef GPIO_InitStructure;
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHZ;
GPIO_Init(GPIOB, &GPIO_InitStructure);
```

### 增加宏定义来增强代码可移植性

项目地址： **FWlib-LED**

在main.c中增加宏定义

```c
#define LED_B_GPIO_PORT	GPIOB
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

在main.c中使用宏定义后的代码实现LED闪烁

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
  - xx: GPIO, USART, I2C, 
  - stm32f10x_xx.c: 外设的驱动函数库文件
  - stm32f10x_xx.h: 存放外设的初始化结构体，外设初始化结构体成员的参数列表，外设固件库的头文件声明
4. 内核相关 
  - CMSIS: Cortex微控制器软件接口标准
  - core_cm3.h: 实现了内核里面外设的寄存器映射
  - core_cm3.c: 内核外设的驱动固件库
  - NVIC(嵌套向量中断控制器), SysTick(系统滴答定时器), misc.h, misc.c
5. 头文件的配置文件 stm32f10x_conf.h里面包含
  - stm32f10x_usart.h
  - stm32f10x_i2c.h
  - stm32f10x_spi.h
  - stm32f10x_adc.h
  - stm32f10x_fsmc.h
7. 专门存放终端服务函数的C文件(可以放在其他地方，不一定要放在stm32f10x_it.c中)
  - stm32f10x_it.c
  - stm32f10x_it.h

### 新建固件库版本工程

项目路径: **Fwlib-Template**

- Doc: 用来存放程序说明的文件，由写程序的人添加
- Libraries: 存放库文件
- Project: 存放工程
- User: 用户编写的驱动文件

其余按照视频配置，P18, 视频链接: [按照P18进行库移植](https://www.bilibili.com/video/BV1yW411Y7Gw/?p=18&share_source=copy_web&vd_source=0db47c15b9f51dbaa4548ec2dc55dea4)


### GPIO输出-使用固件库点亮LED

项目地址: **12-GPIO输出-使用固件库点亮LED**

在User目录下新建led文件夹，添加bsp_led.c和bsp_led.h

在bsp_led.h中添加所使用的宏定义和函数声明

```c
#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "stm32f10x.h"

// 宏定义
#define LED_B_GPIO_PIN GPIO_Pin_1 // stm32f10x_gpio.h中定义
#define LED_B_GPIO_PORT GPIOB // stm32f10x.h中定义 
#define LED_B_GPIO_CLK RCC_APB2Periph_GPIOB

// 函数声明
void LED_GPIO_Config(void);

#endif // !__BSP_LED_H
```

在bsp_led.c中添加初始化函数

```c
// bsp: board support package 板级支持包
#include "bsp_led.h"

void LED_GPIO_Config(void)
{
    RCC_APB2PeriphClockCmd(LED_B_GPIO_CLK, ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = LED_B_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_B_GPIO_PORT, &GPIO_InitStruct);
}
```

在main.c中调用初始化函数，并进行软件延时，实现LED闪烁

```c
#include "stm32f10x.h"
#include "bsp_led.h"

void Delay(uint32_t count)
{
    for( ; count != 0; count--)
    {
        uint32_t current;
        for(current = count; current != 0; current--)
        {
            ;
        }
    }
    
}

int main(void)
{
    LED_GPIO_Config();

    while(1)
    {
        GPIO_SetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN);
        Delay(0xFFF); // 延时
        GPIO_ResetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN);
        Delay(0xFFF); // 延时
    }
}
```

**增加函数宏定义**

在bsp_led.h中增加如下代码:

```c
#define ON 1 
#define OFF 0
#define LED_B(a) if (a)\
                     GPIO_ResetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN); \
                     else\
                     GPIO_SetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN);
// 使用\可以进行换行，其后不能跟空格，\后应该直接回车
```

在main.c中使用宏定义的函数

```c
LED_B(OFF);
Delay(0xFFF); // 延时
LED_B(ON);
Delay(0xFFF); // 延时
```

#### 使用\的注意事项


在C语言中使用反斜杠 \ 进行换行时，确实有一些需要注意的事项。这种用法通常出现在宏定义或是将长代码行分割为多行以提高代码的可读性。正确使用时，\ 应该放在行尾，紧接着是换行符。

**注意事项**
- **无空格**：在行尾使用 \ 时，它之后直到行末不能有任何字符，包括空格或制表符。任何在 \ 之后的空格都会使得换行转义失效，导致编译错误。
- **紧跟换行符**：\ 应该直接紧跟换行符。这告诉编译器忽略换行符，将下一行视为当前行的延续。
- **可读性**：虽然使用 \ 可以将长代码行分割为多行，但过度使用可能会降低代码的可读性。适当使用，以保持代码整洁和可维护。
- **宏定义中的使用**：在宏定义中使用 \ 进行换行是常见的做法，**因为宏定义必须是单行的**。在这种情况下，确保每一行（除了最后一行）都以 \ 结尾。

**示例**

正确的使用：

```c
#define MY_MACRO(a, b) \
    do { \
        a = 2; \
        b = 3; \
    } while(0)

int main() {
    int x, y;
    MY_MACRO(x, y);
    return 0;
}
```
在这个例子中，宏 MY_MACRO 被分成了多行，每行的末尾都使用了 \ 来实现。

错误的使用（如果 \ 后有空格）：

```c
#define MY_MACRO(a, b) \ 
    do { \
        a = 2; \
        b = 3; \
    } while(0)
```

在这个错误的例子中，**第一行的 \ 后面如果有空格，将导致编译错误**。

总之，当在C语言中使用 \ 进行换行时，**确保 \ 是每行的最后一个字符，并且紧接着换行符**，以避免编译错误并保持代码的清晰

### GPIO输入

项目地址: **13-GPIO输入-按键检测**

通过原理图可知**KEY1接PA0口, 按键按下后为高电平**, 原理图如下

![KEY1原理图](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401011723631.png)

实现**按下KEY1后蓝灯状态翻转**

在bsp_led.h中宏定义电平翻转函数

```c
#define LED_B_TOGGLE {LED_B_GPIO_PORT->ODR ^= LED_B_GPIO_PIN;}
/*----------------------------------------------------------------
^= 异或运算 (a ^ b) 则ab不同为1，相同则为0
ODR低16位和GPIO_Pin_1作异或并重新赋值给ODR可实现ODR的Bit0翻转
若Bit0=1则Bit0 = 1 ^ 1 = 0, 下一次运算时, Bit0=0则Bit0 = 0^1 = 1
实际上是ODR的Bit0在和1进行异或操作
----------------------------------------------------------------*/
```

在bsp_key.h中进行宏定义和函数声明

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

在bsp_key.c中写初始化函数和端口扫描函数

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

在main.c中进行调用

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

在C语言中，异或运算是一种基本的位运算，使用符号 ^ 表示。**异或运算符对两个操作数的对应位进行比较，如果两个相应的位不同，则结果为1，如果相同，则结果为0。**换句话说，它在以下情况下返回1：

- 第一个操作数的位是0，第二个操作数的位是1。
- 第一个操作数的位是1，第二个操作数的位是0。

**异或运算的特性**

- 交换律：a ^ b 等于 b ^ a。
- 结合律：(a ^ b) ^ c 等于 a ^ (b ^ c)。
- 自反性：任何数与自身异或的结果都是0，即 a ^ a 等于 0。
- 与0的异或：任何数与0异或都等于它本身，即 a ^ 0 等于 a。

**应用**

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

**示例**

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

### 地址映射

位带操作的地址映射通常遵循以下规则：

**位带别名地址 = 位带基地址 + (字节偏移量 x 32) + (位编号 x 4)**

其中，**字节偏移量是目标地址相对于位带区域基地址的偏移量**，**位编号是要操作的位**。

### 示例

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

### 注意事项

- 硬件支持：确保你的Cortex-M3微控制器支持位带操作。
- 地址计算：正确的地址计算对于位带操作至关重要。
- 原子操作：位带操作是原子的，这意味着在多任务或中断驱动的环境中，它们是安全的。

### 使用位带操作实现GPIO的输出和输入

项目地址: **14-位带操作-GPIO的输出和输入**

**使用位带操作实现GPIO输出: LED_B的闪烁**

在main.c中添加位带操作的宏定义

```c
#define GPIOB_ODR_Addr (GPIOB_BASE+0x0C)
#define PBout(n) *(unsigned int*)((GPIOB_ODR_Addr&0xF0000000) + 0x02000000 + ((GPIOB_ODR_Addr&0x00FFFFFF)<<5)+(n<<2))
```

在main.c中使用位带操作

```c
while(1)
{
    PBout(1) = 1;
    Delay(0xFFF); // 延时
    PBout(1) = 0;
    Delay(0xFFF); // 延时
}
```

**使用位带操作实现GPIO输入: KEY1和KEY2控制LED_B状态翻转**

在bsp_key.h中添加KEY2的宏定义

```c
#define KEY2_GPIO_PIN GPIO_Pin_13 // stm32f10x_gpio.h中定义
#define KEY2_GPIO_PORT GPIOC // stm32f10x.h中定义 
#define KEY2_GPIO_CLK RCC_APB2Periph_GPIOC
```
在bsp.c中增加KEY2的GPIO初始化

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

在main.c中添加GPIO输入位带操作的宏定义

```c
#define GPIOA_IDR_Addr (GPIOA_BASE+0x08)
#define GPIOC_IDR_Addr (GPIOC_BASE+0x08)
#define PAin(n) *(unsigned int*)((GPIOA_IDR_Addr&0xF0000000) + 0x02000000 + ((GPIOA_IDR_Addr&0x00FFFFFF)<<5)+(n<<2))
#define PCin(n) *(unsigned int*)((GPIOC_IDR_Addr&0xF0000000) + 0x02000000 + ((GPIOC_IDR_Addr&0x00FFFFFF)<<5)+(n<<2))
```

在main.c中使用位带操作

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

__Vectors       DCD     __initial_sp               ; Top of Stack
                DCD     Reset_Handler              ; Reset Handler
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

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY
                
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
                
; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler                [WEAK]
                B       .
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

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************
                 IF      :DEF:__MICROLIB
                
                 EXPORT  __initial_sp
                 EXPORT  __heap_base
                 EXPORT  __heap_limit
                
                 ELSE
                
                 IMPORT  __use_two_region_memory
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

**SPACE：用于分配一定大小的内存空间，单位为字节。这里指定大小等于 Stack_Size, 标号 __initial_sp 紧挨着 SPACE 语句放置，表示栈的结束地址，即栈顶地址，栈是由高向低生长**

```assembly
Stack_Mem       SPACE   Stack_Size
; SPACE：用于分配一定大小的内存空间，单位为字节。这里指定大小等于 Stack_Size。
__initial_sp
; 标号 __initial_sp 紧挨着 SPACE 语句放置，表示栈的结束地址，即栈顶地址，栈是由高向低生长
```

#### SPACE手册说明

![SPACE](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401031539781.png)

### PRESERVE8指令

**PRESERVE8：指定当前文件的堆栈按照 8 字节对齐**

#### PRESERVE8手册说明

![PRESERVE8](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401031556307.png)

![PRESERVE8](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401031557775.png)

### THUMB指令

野火的解释: **THUMB：表示后面指令兼容 THUMB 指令。THUBM 是 ARM 以前的指令集，16bit，现在 Cortex-M系列的都使用 THUMB-2 指令集，THUMB-2 是 32 位的，兼容 16 位和 32 位的指令，是 THUMB的超集**

#### THUMB手册说明

![THUMB](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401031600256.png)

### EXPORT指令

**EXPORT：声明一个标号可被外部的文件使用，使标号具有全局属性。如果是 IAR 编译器，则使用的是 GLOBAL 这个指令**

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