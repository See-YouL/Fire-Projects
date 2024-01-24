#include "bsp_exti.h"

/**
 * @brief Configures the NVIC for EXTI interrupts.
 *
 * This function configures the NVIC (Nested Vectored Interrupt Controller) for EXTI interrupts.
 * It sets the priority group, selects the interrupt source, sets the preemption priority and subpriority,
 * and enables the interrupt.
 *
 * @param None
 * @return None
 */
static void EXTI_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStruct;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); // 配置中断优先级分组

    NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn; // 选择中断源
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; // 抢占优先级
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1; // 子优先级
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; // 使能中断
    NVIC_Init(&NVIC_InitStruct);
}

void EXTI_Key_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStruct;

    // 配置中断优先级

    // 1. 初始化要连接到EXTI的GPIO
    // 初始化 Key1(PA0)
    RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK, ENABLE);
    GPIO_InitStruct.GPIO_Pin = KEY1_INT_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStruct);

    // 2. 初始化EXTI用于产生中断/事件
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0); // 选择输入线
    EXTI_InitStruct.EXTI_Line = EXTI_Line0;                     // 选择EXTI线路
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;            // 选择中断模式
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;         // 选择触发模式
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;                          // 使能EXTI线路
    EXTI_Init(&EXTI_InitStruct);

    // 3. 初始化NVIC, 用于处理中断
    EXTI_NVIC_Config();
}