#ifndef _MCP
#define _MCP_
#include "LPC17xx.h"
#include "misc.h"
#include "spi.h"

#define OUTPUT 0b0
#define INPUT 0b1

void mcp23S17_init(void);
void mcp23S17_conf_pin(uint8_t reg_addr, uint8_t mode);
void mcp23S17_write_pin(uint8_t reg_addr, uint8_t data);

#endif

