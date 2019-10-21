#include "keypad.h"
uint8_t key;

void keypad_init(void)
{
	RCC->APB2ENR |= KEYPAD_GPIO_EN;
	KEYPAD->CRL   = 0x44443333;
}

uint8_t keypad_kbhit(void)
{
	uint32_t col;
	
	//check to see any key pressed
	KEYPAD->ODR = 0xF0FF;				//enable all rows
	col = KEYPAD->IDR;		//read all columns
	if (col == 0)
		return 0;	//no key pressed
	else
		return 1;	//a key is pressed
}

uint8_t keypad_getkey(void)
{
	const uint8_t keymap[4][4] = {
	{'7', '8', '9', '/'},
	{'4', '5', '6', '*'},
	{'1', '2', '3', '-'},
	{'.', '0', '=', '+'}
	};
	
	uint32_t row, col;
	
	//check to see any key pressed first
	KEYPAD->ODR = 0xF0FF;				//enable all rows
	col = KEYPAD->IDR;		//read all columns
	if (col == 0)
		return 0;	//no key pressed
	
	/*If a key is pressed, it gets here to find out which key.
	Although it is written as an infinite loop, it will take one of the breaks or return in one pass.*/
	while (1)
	{
		row = 0;
		KEYPAD->ODR =	0xFEFF;		//enable row 0
		delay_us(2);							//wait for signal to settle
		col = KEYPAD->IDR & 0xF000;
		if (col) break;
		
		row = 1;
		KEYPAD->ODR =	0xFDFF;		//enable row 1
		delay_us(2);							//wait for signal to settle
		col = KEYPAD->IDR & 0xF000;
		if (col) break;
		
		row = 2;
		KEYPAD->ODR =	0xFBFF;		//enable row 2
		delay_us(2);							//wait for signal to settle
		col = KEYPAD->IDR & 0xF000;
		if (col) break;
		
		row = 3;
		KEYPAD->ODR =	0xF7FF;		//enable row 3
		delay_us(2);							//wait for signal to settle
		col = KEYPAD->IDR & 0xF000;
		if (col) break;
		
		return 0;
	}
	
	//gets here when one of the rows has key pressed
	if (col == 0x1000) return keymap[row][0];		//key in comlumn 0
	if (col == 0x2000) return keymap[row][1];		//key in comlumn 1
	if (col == 0x4000) return keymap[row][2];		//key in comlumn 2
	if (col == 0x8000) return keymap[row][3];		//key in comlumn 3
	
	return 0;		//just to be safe
}

uint8_t keypad_getchar(void)
{
	uint8_t key;
	
	//wait until the previous key is released
	do
	{
		while (keypad_getkey() != 0);
		delay_ms(20);		//debounce
	}while(keypad_getkey() != 0);
	
	do{
		key = keypad_getkey();
		delay_ms(20);		//debounce
	}while(keypad_getkey() != key);
	
	return key;
}
