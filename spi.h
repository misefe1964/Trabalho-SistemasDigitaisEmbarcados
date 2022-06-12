#ifndef _SPI_
#define _SPI_
#include "LPC17xx.h"
#include "misc.h"
#include "digital.h"
#include "delay.h"

#define MISO PIN(0, 17)
#define MOSI PIN(0, 18)
#define SCK  PIN(0, 15)

// spi functions
uint8_t spi_write(uint8_t byte);

#endif

