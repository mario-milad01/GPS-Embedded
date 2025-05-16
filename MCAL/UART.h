#ifndef UART_H
#define UART_H

#include <stdint.h>
void UART4_Init(void);
void UART4_Send(char data);
char UART4_Receive(void);

#endif 
