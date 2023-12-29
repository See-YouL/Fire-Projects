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
#define RCC_APB2ENR (*(volatile unsigned int *)(RCC_BASE + 0x18)) // APB2外设时钟使能寄存器

// 定义结构体
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

typedef struct 
{
    uint32_t CRL;
    uint32_t CRH;
    uint32_t IDR;
    uint32_t ODR;
    uint32_t BSRR;
    uint32_t BRR;
    uint32_t LCKR;
}GPIO_TypeDef;

#define GPIOB ((GPIO_TypeDef *)GPIOB_BASE) // 使用GPIOB->访问成员变量
/*----------------------------------------------------------------
若定义为 #define GPIOB (*(GPIO_TypeDef *)(GPIOB_BASE))
则使用GPIOB.XXX来访问成员变量
----------------------------------------------------------------*/

typedef struct 
{
    uint32_t CR;
    uint32_t CFGR;
    uint32_t CIR;
    uint32_t APB2RSTR;
    uint32_t APB1RSTR;
    uint32_t AHBENR;
    uint32_t APB2ENR;
    uint32_t APB1ENR;
    uint32_t BDCR;
    uint32_t CSR;
    uint32_t AHBRSTR;
    uint32_t CFGR2;
}RCC_Typedef;

#define RCC ((RCC_Typedef*)RCC_BASE) // 使用RCC->访问成员变量
/*----------------------------------------------------------------
若定义为 #define RCC (*(RCC_Typedef*)RCC_Base)
则使用RCC.XXX来访问成员变量
----------------------------------------------------------------*/