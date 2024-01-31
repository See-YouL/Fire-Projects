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

#### I2C物理层主要特点

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

##### 时钟控制逻辑

![时钟控制逻辑](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270347794.png)
![时钟控制逻辑](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270325594.png)

注: *Tpck1: 指的是APB1时钟周期(1/36MHz)*

###### 计算时钟频率的方法

![计算时钟频率的方法](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401270333989.png)

实际就是解未知数CCR的一元一次方程

##### 数据控制逻辑

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
