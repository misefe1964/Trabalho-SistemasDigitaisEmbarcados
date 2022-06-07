#include "spi.h"

void mcp23S17_init(void){
    // set registers
    LPC_SC->PCONP |= bit8; // power on PCSPI
    LPC_SC->PCLKSEL0 |= bit16;
    LPC_SC->PCLKSEL0 |= bit17; // select clock for SPU
    // PINSEL0[31:30] = 11, PSI Clock = SCK
    LPC_PINCON->PINSEL0 |= bit30; 
    LPC_PINCON->PINSEL0 |= bit31;
    // PINMODE
    // PINSEL1
    LPC_PINCON->PINSEL1 |= bit0;
    LPC_PINCON->PINSEL1 |= bit1; // select SSEL:q

    LPC_PINCON->PINSEL1 |= bit2;
    LPC_PINCON->PINSEL1 |= bit3; // select MISO

    LPC_PINCON->PINSEL1 |= bit4;
    LPC_PINCON->PINSEL1 |= bit5; // select MOSI

    //S0SPINT
    LPC_SPI->SPINT &= nbit0; // interrupt flag is not set
}
void mcp23S17_conf_pin(uint8_t pin, uint8_t mode){

}
void mcp23S17_write_pin(uint8_t reg_addr, uint8_t data){
}


