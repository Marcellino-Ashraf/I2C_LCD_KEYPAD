#include <stm32f10x.h>

void I2C_INIT();
void I2C_SEND_BYTE(uint8_t address,uint8_t data);
char I2C_RECEIVE_BYTE();
