#include "delay.h"
#include "LCD_DRIVER.h"
#include "usart.h"

#define KEYPAD 					GPIOB
#define KEYPAD_GPIO_EN	(1<<3)		//in case KEYPAD is connected to GPIOB
#define ROW_A	 					8
#define ROW_B	 					9
#define ROW_C	 					10
#define ROW_D	 					11
#define COLUMN_1				12
#define COLUMN_2				13
#define COLUMN_3				14
#define COLUMN_4				15

void keypad_init(void);
uint8_t keypad_kbhit(void);
uint8_t keypad_getkey(void);
uint8_t keypad_getchar(void);
