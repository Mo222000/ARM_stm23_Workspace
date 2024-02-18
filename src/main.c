#include <MCAL/RCC/RCC.h>

int main ()
{
    uint16_t status;
    
    while (1)
    {
        status = RCC_Control_AHB1Peripherals(RCC_PERI_AHB1ENR_GPIOA, Status_Enable);
    }
    
    return 0;
}