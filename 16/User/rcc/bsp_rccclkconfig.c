#include "bsp_rccclkconfig.h"

void HSE_SetSysClk()
{
    // 使能 HSE
    RCC_HSEConfig(HSE_ON);
    RCC_WaitForHSEStartUp
}