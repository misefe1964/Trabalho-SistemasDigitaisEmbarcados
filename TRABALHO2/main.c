#include "LPC17xx.h"
#include "uart.h"
#include "digital.h"
#include <stdio.h>
#include <string.h>
#include "nrf24.h"
#include "delay.h"

uint8_t buffer[50];
int modulo_receptor = 0; // mudar aqui para receptor ou transmissor

int main(void) {
    SystemInit();
    delay_init();
    UART0_Init(115200);
    nrf24_init();

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
      sprintf((char *)buffer, "Mi %d",x);
      nrf24_transmite(buffer); x++;
      delay_ms(1000);
    }
  }
}
