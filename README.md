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

![看视频配置Keil MDK](https://www.bilibili.com/video/BV1yW411Y7Gw/?p=2&share_source=copy_web&vd_source=0db47c15b9f51dbaa4548ec2dc55dea4)

### 配置串口下载程序

看视频配置串口下载程序,P4

![看视频配置串口下载程序](https://www.bilibili.com/video/BV1yW411Y7Gw/?p=4&share_source=copy_web&vd_source=0db47c15b9f51dbaa4548ec2dc55dea4)

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

### 寄存器

