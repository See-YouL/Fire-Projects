# 野火霸道V2开发板学习笔记

## 说明

- 编译器： ARM v6.19
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
