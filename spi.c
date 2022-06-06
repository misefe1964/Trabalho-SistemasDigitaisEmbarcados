#include "spi.h"

void mcp23S17_init(void){
    // set registers
    PCONP->PCSPI = 1; // power
    PCLKSEL0->PCLK_SPI = 0; // clock
    // PINSEL0[31:30] = 11, PSI Clock = SCK
    PINSEL |= bit30; 
    PINSEL |= bit31;
    // PINMODE
    // PINSEL1
    PINSEL1 |= bit0;
    PINSEL1 |= bit1; // select SSEL

    PINSEL1 |= bit2;
    PINSEL1 |= bit3; // select MISO

    PINSEL1 |= bit4;
    PINSEL1 |= bit5; // select MOSI

    //S0SPINT
    S0SPINT->SPIF = 0 // interrupt flag is not set
    
}
void mcp23S17_conf_pin(uint8_t pin, uint8_t mode){
}
void mcp23S17_write_pin(uint8_t reg_addr, uint8_t data){
}


