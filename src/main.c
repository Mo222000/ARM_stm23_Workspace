#include <MCAL/RCC/RCC.h>

int main ()
{
    RCC_Control_AHB1Peripherals(RCC_PERI_AHB1ENR_GPIOA, 3);
    RCC_Control_AHB1Peripherals(RCC_PERI_AHB1ENR_CRC, Status_Enable);
    RCC_ControlClock(RCC_ClkHSEON,Status_Enable);    
    RCC_SelectSystemClock(RCC_SYSCLK_HSE);
    while (1)
    {

    }
    
    return 0;
}