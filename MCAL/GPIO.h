#ifndef GPIO_H
#define GPIO_H
#include "TM4C123GH6PM.h"
#define BUZZER_ON  (GPIO_PORTC_DATA_R |= 0x01)
#define BUZZER_OFF (GPIO_PORTC_DATA_R &= ~0x01)

void portC_Pin0_Init(void);

#endif
