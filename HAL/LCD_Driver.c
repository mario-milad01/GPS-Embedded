#include "TM4C123.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "LCD_Driver.h"
#include "GPS.h"
#include "UART.h"


static void delay(volatile uint32_t d)
{
    while (d--) { __NOP(); }
}

/* Drive the eight data pins in one shot */
static void Printdata(uint8_t data)
{
    if (data & 0x01U) GPIOA->DATA |=  (1U << 7); else GPIOA->DATA &= ~(1U << 7);
    if (data & 0x02U) GPIOA->DATA |=  (1U << 6); else GPIOA->DATA &= ~(1U << 6);
    if (data & 0x04U) GPIOA->DATA |=  (1U << 5); else GPIOA->DATA &= ~(1U << 5);
    if (data & 0x08U) GPIOB->DATA |=  (1U << 4); else GPIOB->DATA &= ~(1U << 4);
    if (data & 0x10U) GPIOE->DATA |=  (1U << 5); else GPIOE->DATA &= ~(1U << 5);
    if (data & 0x20U) GPIOE->DATA |=  (1U << 4); else GPIOE->DATA &= ~(1U << 4);
    if (data & 0x40U) GPIOE->DATA |=  (1U << 1); else GPIOE->DATA &= ~(1U << 1); /* D6 */
    if (data & 0x80U) GPIOD->DATA |= (1U << 3); else GPIOD->DATA &= ~(1U << 3);  /* D7 */
}

static void lcd_pulse_en(void)
{
    GPIOD->DATA |=  (1U << 2);   
    delay(10000U);
    GPIOD->DATA &= ~(1U << 2);  
}

static void lcd_cmd(uint8_t cmd)
{
    Printdata(cmd);
    GPIOD->DATA &= ~(1U << 1);   
    GPIOD->DATA &= ~(1U << 0);   
    lcd_pulse_en();
}

static void lcd_data(uint8_t data)
{
    Printdata(data);
    GPIOD->DATA &= ~(1U << 1);   
    GPIOD->DATA |=  (1U << 0);   
    lcd_pulse_en();
}

static void lcd_string(const char *str, uint8_t len)
{
    uint8_t i;
    for (i = 0U; i < len; i++) {
        lcd_data((uint8_t)str[i]);
    }
}

static void lcd_init(void)
{
    lcd_cmd(0x38U);  
    lcd_cmd(0x06U);  
    lcd_cmd(0x0CU);  
    lcd_cmd(0x01U);  
    delay(20000U);
}

void Lcd_display(char min_index)
{
    SYSCTL->RCGCGPIO |= (1U << 0) | (1U << 1) | (1U << 3) | (1U << 4);
    delay(100000U);

    /* Data lines */
    GPIOA->DEN |= (1U << 5) | (1U << 6) | (1U << 7);
    GPIOA->DIR |= (1U << 5) | (1U << 6) | (1U << 7);

    GPIOB->DEN |= (1U << 4);               /* only PB4 for D3 */
    GPIOB->DIR |= (1U << 4);

    GPIOE->DEN |= (1U << 1) | (1U << 4) | (1U << 5);
    GPIOE->DIR |= (1U << 1) | (1U << 4) | (1U << 5);

    /* Control lines + D7 on Port D */
    GPIOD->DEN |= (1U << 0) | (1U << 1) | (1U << 2) | (1U << 3);
    GPIOD->DIR |= (1U << 0) | (1U << 1) | (1U << 2) | (1U << 3);

    /* LCD init */
    lcd_init();
    lcd_cmd(0x80);     /* home first row */
		lcd_string("Nearest Location",16);
		lcd_cmd(0xC0);     /* keep display on, move to 2nd row by writing 0xC0 later */
    switch ((int)(min_index - '0')) {
    case 0:  lcd_string("Faculty's Mosque",16);   
			break;
    case 1:  lcd_string("Hall A & B",10); 
			break;
    case 2:  lcd_string("Hall C & D", 6);              
			break;
    case 3:  lcd_string("Luban's Workshop",16);          
			break;
    case 4:  lcd_string("ICHEP-Building", 14);          
			break;
    case 5:  lcd_string("Kharasana Build",15);          
			break;
    }
		
}
