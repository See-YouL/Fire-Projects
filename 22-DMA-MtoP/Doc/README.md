# DMA实验2: M to P

**实验需求**: SRAM to 串口, 同时LED灯闪烁, 演示DMA数据不需占用CPU

## 在bsp_dma_m2p.h中加入宏定义

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

## 在bsp_dma_m2p.c中加入USART的初始化函数

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

## 在bsp_dma_m2p.c中加入USARTx_TX DMA配置, 实现内存到外设(USART1->DR)

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
}
```

## 在bsp_dma_m2p.c中声明在内存的变量

```c
uint8_t SendBuff[SENDBUFF_SIZE];
```

## 在main.c中声明外部变量

```c
extern uint8_t SendBuff[SENDBUFF_SIZE];
```

## 在main.c中测试DMA, 实现DMA将储存器中的数据发送到USART->DR, 并实现LED1闪烁

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
