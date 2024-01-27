# README

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

**I2C物理层主要特点**

- I2C是支持多设备的总线, 可支持多个通讯主机和从机
- I2C使用两条线路, 一条SDA(双向串行数据线)来表示数据, 一条SCL(串行时钟线)来同步数据, 属于同步通信
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

**I2C基本读写过程**

**主机写数据到从机**

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

**主机由从机读数据**

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

**通信复合格式**

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

**通讯的起始和停止信号**

![通讯的起始和停止信号](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270225648.png)

- 起始信号: **SCL高电平, SDA由高电平向低电平转换**
- 停止信号: **SCL高电平, SDA由低电平向高电平转换**

**数据的有效性**

![数据有效性](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270237788.png)

- SDA: 负责传输数据
- SCL: 高电平时采集SDA上1bit数据, 低电平时SDA进行电平转换

**地址及数据方向**

![地址及数据方向](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270243764.png)

**I2C采用高位先行, 由高位到低位进行传输**

**一般使用7位表示I2C上的设备地址, 设备地址加上其后的读写位可以凑成8位即1字节方便传输**

例如, 某设备在I2C上的设备地址为7位的0x78(0b01111000), 可加入读写位凑到八位

- 8位设备的读地址位为0xF1(0b11110001)
- 8位设备的写地址位为0xF0(0b11110000)

**响应**

![响应](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270254565.png)

1. 1-8个时钟信号中: 数据发送端控制SDA传输7位设备地址和1位读写信号
2. 在第9个时钟信号时: 数据接收端获得SDA控制权, 发送应答信号(低电平表示应答)

### STM32的I2C特性及架构

![STM32的I2C特性及架构](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270305500.png)

- 软件模拟协议: 较为繁琐
- 硬件模拟协议: 较为方便, 减轻CPU负担

*STM32硬件的I2C逻辑可能会有问题*

**STM32的I2C架构分析**

![STM32的I2C架构分析](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270315440.png)

**I2C的通讯引脚**

![I2C的通讯引脚](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270346561.png)

![I2C的通讯引脚](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270316720.png)

*勘误: I2C1_SCL默认映射到PB5, I2C1_SDA默认映射到PB7, 图片中有误*

**STM32兼容smbus协议**

**时钟控制逻辑**

![时钟控制逻辑](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270347794.png)
![时钟控制逻辑](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270325594.png)

*Tpck1: 指的是APB1时钟周期(1/36MHz)*

**计算时钟频率的方法**

![计算时钟频率的方法](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270333989.png)

**实际就是解未知数CCR的一元一次方程**

**数据控制逻辑**

![数据控制逻辑](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270347332.png)

![数据控制逻辑](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270337311.png)

1. 将8位数据写入数据寄存器(DR)
2. 数据寄存器里面的数据会被发送到数据移位寄存器

**整体控制逻辑**

![整体控制逻辑](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270348369.png)

![整体控制逻辑](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270355991.png)

### STM32硬件I2C的通讯过程

**STM32作为主发送器的通讯过程**

![STM32作为主发送器的通讯过程](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270357886.png)

*勘误: EV8_2: TxE=1, BTF=1, 请求设置停止位. TxE和BTF位由硬件在产生停止条件时清除*

- EV5: 在正常产生S起始信号后会产生EV5事件(I2C_SRx:SB[0]置1表示起始条件已发送)
- EV6: 在正常发送SLAVE ADDRESS和R/!W位后会产生EV6事件(I2C_SRx:ADDR[1]置1表示地址发送结束)
- EV8: 在正常数据发送完毕后会产生EV8事件(I2C_SRx:TxE[7]置1表示数据寄存器空)
- EV8_2: 在从机发送结束应答后会产生EV8_2事件(I2C_SRx:TxE[7]置1表示数据寄存器空, I2C_SRx:BTF[2]置1表示字节发送结束, I2C_CRx:STOP[9]置1表示在当前字节传输或在当前起始条件发出后产生停止条件, 产生停止条件后由硬件清除TxE和BTF位)

**STM32作为主接收器的通讯过程**

![STM32作为主接收器的通讯过程](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270423471.png)

*勘误: EV7_1: RxNE=1, 读DR寄存器清除该事件. 设置ACK=0和STOP请求*

- EV5: 在正常产生S起始信号后会产生EV5事件(I2C_SRx:SB[0]置1表示起始条件已发送)
- EV6: 在正常发送SLAVE ADDRESS和R/!W位后会产生EV6事件(I2C_SRx:ADDR[1]置1表示地址发送结束)
- EV7: 在正常数据发送完毕后会产生EV7事件(I2C_SRx:RxNE[6]置1表示数据寄存器(接收时)非空)
- EV7_1: 在主机发送结束应答后会产生EV7_1事件(I2C_SRx:RxNE[6]置1表示数据寄存器(接收时)非空, I2C_CRx:ACK[10]置0表示设置为无应答返回, I2C_CRx:STOP[9]置1表示在当前字节传输或释放SCL和SDA线)

**标志位的清除方法**

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

I2C_GenerateSTART函数, 用于产生起始条件

![I2C库函数](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271607885.png)

I2C_GetFlagStatus函数, 用于获取状态位

![I2C库函数](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271610721.png)

**I2C_FLAG参数列表对应I2C_SRx状态寄存器的各个位, 可通过查询手册查看其含义**

