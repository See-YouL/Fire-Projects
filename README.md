# 野火霸道V2开发板学习笔记

## 说明

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

- Doc: 用来存放程序说明的文件，由写程序的人添加
- Libraries: 存放库文件
- Project: 存放工程
- User: 用户编写的驱动文件

其余按照视频配置，P18, 视频链接: [按照P18进行库移植](https://www.bilibili.com/video/BV1yW411Y7Gw/?p=18&share_source=copy_web&vd_source=0db47c15b9f51dbaa4548ec2dc55dea4)
  


