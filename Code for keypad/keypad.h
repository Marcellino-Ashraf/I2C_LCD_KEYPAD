#include "delay.h"
#include "LCD_DRIVER.h"

#define KEYPAD 					GPIOA
#define KEYPAD_GPIO_EN	(1<<2)		//in case KEYPAD is connected to GPIOA
#define ROW_A	 					0
#define ROW_B	 					1
#define ROW_C	 					2
#define ROW_D	 					3
#define COLUMN_1				4
#define COLUMN_2				5
#define COLUMN_3				6
#define COLUMN_4				7

void keypad_init(void);
uint8_t keypad_kbhit(void);
uint8_t keypad_getkey(void);
uint8_t keypad_getchar(void);
