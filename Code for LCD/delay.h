#include <stm32f10x.h>

//SysTick control and status register (STK_CTRL)
#define COUNTFLAG	1<<16
#define CLKSOURCE	1<<2
#define TICKINT		1<<1
#define ENABLE		1<<0

//SysTick calibration value register (STK_CALIB)
#define NOREF	1<<31
#define SKEW	1<<30

void delay_us (uint32_t us);
void delay_ms(uint32_t ms);
