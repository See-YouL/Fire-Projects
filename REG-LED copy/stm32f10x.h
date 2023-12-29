// 存放stm32寄存器映射的代码

// 外设 Peripheral
#define PERIPH_BASE ((unsigned int)0x40000000)
#define APB1PERIPH_BASE (PERIPH_BASE) // 从TIM2开始
#define APB2PERIPH_BASE (PERIPH_BASE + 0x10000) // 从AFIO开始
#define AHBPERIPH_BASE (PERIPH_BASE + 0x20000) // 从DMA1开始

// RCC
#define RCC_BASE (AHBPERIPH_BASE + 0x1000) // RCC基地址 

// GPIOB
#define GPIOB_BASE (APB2PERIPH_BASE + 0x0C00) // GPIOB基地址

// 定义寄存器

// APB2外设时钟使能寄存器
#define RCC_APB2ENR ((volatile unsigned int *)(RCC_BASE + 0x18))