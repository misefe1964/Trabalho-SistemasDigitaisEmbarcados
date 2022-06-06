#ifndef _SPI_
#define _SPI_
#include "LPC17xx.h"

// define pins from expansor

// spi functions
void mcp23S17_init(void);
void mcp23S17_conf_pin(uint8_t pin, uint8_t mode);
void mcp23S17_write_pin(uint8_t reg_addr, uint8_t data);
void mcp23S17_read_pin(uint8_t reg_addr, uint8_t *data);

#endif
