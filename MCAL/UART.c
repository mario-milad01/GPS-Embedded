#include "TM4C123GH6PM.h"
#include "UART.h"
#include <stdint.h>


void UART4_Init(void){ 
  SYSCTL_RCGCUART_R |= 0x00000010;     
  SYSCTL_RCGCGPIO_R |= 0x00000004;     
	while( (SYSCTL_PRGPIO_R &0x04 ) ==0){} ;
  UART4_CTL_R &= ~0x0001;              
  UART4_IBRD_R = 43;                  
  UART4_FBRD_R = 26;                   
  UART4_LCRH_R = 0x00000070;           
  UART4_CTL_R |= 0x0001;               
  GPIO_PORTC_AFSEL_R |= 0x30;          
  GPIO_PORTC_DEN_R |= 0x30;            
  GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R & 0xFF00FFFF) | 0x00220000; 
  GPIO_PORTC_AMSEL_R &= ~0x30;        
}
void UART4_Send(char data)
{
    while (UART4_FR_R & UART_FR_TXFF) ;       
    UART4_DR_R = (uint32_t)data;
}

char UART4_Receive(void)
{
    while (UART4_FR_R & UART_FR_RXFE) ;      
    return (char)(UART4_DR_R & 0xFF);
}
