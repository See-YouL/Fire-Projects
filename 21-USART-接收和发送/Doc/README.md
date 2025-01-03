# USART-串口通信

## 串口通信协议简介

![](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171610065.png)

**物理层的常用标准**

![](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171610887.png)

**232和TTL电平区别**

![](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171611637.png)

- TTL: 从芯片出来的基本是TTL电平
- 232: 负逻辑, 压差大

**232通信通讯结构图**

![](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171631235.png)

**DB9接口图**

![DB9接口](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171634288.png)

**USB转串口通讯结构图**

![](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171644660.png)

**串口到串口通讯结构图**

![](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171655718.png)

**串口数据包的组成**

![](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171658813.png)

![](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171659831.png)

![](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171702232.png)

![](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171703446.png)

![](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171703050.png)

![](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171704956.png)

## STM32串口功能框图讲解

### 引脚部分讲解

![](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171708669.png)

![](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171708578.png)

**引脚对应**

![](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171710068.png)

### 数据寄存器部分

![](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171723621.png)

**数据格式**

![](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171725627.png)

**USART_CR1的bit12 M控制字长**

![](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171727509.png)

**USART_CR2的bit[13:12] STOP控制停止位的位数**

![](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171727238.png)

**USART_CR1的bit10(PSE), bit9(PS)来使能校验和选择校验模式**

![](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171730822.png)

**USART_CR1的bit8(PEIE)来使能中断**

![](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171731175.png)

**USART_SR的bit0(PE)来检测校验错误**

![](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171732400.png)

**发送数据部分**

![](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171739676.png)

1. 先将USART_CR1的UE位置1(*使能USART模块*), 再将USART_CR1的TE位置1(*使能发送*)
2. 数据从CPU或DMA中写入发送数据寄存器(TDR), TDR发送完毕后, USART_SR的TXE位置1(*数据已经被转移到移位寄存器中*)
3. 发送移位寄存器发送完毕后, USART_SR的TC位置1(*表示发送完成*)

**接收数据部分**

![接收数据部分](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171900970.png)

1. 先将USART_CR1的UE位置1(*使能USART模块*), 再将USART_CR1的RE位置1(*使能接收*)
2. 数据从RX到接收移位寄存器到接收数据寄存器(RDR), 接收完毕后, USART_SR的RXNE位置1(*收到数据, 可以读出*)

### 波特率设置

**使用USART_BRR进行配置**

![](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171906798.png)

**波特率的计算公式**

![](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171909589.png)

- APB2时钟: 72MHz, 挂载USART1
- APB1时钟: 36MHz, 挂载USART2, 3, 4, 5

![](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401171910703.png)

##  串口初始化结构体和固件库讲解

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

- **串口初始化函数**: void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct);
- **中断配置函数**: void USART_ITConfig(USART_TypeDef* USARTx, uint16_t USART_IT, FunctionalState NewState);
- **串口使能函数**: void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
- **数据发送函数**: void USART_SendData(USART_TypeDef* USARTx, uint16_t Data);
- **数据接收函数**: void USART_ReceiveData(USART_TypeDef* USARTx);
- **中断状态位获取函数**: ITStatus USART_GetITStatus(USART_TypeDef* USARTx, uint16_t USART_IT);

## USB转串口的硬件原理图

![硬件原理图](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401172002602.png)

## 串口GPIO汇总

![串口GPIO](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401220859886.png)

## 补充: 外设的GPIO配置

**在STM32F10x参考手册中的8.1.11节可找到外设的GPIO配置, 其中关于USART部分的GPIO配置如下图**

![USART的GPIO配置](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401220904826.png)

## 配置串口助手

**本项目使用的串口助手: 野火多功能调试助手V1.0.2.9**

串口配置如下图(*串口配置参数与串口的初始化配置有关, 该配置符合下文代码的初始化*)

![串口助手配置](https://raw.githubusercontent.com/See-YouL/MarkdownPhotos/main/202401250242370.png)

## USART接收和发送实验

**项目地址 : 21-USART-接收和发送**

**实验需求**: 单片机给电脑发送数据, 电脑上位机把数据打印出来; 电脑上位机给单片机发数据, 单片机接收到数据之后立马发回给电脑, 并打印出来.

### 在bsp_usart.h中进行串口的宏定义, 并使用条件编译来选择串口

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

### 在bsp_usart.c中编写usart的初始化函数

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

### 在bsp_usart.c中编写串口中断优先级配置函数

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

### 在bsp_usart.c中编写发送一个字节到串口的函数

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

### 在bsp_usart.c中编写发送两个字节到串口的函数

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

### 在bsp_usart.c中编写发送数组的函数

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

### 在bsp_usart.c中编写发送字符串的函数

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

### 在bsp_usart.c中编写重定向标准输出输入函数, 使得串口可使用scanf printf等函数

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

### 在main.c函数中进行测试

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

### 在stm32f10x_it.c中编写中断服务函数实现串口数据的接收并发送

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