返回值说明

![返回值说明](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271612900.png)

```c
typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;
```

- RESET: 0, 返回RESET表示该状态位为0
- SET: 1, 返回SET表示该状态位为1

I2C_Send7bitAddress函数, 用于发送7位地址

![I2C库函数](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271616560.png)

*参数Address为八位读/写地址, 通过I2C_Direction实际配置读写方向, 最终方向以I2C_Direction配置为准, 参数Address的读写位失效*

I2C_SendDate函数, 通过I2Cx外设发送数据字节

![I2C库函数](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271618557.png)

I2C_ReceiveData函数, 返回 I2Cx 外设最近接收的数据

![I2C库函数](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271622473.png)

AcknowledgeConfig函数, 使能或禁用I2C的应答

![I2C库函数](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271623317.png)

I2C_Cmd函数, 使能或禁用I2Cx外设

![I2C库函数](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271625131.png)

I2C_CheckEvent函数, I2C状态监测函数

**监测的事件发生则返回SUCCESS**

![I2C库函数](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401280036252.png)

![](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401280037103.png)

![](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401280037758.png)

![](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401280038783.png)

![](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401280038105.png)

### EEPROM硬件结构

![EEPROM](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271630443.png)


引脚说明

- VCC: 电源引脚, 接3V3
- GND: 地引脚, 接地
- SCL: 时钟线, 经2.2K上拉电阻接3V3, 接PB6引脚(默认映射I2C1_SCL)
- SDA: 数据线, 经2,2K上拉电阻接3V3, 接PB7引脚(默认映射I2C1_SDA)
- HOLD: WP引脚, 接地, 不启用写保护(即可向AT24C02写数据)
- A0-A2: 地址引脚, 接地, A0:A2为000, 如需拓展EEPROM则可通过配置A0-A2的地址引脚来进行区分(如: 配置A0:A2为001, 则可对两EEPROM进行区分)

### AT24C02介绍

![AT24C02](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271642465.png)

AT24C02可存储256字节数据

引脚说明

![AT24C02](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271648925.png)

- A0-A2: AT24C02用来区分不同AT24C0x芯片的设备地址
- SDA: 数据线
- SCL: 时钟线
- WP: 写保护, 置1启用写保护
- NC: 不连接


设备地址

![设备地址](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271702961.png)

![设备地址](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271702718.png)

**AT24C02有256字节, 即属于2K(256*8)**

![设备地址](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271701248.png)

根据原理图, 将A2-A0均接地, 则A2 = A1 = A0 = 0

**AT24C02的地址为0b1010000R/W, Bit0为R/!W位**

- AT24C02在A2:A1[000]情况下读地址: 0b10100001(0xA1)
- AT24C02在A2:A1[000]情况下写地址: 0b10100000(0xA0)

AT24C02的Byte Write(以字节方式写数据)操作

![Byte Write](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271719435.png)

*第一个传输的数据段(DATA)为WORD ADDRESS(需要写入的字节所在的地址), 第二次传输数据段(DATA)才为真正需要写入的内容*

![Byte Write](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271723653.png)

```tex
翻译: Byte Write的工作流程

1. 在发送完SLAVE ADDRESS和W/!R后, 需要发送一个字节的数据地址(WORD ADDRESS)(即需要写入的字节所在的地址)
2. 收到地址(WORD ADDRESS)后, EEPROM会响应ACK, 然后接收一个字节的数据(DATA)(真正要写入的内容)
3. 接收到数据(DATA)后, EEPROM响应ACK, 单片机必须发送STOP信号, 不能继续传输第二段数据(给EEPROM预留写入时间)
4. 接收到停止信号后, EEPROM在tWR的周期时间内进行向内部写入数据
5. 在此写入周期中, 所有输入被禁用, EEPROM不进行响应
```

AT24C02的Page Write(以页方式写数据)操作, 又称突发写入(即仅发送一个地址可写入多个数据)

*Page Write解决了Byte Write不能连续写入的缺陷*

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

AT24C02的Current Address Read(从当前地址读数据)操作

![Current Address Read](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271810617.png)

*一般不用, 因为在开发中不好确定当前地址的位置*

AT24C02的Random Read(随机读数据)操作

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

AT24C02的Sequential Read(顺序读数据)操作

![Sequential Read](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271838678.png)

**与Page Write类似**

![Sequential Read](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401271841941.png)

```tex
翻译: Sequential Read流程

1. Sequntial Read从当前地址读取或随机地址开始读取
2. 单片机收到DATA后，会响应ACK
3. 只要EEPROM收到ACK响应，它就会继续递增数据地址，并顺序串行输出DATA
4. 当达到内存地址限制时，数据地址将"roll over"，顺序读取将继续从头开始重新读取数据
5. 当单片机NO ACK响应并生成STOP，则终止Sequential Read
```

### I2C-读写EEPROM实验

**项目地址** 24-I2C-EEPROM

 **操作流程**

  1. 初始化I2C相关的GPIO
  2. 配置I2C外设的工作模式
  3. 编写I2C写入EEPROM的Byte Write函数 
  4. 编写I2C读取EEPROM的Random Read函数
  5. 使用read函数和write函数进行读写校验
  6. 编写Page Write和Sequential Read函数进行校验

在bsp_i2c.h中定义相关宏