#include "Systick.h "
#include "TM4C123GH6PM.h"
#include <stdint.h>

void SYSTICK_Init(void){
	NVIC_ST_CTRL_R=0;
	NVIC_ST_RELOAD_R=0x00FFFFFF;
	NVIC_ST_CURRENT_R=0;
	NVIC_ST_CTRL_R=0X0005;
}

void SYSTICK_Wait_10ms(unsigned int delay){
	do{
	NVIC_ST_RELOAD_R = delay-1;
	NVIC_ST_CURRENT_R=0;
	}
	while((NVIC_ST_CTRL_R&0X00010000)==0);      //continue looping if count in ctrl register is still 0
}


void SYSTICK_Wait_seconds(uint32_t delay_sec){              //the delay here must be 5 to loop 500 time each time delay 10ms then this will produce delay 5sec
	unsigned long i;
	for(i=0;i<(delay_sec*100);i++){
		SYSTICK_Wait_10ms(800000);
	}
}
