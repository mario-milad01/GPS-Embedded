#include "GPIO.h"
#include "TM4C123GH6PM.h"

void portC_Pin0_Init(void)
{
    SYSCTL_RCGCGPIO_R |= 0x04;                
    while ((SYSCTL_PRGPIO_R & 0x04) == 0);   

    GPIO_PORTC_LOCK_R = 0x4C4F434B;          
    GPIO_PORTC_CR_R |= 0x01;                  
    GPIO_PORTC_AMSEL_R &= ~0x01;              
    GPIO_PORTC_PCTL_R &= ~0x0000000F;         
    GPIO_PORTC_DIR_R |= 0x01;                 
    GPIO_PORTC_AFSEL_R &= ~0x01;              
    GPIO_PORTC_DEN_R |= 0x01;                 
}
