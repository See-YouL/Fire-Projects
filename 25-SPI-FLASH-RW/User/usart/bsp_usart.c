#include "stm32f10x_conf.h"
#include "bsp_usart.h"

//  /**
//   * @brief  配置嵌套向量中断控制器NVIC
//   * @param  无
//   * @retval 无
//   */
// static void NVIC_Configuration(void)
// {
//   NVIC_InitTypeDef NVIC_InitStructure;
  
//   /* 嵌套向量中断控制器组选择 */
//   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
//   /* 配置USART为中断源 */
//   NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
//   /* 抢断优先级*/
//   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//   /* 子优先级 */
//   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//   /* 使能中断 */
//   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//   /* 初始化配置NVIC */
//   NVIC_Init(&NVIC_InitStructure);
// }

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
	
	// // 串口中断优先级配置
	// NVIC_Configuration();
	
	// // 使能串口接收中断
	// USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE);	
	
	// 使能串口
	USART_Cmd(DEBUG_USARTx, ENABLE);	    
}

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
