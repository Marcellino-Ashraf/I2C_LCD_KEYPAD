/*
THIS PROJECT IS AN APPLICATION ON THE I2C PERIPHERAL.

AUTHOR: MARCELLINO ASHRAF

HARDWARE COMPONENTS:
1- STM32F103C8 MICRO-CONTROLLER TO RECEIVE FROM KEYPAD.
2- STM32F103C8 MICRO-CONTROLLER TO SEND TO LCD.

THIS PROJECT FILE HAS THE CODE FOR THE STM32F103C8 MICRO-CONTROLLER TO RECEIVE FROM KEYPAD.
*/

#include "keypad.h"
#include "I2C.h"

void SystemInit(){}
	
int main ()
{
	uint8_t key;
	
	keypad_init();
	I2C_INIT();
	
	while (1)
	{
		key = keypad_getkey();
		if(key != 0)
			I2C_SEND_BYTE(1,key);
		delay_ms(100);
	}
	
	return 0;
}
