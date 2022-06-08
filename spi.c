#include "spi.h"

uint8_t spi_write(uint8_t byte){
    uint8_t valor = 0;
    uint8_t bit;
    for(x = 0; x <8; x++) {
        bit = (byte >> (7-x) & 1;
        digital_write(MOSI, bit);
        digital_write(SCK, HIGH);
        delay_ms(50);
        valor = (valor << 1) | digital_read(MISO);
        digital_write(SCK, LOW);
        delay_ms(50);
    }
    return (valor);
}
