#ifndef _SPI_
#define _SPI_
#include "LPC17xx.h"
#include "misc.h"
#include "digital.h"
#include "delay.h"

uint8_t spi_write(uint8_t byte);

void set_cs_low();
void set_cs_high();

#endif

