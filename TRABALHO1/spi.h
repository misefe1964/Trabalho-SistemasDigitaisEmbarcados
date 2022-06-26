#ifndef _SPI_
#define _SPI_
#include "LPC17xx.h"
#include "misc.h"
#include "digital.h"
#include "delay.h"

#define SCK  PIN(0, 15)
#define SSEL PIN(0, 16)
#define MISO PIN(0, 17)
#define MOSI PIN(0, 18)

#define SCK_Freq 4000000

// spi functions
uint8_t spi_write(uint8_t byte);

void spi_init();

void set_cs_low();
void set_cs_high();

#endif
