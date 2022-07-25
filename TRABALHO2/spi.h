#ifndef _SPI_
#define _SPI_
#include "LPC17xx.h"
#include "misc.h"
#include "digital.h"
#include "delay.h"

#define SCK  PIN(1, 26)
#define CS   PIN(1, 25)
#define MISO PIN(1, 24)
#define MOSI PIN(1, 23)

#define SCK_Freq 4000000

// spi functions
uint8_t spi_write(uint8_t byte);
void spi_configura();
void spi_habilita();
void spi_desabilita();

#endif
