#include <MCAL/NVIC/NVIC.h>

void NVIC_TEST (void)
{
    NVIC_EnableIRQ(WWDG_IRQ);
    NVIC_DisableIRQ(WWDG_IRQ);
    NVIC_EnableIRQ(SPI1_IRQ);
    NVIC_SetGroupPriorityBits(GroupBits_2);
    NVIC_SetIRQPriority(WWDG_IRQ, 1, 1);
}