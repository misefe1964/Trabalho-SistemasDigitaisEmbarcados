#include "spi.h"

void spi_configura() {
  pinMode(MOSI,OUTPUT);
  pinMode(MISO,INPUT);
  pinMode(SCK,OUTPUT);
  pinMode(CS,OUTPUT);
  spi_desabilita();
}

uint8_t spi_write(uint8_t byte) {
  uint8_t valor = 0;
  uint8_t bit;
  for(uint8_t x = 0; x <8; x++) {
    bit = (byte >> (7-x)) & 1;
    digitalWrite(MOSI, bit);
    digitalWrite(SCK, HIGH);
    delay_us(50);
    valor = (valor << 1 | digitalRead(MISO));
    digitalWrite(SCK, LOW);
    delay_us(50);
  }
  return (valor);
}

void spi_habilita() {
  digitalWrite(CS, LOW);
}

void spi_desabilita() {
  digitalWrite(CS, HIGH);
}
