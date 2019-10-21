#include <stm32f10x.h>
#include "LCD_DRIVER.h"
#include "delay.h"

void LCD_init(void)
{
	//Initialize ports A
	RCC->APB2ENR |= IOAEN;
	GPIOA->CRL = 0x33333333;
	
	delay_ms(20);
	LCD_nibble_write(0x30, 0);
	delay_ms(5);
	LCD_nibble_write(0x30, 0);
	delay_ms(100);
	LCD_nibble_write(0x30, 0);
	delay_ms(40);
	
	LCD_nibble_write(0x20, 0);
	delay_ms(40);
	
	LCD_command(LCD_4_bit_data);
	LCD_command(LCD_shift_cursor_right);
	LCD_command(LCD_clear);
	LCD_command(LCD_cursor_blinking);
}

void LCD_nibble_write(unsigned char data, unsigned char control)
{
	data    &= 0xF0;				//Clear lower nibble for data
	control &= 0x0F;				//Clear Upper nibble for control
	
	LCD_PORT->ODR = data | control;		    	//RS = control, R/W = 0
	LCD_PORT->ODR = data | control | E;			//Pulse E
	delay_us(5);
	LCD_PORT->ODR = data | control;
	//LCD_PORT->ODR &= !E;
	//LCD_PORT->ODR = 0;
}

void LCD_command(unsigned char command)
{
	LCD_nibble_write(command & 0xF0, 0);  	//Upper nibble first
	LCD_nibble_write(command << 4, 0);  		//Lower nibble last
	
	if (command < 4)
		delay_ms(2);						//Commands 1 & 2 take up to 1.64 ms
	else
		delay_us(40);						//All other commands take up to 40 us
}

void LCD_data(unsigned char data)
{
	LCD_nibble_write(data &0xF0, RS);  		//Upper nibble first
	LCD_nibble_write(data << 4, RS);  		//Lower nibble last
	
	delay_us(40);
}

void LCD_string(char string[])
{
	//unsigned int size = sizeof(*string);
	unsigned int counter = 0;
	
	//for (counter = 0; counter < size; counter++)
	while(string[counter] != '\0')
	{
		LCD_data(string[counter]);
		counter++;
	}
}

