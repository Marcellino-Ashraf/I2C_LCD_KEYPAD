#include "delay.h"

static volatile uint32_t delay;

void delay_us(uint32_t us)
{
	SysTick->LOAD = 7;
	SysTick->CTRL = CLKSOURCE | ENABLE;
	while (us)
	{
		if (SysTick->CTRL & COUNTFLAG)
		{
			us--;
		}
	}
	SysTick->CTRL = 0;
}

void delay_ms(uint32_t ms)
{
	delay = ms;
	SysTick->LOAD = 7999;
	SysTick->CTRL = CLKSOURCE | TICKINT | ENABLE;
	while (delay){}
	SysTick->CTRL = 0;
}

void SysTick_Handler()
{
	delay--;
	SysTick->CTRL |= COUNTFLAG;
}
