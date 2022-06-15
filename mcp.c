#include "mcp.h"

uint8_t current_IODIRA;
uint8_t current_GPIOA;

void mcp23S17_init(void) {
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
    if (data == 1) current_GPIOA |= (1 << pin);
    else if (data == 0) current_GPIOA &= (0 << pin);

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
    return (uint8_t)0;
}

