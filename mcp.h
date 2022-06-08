#ifndef _MCP
#define _MCP_
#include "LPC17xx.h"
#include "misc.h"

// define pins from expansor

// mcp functions
void mcp23S17_init(void);
void mcp23S17_conf_pin(uint8_t reg_addr, uint8_t mode);
void mcp23S17_write_pin(uint8_t reg_addr, uint8_t data);

#endif
