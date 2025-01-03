# DMA

DMA: Direct Memory Access, 直接寄存器访问. 主要功能是可以把数据从一个地方搬到另一个地方, 而且不占用CPU

- DMA1: 有7个通道, 可实现P->M, M->P, M->M
- DMA2: 有5个通道, 可实现P->M, M->P, M->M(*只存在于大容量和互联型产品中*)

## 补充: DMA介绍

DMA（Direct Memory Access，直接内存访问）是计算机系统中的一种技术，**它允许外设或内存模块通过绕过中央处理器（CPU）直接与系统内存进行数据传输**。DMA的目标是提高数据传输效率，减轻CPU的负担，使CPU能够专注于执行其他任务。

以下是关于DMA的一些重要概念和特性：

**工作原理**：

DMA通过在系统总线上控制数据传输而不涉及CPU来工作。它可以在CPU不介入的情况下，直接将数据从一个位置传输到另一个位置。

1. 配置： CPU负责配置DMA，确定源地址、目标地址、传输方向、传输大小等参数。
2. 启动： 一旦DMA被配置，CPU就可以启动DMA控制器，它将负责管理数据传输。
3. 传输： DMA控制器在总线上控制数据传输，无需CPU的干预。数据在源和目标之间直接传输。
4. 中断通知： DMA传输完成后，通常会发出一个中断信号，以通知CPU或其他系统组件。

**优点**：

1. 提高性能： 通过绕过CPU，减轻了CPU的负担，使其能够执行其他任务，提高了整体系统性能。
2. 实时数据传输： 特别适用于实时数据传输，如音频、视频流等。
3. 高效处理大量数据： 对于大量数据的块传输，DMA比CPU执行这样的传输更为高效。

**应用领域**：

DMA在多种应用场景中都得到了广泛应用，包括但不限于：

1. 嵌入式系统： 用于处理外设和内存之间的数据传输，例如，处理音频、图像等。
2. 网络通信： 在网络接口控制器和系统内存之间快速传输数据。
3. 存储系统： 用于在磁盘、固态硬盘等存储设备和系统内存之间进行数据传输。
4. 图形处理： 在图形卡和系统内存之间进行大规模图形数据的传输。

**DMA控制器**：

DMA通常由专门的硬件单元，称为DMA控制器，来管理。DMA控制器的设计和功能因芯片架构而异，但通常包括寄存器用于配置、启动和监视传输。

总的来说，DMA是一项重要的技术，对于需要高效数据传输的系统是至关重要的。通过减轻CPU的负担，DMA提高了系统的整体性能和响应速度。

## DMA功能框图讲解

![DMA功能框图讲解](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401261122722.png)

## DMA请求映射

DMA1请求映射

![DMA1请求映射](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401261126729.png)

DMA2请求映射

![DMA2请求映射](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401261127579.png)

## DMA仲裁器

![DMA仲裁器](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401261128690.png)

*软件配置在寄存器DMA_CCRx:PL[1:0]进行通道优先级配置*

## DMA固件库-初始化结构体

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

## DMA固件库-固件库函数

在stm32f10x_dma.h文件中可以找到DMA固件库函数的声明, 以下是常用的函数

```c
void DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_InitTypeDef* DMA_InitStruct); // 初始化函数
void DMA_Cmd(DMA_Channel_TypeDef* DMAy_Channelx, FunctionalState NewState); // 使能DMA
FlagStatus DMA_GetFlagStatus(uint32_t DMAy_FLAG); // 判断标志位
```

## DMA实验1: M to M

**项目地址**: 

**实验需求**: FLASH to SRAM, 把内部FLASH的数据传输到内部的SRAM

在bsp_dma_m2m.h增加宏定义

```c
// 当使用存储器到存储器模式时候，通道可以随便选，没有硬性的规定
#define M2M_DMA_CHANNEL     DMA1_Channel6
#define M2M_DMA_CLOCK       RCC_AHBPeriph_DMA1
// 传输完成标志
#define M2M_DMA_FLAG_TC     DMA1_FLAG_TC6
// 要发送的数据大小
#define BUFFER_SIZE     32
```

在bsp_dma_m2m.c中定义源和目标变量

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
在bsp_dma_m2m.c中增加DMA初始化函数

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

在bsp_dma_m2m.c中增加判断数据相等的函数

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

在main.c函数中进行测试

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