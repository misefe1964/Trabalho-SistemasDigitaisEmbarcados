#include "mcp.h"

uint8_t current_IODIRA;
uint8_t current_GPIOA;

void mcp23S17_init(void) {
    spi_init();
    // All IO pins start as INPUT
    set_cs_low();
    current_IODIRA = 0xFF;
    spi_write(0x40);
    spi_write(IODIRA);
    spi_write(current_IODIRA);
    set_cs_high();
    // All IO pins start as LOW
    current_GPIOA = 0x00;
    set_cs_low();
    spi_write(0x40);
    spi_write(IODIRA);
    spi_write(current_GPIOA);
    set_cs_high();
    // set pull-up resistor for GPIOA - port 0-3
    set_cs_low();
    spi_write(0x40);
    spi_write(GPPUA);
    spi_write(0x0F);
    set_cs_high();
}

void mcp23S17_conf_pin(uint8_t pin, uint8_t mode) {
    set_cs_low();
    // send device opcode = 0100 0000 (write)
    spi_write(0x40);
    // send register address
    spi_write(IODIRA);
    // update current state of IODIRA register
    if (mode == INPUT)
        current_IODIRA |= (1 << pin);
    else if (mode == OUTPUT)
        current_IODIRA &= ~(1 << pin);
    spi_write(current_IODIRA);
    set_cs_high();
}

uint8_t mcp23S17_write_pin(uint8_t pin, uint8_t data, uint8_t mode) {
    if (data == 1) current_GPIOA |= (1 << pin);
    else if (data == 0) current_GPIOA &= ~(1 << pin);

    set_cs_low();
    // send device opcode = 0100 0000 + mode
    spi_write(0x40 + mode);

    // send register address
    spi_write(GPIOA);

    // set data to be written
    uint8_t b = spi_write(current_GPIOA);
    set_cs_high();

    if(mode == READ) {
        return (b >> pin) & 1;
    }
    return (uint8_t)0;
}

void mcp23S17_invert_pin(uint8_t pin) {
    uint8_t current = mcp23S17_write_pin(pin, 0, READ);
    mcp23S17_write_pin(pin, !current, WRITE);
}

