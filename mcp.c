#include "mcp.h"

uint8_t current_IODIRA;
uint8_t current_GPIOA;

void mcp23S17_init(void) {
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

    // All IO pins start as INPUT
    current_IODIRA = 0xFF;
    spi_write(0x41);
    spi_write(IODIRA);
    spi_write(current_IODIRA);
    // All IO pins start as LOW
    current_GPIOA = 0x00;
    spi_write(0x41);
    spi_write(IODIRA);
    spi_write(current_GPIOA);
}

void mcp23S17_conf_pin(uint8_t pin, uint8_t mode) {
    set_cs_low();

    // send device opcode = 0100 0001
    spi_write(0x41);
    // send register address
    spi_write(IODIRA);
    // update current state of IODIRA register
    if (mode == INPUT)
        current_IODIRA |= (1 << pin);
    else if (mode == OUTPUT)
        current_IODIRA &= (0 << pin);
    spi_write(current_IODIRA);

    set_cs_high();
}

uint8_t mcp23S17_write_pin(uint8_t pin, uint8_t data, uint8_t mode) {
    if (data == 1) current_GPIOA |= (1 << pin)
    else if (data == 0) current_GPIOA &= (0 << pin)

    set_cs_low();

    // send device opcode = 0100 0000 + mode
    spi_write(0x40 + mode);

    // send register address
    spi_write(GPIOA);

    // set data to be written
    uint8_t b = spi_write(current_GPIOA);

    set_cs_high();

    if(mode == READ) {
        return b;
    }
    else if (mode == WRITE) {
        return (uint8_t)0;
    }
}

