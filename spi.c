#include "spi.h"

void spi_init() {
    pinMode(MOSI,OUTPUT);
    pinMode(MISO,INPUT);
    pinMode(SCK,OUTPUT);
    pinMode(SSEL,OUTPUT);

    set_cs_high();
  
}

uint8_t spi_write(uint8_t byte) {
    uint8_t valor = 0;
    uint8_t bit;
    for(uint8_t x = 0; x <8; x++) {
        bit = (byte >> (7-x)) & 1;
        digitalWrite(MOSI, bit);
        digitalWrite(SCK, HIGH);
        delay_ms(5);
        valor = (valor << 1 | digitalRead(MISO));
        digitalWrite(SCK, LOW);
        delay_ms(5);
    }
    return (valor);
}

void set_cs_low() {
    digitalWrite(SSEL, LOW);
}

void set_cs_high() {
    digitalWrite(SSEL, HIGH);
}

