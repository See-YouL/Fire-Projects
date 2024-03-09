# README

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
- SI_IO1: MISO  中
- /WP_IO2: 写保护接高电平, 不使用
- /HOLD_IO3: 暂停通讯, 接高电平, 不使用

### SPI-FLASH读写测试

项目地址: **25-SPI-FLASH-RW**

#### SPI引脚宏定义

在bsp_spi_flash.h中

```c
/**
 * @brief 如果使用霸道开发板则配置为1, 指南者开发板为0
 */

#define USE_BD 1

/**
 * @defgroup SPI_FLASH_Define 
 * @{
 */

/**
 * @brief SPI的宏定义
 */

#define FLASH_SPIx SPI1 /*!< FLASH所使用的SPIx */
#define FLASH_SPI_APBxClock_FUN RCC_APB2PeriphClockCmd /*!< SPI的GPIO时钟的使能函数 */
#define FLASH_SPI_CLK RCC_APB2Periph_SPI1 /*!< SPI的时钟 */
#define FLASH_SPI_GPIO_APBxClock_FUN RCC_APB2PeriphClockCmd /*!< SPI引脚的GPIO时钟 */

/**
 * @brief SPI的GPIO引脚宏定义
 */

#if (1 == USE_BD)
    #define FLASH_SPI_GPIO_CLK RCC_APB2Periph_GPIOA
    #define FLASH_SPI_CS_PORT GPIOA /*!< SPI的CS引脚 */
    #define FLASH_SPI_CS_PIN GPIO_Pin_4 /*!< SPI的CS引脚 */
#else
    #define FLASH_SPI_GPIO_CLK (RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC)
    #define FLASH_SPI_CS_PORT GPIOC /*!< SPI的CS引脚 */
    #define FLASH_SPI_CS_PIN GPIO_Pin_0 /*!< SPI的CS引脚 */
#endif

#define FLASH_SPI_SCK_PORT GPIOA /*!< SPI的SCK引脚 */
#define FLASH_SPI_SCK_PIN GPIO_Pin_5 /*!< SPI的SCK引脚 */
#define FLASH_SPI_MOSI_PORT GPIOA /*!< SPI的MOSI引脚 */
#define FLASH_SPI_MOSI_PIN GPIO_Pin_7 /*!< SPI的MOSI引脚 */
#define FLASH_SPI_MISO_PORT GPIOA /*!< SPI的MISO引脚 */
#define FLASH_SPI_MISO_PIN GPIO_Pin_6 /*!< SPI的MISO引脚 */

/**
 * @brief CS引脚配置
 */
#define FLASH_SPI_CS_HIGH GPIO_SetBits(FLASH_SPI_CS_PORT, FLASH_SPI_CS_PIN);
#define FLASH_SPI_CS_LOW GPIO_ResetBits(FLASH_SPI_CS_PORT, FLASH_SPI_CS_PIN);
```

#### DEBUG信息宏定义

在bsp_spi_flash.h中

```c
/**
 * @brief DEBUG信息输出
 */
#define FLASH_DEBUG_ON 0
#define FLASH_INFO(fmt, arg...) printf("<<-FLASH-INFO->> "fmt"\n", ##arg)
#define FLASH_ERROR(fmt, arg...) printf("<<-FLASH-ERROR->> "fmt"\n", ##arg)
#define FLASH_DEBUG(fmt, arg...) do{\
 printf("<<-FLASH-DEBUG->> [%d]"fmt"\n", __LINE__, ##arg);\
                                   }while(0)

/**
 * @brief 等待超时时间
 */
#define SPI_FLAG_TIMEOUT ((uint32_t)0x1000)
#define SPI_LONG_TIMEOUT ((uint32_t)(10 * SPI_FLAG_TIMEOUT))
```

#### 定义超时函数

在bsp_spi_flash.c中

```c
/**
 * @brief 超时函数
 */
static __IO uint32_t SPITimeout = SPI_LONG_TIMEOUT;
static uint32_t SPI_TIMEOUT_UserCallback(uint8_t errorCode);

/**
 * @brief 超时函数
 * @param errorCode: 错误代码, 用来定位是哪个环节出错
 * @retval 返回0, 表示SPI读取失败 
 */
static uint32_t SPI_TIMEOUT_UserCallback(uint8_t errorCode)
{
    FLASH_ERROR("SPI Timeout, errorCode = %d\r\n", errorCode);
    return 0;
}
```

#### SPI的IO配置函数

在bsp_spi_flash.c中

```c
/**
 * @brief SPI的IO配置
 * @param None
 * @return None
 */
static void SPI_GPIO_Config(void)
{
    /* 定义GPIO初始化结构体 */
    GPIO_InitTypeDef GPIO_InitStructure;
    /* 使能与SPI有关的时钟 */
    FLASH_SPI_APBxClock_FUN(FLASH_SPI_CLK, ENABLE);
    FLASH_SPI_GPIO_APBxClock_FUN(FLASH_SPI_GPIO_CLK, ENABLE);
    /* SCK 配置 */
    GPIO_InitStructure.GPIO_Pin = FLASH_SPI_CLK;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(FLASH_SPI_SCK_PORT, &GPIO_InitStructure);
    /* MOSI 配置 */
    GPIO_InitStructure.GPIO_Pin = FLASH_SPI_MOSI_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(FLASH_SPI_MOSI_PORT, &GPIO_InitStructure);
    /* MISO 配置 */
    GPIO_InitStructure.GPIO_Pin = FLASH_SPI_MISO_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(FLASH_SPI_MISO_PORT, &GPIO_InitStructure);
    /* CSS 软件配置 */
    GPIO_InitStructure.GPIO_Pin = FLASH_SPI_CS_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(FLASH_SPI_CS_PORT, &GPIO_InitStructure);
    /* CS引脚配置为高电平 */
    FLASH_SPI_CS_HIGH;
}
```

#### SPI工作模式配置

在bsp_spi_flash.c中

```c
/**
 * @brief SPI工作模式配置
 * @param None
 * @return None
 */
static void SPI_Mode_Config(void)
{
    /* 定义SPI初始化结构体 */
    SPI_InitTypeDef SPI_InitStructure;
    /* 二分频 */
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    /* 配置CPHA偶数边缘采样 */
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    /* 配置CPOL高电平采样 */
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    /* 不使用CRC校验 */
    SPI_InitStructure.SPI_CRCPolynomial = 0;
    /* 数据位配置为8位 */
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    /* 配置方向为双向全双工 */
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    /* 配置为MSB先行 */
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    /* 配置为主机模式 */
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    /* 配置为软件CS */
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;;
    /* 初始化SPI */
    SPI_Init(FLASH_SPIx, &SPI_InitStructure);
    /* 使能SPI */
    SPI_Cmd(FLASH_SPIx, ENABLE);
}
```

#### 编写SPI初始化函数

```c
/**
 * @brief SPI初始化
 * @param None
 * @return None
 */
void SPI_FLASH_Init(void)
{
    /* 初始化SPI_GPIO */
    SPI_GPIO_Config();
    /* 初始化SPI */
    SPI_Mode_Config();
}
```
