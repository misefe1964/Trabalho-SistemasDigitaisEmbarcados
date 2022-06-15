#include "spi.h"

static uint32_t spi_GetPclk(void);

void spi_init() {
    pinMode(MOSI,OUTPUT);
    pinMode(MISO,INPUT);
    pinMode(SCK,OUTPUT);
    pinMode(SSEL,OUTPUT);

    // set registers
    LPC_SC->PCONP |= bit8; // power on PCSPI
    LPC_SC->PCLKSEL0 |= bit16;
    LPC_SC->PCLKSEL0 |= bit17; // select clock for SPI

    // PINSEL0[31:30] = 11, PSI Clock = SCK
    LPC_PINCON->PINSEL0 |= bit30; 
    LPC_PINCON->PINSEL0 |= bit31;
    // PINMODE
    // PINSEL1
    LPC_PINCON->PINSEL1 |= bit0;
    LPC_PINCON->PINSEL1 |= bit1; // select SSEL

    LPC_PINCON->PINSEL1 |= bit2;
    LPC_PINCON->PINSEL1 |= bit3; // select MISO

    LPC_PINCON->PINSEL1 |= bit4;
    LPC_PINCON->PINSEL1 |= bit5; // select MOSI

    //S0SPINT
    LPC_SPI->SPINT &= nbit0; // interrupt flag is not set

    LPC_SPI->SPCR |= bit3; 
    LPC_SPI->SPCR &= nbit4;   // bit is sent on rising edge and sampled on falling edge

    LPC_SPI->SPCCR = spi_GetPclk()/SCK_Freq; // Set Spi Clock
    
    set_cs_high();
  
}

uint8_t spi_write(uint8_t byte) {
    uint8_t valor = 0;
    uint8_t bit;
    for(uint8_t x = 0; x <8; x++) {
        bit = (byte >> (7-x)) & 1;
        digitalWrite(MOSI, bit);
        digitalWrite(SCK, HIGH);
        delay_ms(50);
        valor = (valor << 1 | digitalRead(MISO));
        digitalWrite(SCK, LOW);
        delay_ms(50);
    }
    return (valor);
}

void set_cs_low() {
    digitalWrite(SSEL, LOW);
}

void set_cs_high() {
    digitalWrite(SSEL, HIGH);
}

static uint32_t spi_GetPclk(void) {
    uint32_t v_spiPclk_u32,v_Pclk_u32;
    v_spiPclk_u32 = (LPC_SC->PCLKSEL0 >> 16) & 0x03;
    switch( v_spiPclk_u32 )
    {
    case 0x00:
        v_Pclk_u32 = SystemCoreClock/4;           //SystemFrequency or  SystemCoreClock
        break;
    case 0x01:
        v_Pclk_u32 = SystemCoreClock;
        break;
    case 0x02:
        v_Pclk_u32 = SystemCoreClock/2;
        break;
    case 0x03:
        v_Pclk_u32 = SystemCoreClock/8;
        break;
    }
    return (v_Pclk_u32);
}
