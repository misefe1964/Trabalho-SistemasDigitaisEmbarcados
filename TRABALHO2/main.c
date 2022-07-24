#include "LPC17xx.h"
#include "uart.h"
#include "digital.h"
#include <stdio.h>
#include <string.h>
#include "nrf24.h"
#include "delay.h"

SystemInit();
delay_init();
uart_init();
nrf24_init();

uint8_t buffer[10];
int modulo_receptor = 1

void main {
  if(modulo_receptor) {
    printf("Rodando receptor...\n");
    while(1) {
      //codigo para o receptor
      nrf24_recebe(buffer);
      buffer[TAMANHO_MSG]=0;
      printf("recebido=%s\n",(char*)buffer);
    }
  }
  else {
    uint16_t x = 0;
    printf("Rodando transmissor...\n");
    while(1) {
      sprintf((char *)buffer, "oi %d",x);
      nrf24_transmite(buffer); x++;
      delay_ms(100);
    }
  }
}
