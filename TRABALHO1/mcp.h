#ifndef _MCP
#define _MCP_
#include "LPC17xx.h"
#include "misc.h"
#include "spi.h"
#include "mcp23S17.h"
#include "seg.h"

#define OUTPUT 0
#define INPUT 1
#define WRITE 0
#define READ 1

void mcp23S17_init(void);
void mcp23S17_conf_pin(uint8_t pin, uint8_t mode);
uint8_t mcp23S17_write_pin(uint8_t pin, uint8_t data, uint8_t mode);
void mcp23S17_invert_pin(uint8_t pin);
#endif
