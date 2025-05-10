#define NVIC_ST_CTRL_R      (*((volatile unsigned long *)0xE000E010)) 
#define NVIC_ST_RELOAD_R    (*((volatile unsigned long *)0xE000E014)) 
#define NVIC_ST_CURRENT_R   (*((volatile unsigned long *)0xE000E018)) 
void SYSTICK_Init(void);
void SYSTICK_Wait_10ms(unsigned int delay);
void SYSTICK_Wait_seconds(unsigned int delay_sec);