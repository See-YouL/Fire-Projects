#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_key.h"

#define GPIOB_ODR_Addr (GPIOB_BASE+0x0C)
#define GPIOA_IDR_Addr (GPIOA_BASE+0x08)
#define GPIOC_IDR_Addr (GPIOC_BASE+0x08)
#define PBout(n) *(unsigned int*)((GPIOB_ODR_Addr&0xF0000000) + 0x02000000 + ((GPIOB_ODR_Addr&0x00FFFFFF)<<5)+(n<<2))
#define PAin(n) *(unsigned int*)((GPIOA_IDR_Addr&0xF0000000) + 0x02000000 + ((GPIOA_IDR_Addr&0x00FFFFFF)<<5)+(n<<2))
#define PCin(n) *(unsigned int*)((GPIOC_IDR_Addr&0xF0000000) + 0x02000000 + ((GPIOC_IDR_Addr&0x00FFFFFF)<<5)+(n<<2))

void Delay(uint32_t count)
{
    for( ; count != 0; count--)
    {
        uint32_t current;
        for(current = count; current != 0; current--)
        {
            ;
        }
    }
    
}

int main(void)
{
    LED_GPIO_Config();
    KEY_GPIO_Config();

#if 0 // #if 1时，位带实现GPIO输出
    while(1)
    {
        PBout(1) = 1;
        Delay(0xFFF); // 延时
        PBout(1) = 0;
        Delay(0xFFF); // 延时
    }

#else // #if 0 时，位带实现GPIO输入
    while(1)
    {
        if(PAin(0) == KEY_ON)
        {
            Delay(0xFFF); // 加入软件消抖后可正常运行
            while(PAin(0) == KEY_ON) // 等待按键释放
            {
                ;
            }
            LED_B_TOGGLE;
        }

        if(PCin(13) == KEY_ON)
        {
            Delay(0xFFF); // 加入软件消抖后可正常运行
            while(PCin(13) == KEY_ON) // 等待按键释放
            {
                ;
            }
            LED_B_TOGGLE;
        }
    }

#endif
}
