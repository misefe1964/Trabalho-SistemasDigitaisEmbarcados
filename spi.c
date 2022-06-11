#include "spi.h"

uint8_t spi_write(uint8_t byte){
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
