#include "bsp_rccclkconfig.h"


/**
 * @brief 设置系统时钟为外部高速晶振（HSE）时钟，并配置PLL倍频系数。
 * 
 * @param RCC_PLLMul_x PLL倍频系数，范围为2-16。
 * @note 该函数会将RCC模块复位，并使能HSE。如果HSE启动成功，则设置FLASH预取指令使能、FLASH等待周期、AHB总线时钟、APB1总线时钟、APB2总线时钟、PLL倍频系数，并等待PLL稳定后将系统时钟设置为PLL时钟。
 *       如果HSE启动失败，则用户可以在函数中添加处理错误的代码。
 */
void HSE_SetSysClk(uint32_t RCC_PLLMul_x)
{
    RCC_DeInit(); // RCC复位
    ErrorStatus HSEStatus;
    RCC_HSEConfig(RCC_HSE_ON); // 使能HSE
    HSEStatus = RCC_WaitForHSEStartUp(); // 获取HSE启动状态

    if(HSEStatus == SUCCESS)
    {
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); // 使能预取指
        FLASH_SetLatency(FLASH_ACR_LATENCY_2); // 设置等待
        RCC_HCLKConfig(RCC_SYSCLK_Div1); //HCLK = SYSCLK = 72MHz
        RCC_PCLK1Config(RCC_SYSCLK_Div2); //PCLK1 = HCLK / 2 = 36MHz
        RCC_PCLK2Config(RCC_SYSCLK_Div1); //PCLK2 = HCLK / 1 = 72MHz
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_x); // RCC_RLLMul_x 用来超频 频率:(8*x)MHz
        RCC_PLLCmd(ENABLE); // 使能PLL
        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
        {
            // 等待PLL稳定
            ;
        }
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); // 设置系统时钟为PLL时钟
        while(RCC_GetSYSCLKSource() != 0x08)
        {
            // 等待设置系统时钟
            ;
        }
    }
    else
    {
        // 如果HSE启动失败, 用户在此添加处理错误代码
    }
}

/**
 * @brief Configures the GPIO for MCO (Microcontroller Clock Output).
 * 
 * This function initializes the GPIO pin for MCO and configures it as an alternate function push-pull output.
 * The GPIO pin used for MCO is GPIOA Pin 8.
 * 
 * @param None
 * @return None
 */
void MCO_GPIO_Config(void)
{
    // MCO的GPIO初始化
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/**
 * @brief 设置系统时钟为HSI，并配置PLL倍频系数
 * 
 * @param RCC_PLLMul_x PLL倍频系数，范围为2-16
 * 
 * @note 该函数将系统时钟设置为HSI，并根据传入的PLL倍频系数配置PLL，以实现超频功能。
 *       如果HSI启动失败，用户可以在函数的else分支中添加处理错误的代码。
 */
void HSI_SetSysClk(uint32_t RCC_PLLMul_x)
{
    // Function implementation
    __IO uint32_t HSIStatus = 0; // 参考固件库源码
    RCC_DeInit(); // RCC复位
    RCC_HSICmd(ENABLE); // 使能HSI
    HSIStatus = RCC->CR & RCC_CR_HSIRDY; // 获取HSI启动状态, 参考固件库源码

    if(HSIStatus == RCC_CR_HSIRDY)
    {
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); // 使能预取指
        FLASH_SetLatency(FLASH_ACR_LATENCY_2); // 设置等待
        RCC_HCLKConfig(RCC_SYSCLK_Div1); //HCLK = SYSCLK = 72MHz
        RCC_PCLK1Config(RCC_SYSCLK_Div2); //PCLK1 = HCLK / 2 = 36MHz
        RCC_PCLK2Config(RCC_SYSCLK_Div1); //PCLK2 = HCLK / 1 = 72MHz
        RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_x); // RCC_RLLMul_x 用来超频 频率:(8*x)MHz
        RCC_PLLCmd(ENABLE); // 使能PLL
        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
        {
            // 等待PLL稳定
            ;
        }
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); // 设置系统时钟为PLL时钟
        while(RCC_GetSYSCLKSource() != 0x08)
        {
            // 等待设置系统时钟
            ;
        }
    }
    else
    {
        // 如果HSI启动失败, 用户在此添加处理错误代码
    }
}
