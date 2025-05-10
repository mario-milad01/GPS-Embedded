#include "TM4C123GH6PM.h"
#include <stdio.h>

// X  = Y : X IS CONNECTED T OY LIKE THE FOLLOWING:
// RS = PD0
// RW = PD1
// EN = PD2

// D0 = PA7
// D1 = PA6
// D2 = PA5
// D3 = PB4
// D4 = PE5
// D5 = PE4
// D6 = PB1
// D7 = PB0

void Printdata(unsigned char data) // data = 8 bit hexadecimal data
{
	//zeroth bit = D0 = PA7 
	if( (data&0x01) == 0x01 ) 		 {	GPIOA->DATA = GPIOA->DATA | (1<<7);}
  else 													 { 	GPIOA->DATA = GPIOA->DATA & (~(1<<7));}
	
	//first bit = D1 = PA6 
	if ( (data&0x02) == 0x02 )    { 	GPIOA->DATA = GPIOA->DATA | (1<<6);}
	else 														{	GPIOA->DATA = GPIOA->DATA & (~(1<<6));}
	
	//second bit = D2 = PA5 
	if ( (data&0x04) == 0x04 )    {	GPIOA->DATA = GPIOA->DATA | (1<<5);}
	else 														{ GPIOA->DATA = GPIOA->DATA & (~(1<<5));}
	
	//third bit = D3 = PB4 
	if ( (data&0x08) == 0x08 )    { GPIOB->DATA = GPIOB->DATA | (1<<4);}
	else 														{ GPIOB->DATA = GPIOB->DATA & (~(1<<4));}
	
	//fourth bit = D4 = PE5 
	if ( (data&0x10) == 0x10 )    { GPIOE->DATA = GPIOE->DATA | (1<<5);}
	else 														{ GPIOE->DATA = GPIOE->DATA & (~(1<<5));}
	
	//fifth bit = D5 = PE4 
	if ( (data&0x20) == 0x20 )    { GPIOE->DATA = GPIOE->DATA | (1<<4);}
	else 													 { GPIOE->DATA = GPIOE->DATA & (~(1<<4));}
	
	//sixth bit = D6 = PB1 
	if ( (data&0x40) == 0x40 )    { GPIOB->DATA = GPIOB->DATA | (1<<1);}
	else 														{ GPIOB->DATA = GPIOB->DATA & (~(1<<1));}
	
	//seventh bit = D7 = PB0 
	if ( (data&0x80) == 0x80 )    { GPIOB->DATA = GPIOB->DATA | (1<<0);}
	else 														{ GPIOB->DATA = GPIOB->DATA & (~(1<<0));}
}


void delay(long d)
{
	while(d--);
}

void lcd_cmd(unsigned char cmd) //PASSING DATA TO BE PRINTED ON THE LCD
{
	Printdata(cmd); 					 		 //pass the 8-bits data to the datalines of lcd
	GPIOD->DATA &= (~(1<<1)); 		//turn off the R/W pin for enabling the write operation in lcd
	GPIOD->DATA &= (~(1<<0)); 				//turn off the RS pin for writing to the data register of lcd
	GPIOD->DATA |= (1<<2);				//turn on the enable pin of lcd for enabling the clk of lcd
	delay(10000);									//wait for sometime using (delay) for a 1mS or less
	GPIOD->DATA &= (~(1<<2)); 	  //turn off the enable pin of the lcd
}


void lcd_data(unsigned char data) //PASSING INSTRUCTIONS FOR LCD
{
	Printdata(data); 					 		 //pass the 8-bits data to the datalines of lcd
	GPIOD->DATA &= (~(1<<1)); 		//turn off the R/W pin for enabling the write operation in lcd
	GPIOD->DATA |= (1<<0); 				//turn on the RS pin for writing to the data register of lcd
	GPIOD->DATA |= (1<<2);				//turn on the enable pin of lcd for enabling the clk of lcd
	delay(10000);									//wait for sometime using (delay) for a 1mS or less
	GPIOD->DATA &= (~(1<<2)); 	  //turn off the enable pin of the lcd
}

void lcd_string(char *str,unsigned char len) //FOR PASSING A STRING OF CHARs TO LCD TO BE PRINTED
{
	char var;
	for (var=0 ; var<len ; var++)
	{
		lcd_data(str[var]);
	}
}
void lcd_init(void) //BASIC INSTRUCTION SETS FOR INITIALLIZING THE LCD
{
	lcd_cmd(0x38);     // 8-bits mode utilizing 1 columns and 2 rows
	lcd_cmd(0x06);     //autoincrementing the cursor when it prints the data in current
	lcd_cmd(0x0C);     //cursor off and display on
	lcd_cmd(0x01);     //clear screen
}


void transfer(float num) //float min.dist into an array of characters
{
    char buffer[20];
	  int lenn = sizeof(buffer);
    snprintf(buffer, lenn , "%.2f", num);
	  lcd_string(buffer,lenn);
}


//finally: main
void mainn(char min_index , float mindist)
{
	SYSCTL->RCGCGPIO = SYSCTL->RCGCGPIO | (1<<0) | (1<<1) | (1<<3) | (1<<4); // clock of portA,portB,portD,portE

	// Digitalise the datapins and config pins
	GPIOA->DEN |=(1<<5)|(1<<6)|(1<<7); //5-6-7
	GPIOB->DEN |=(1<<0)|(1<<1)|(1<<4); //0-1-4
	GPIOD->DEN |=(1<<0)|(1<<1)|(1<<2); //0-1-2
	GPIOE->DEN |=(1<<4)|(1<<5); //4-5
	
	//Direction of datapins and config pins -> output pins
	GPIOA->DIR |=(1<<5)|(1<<6)|(1<<7); //5-6-7
	GPIOB->DIR |=(1<<0)|(1<<1)|(1<<4); //0-1-4
	GPIOD->DIR |=(1<<0)|(1<<1)|(1<<2); //0-1-2
	GPIOE->DIR |=(1<<4)|(1<<5); //4-5
	delay(10000);
	
	lcd_init();
	lcd_cmd(0x80); //asking lcd to move the cursor to first row and first column
	
	switch (min_index)
	{
		case '0':
			{lcd_string("HALL:A",6); break;}
		case '1':
			{lcd_string("HALL:C",6); break;}
		case '2':
			{lcd_string("HALL:1",6); break;}
		//case '3':
		//	{lcd_string("HALL:+",6); break;}
		//case '4':
			//{lcd_string("HALL:-",6); break;}
		default:
			{lcd_string("error",5); break;}
	}
	
	lcd_cmd(0xC0); //asking lcd to move the cursor to second row and first column
	
  transfer(mindist);
	
	//0x80
	//0xC0
	while(1)
	{
	}
}
