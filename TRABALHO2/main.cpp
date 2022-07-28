#include "digital.hpp"
#include <stdio.h>
#include <string.h>
#include "nrf24.hpp"
#include "delay.hpp"
#include "uart.h"

int main(void)
{
   int receiver_mode = 1;

   SystemInit();
	 UART0_Init(9600);
	 uint8_t buffer[20];
	 uint16_t x;
	 nrf24_init();

	 if(receiver_mode) {
      while(1) {
         nrf24_recebe(buffer);
         buffer[TAMANHO_MSG]=0;
         printf("received=%s\n",(char*)buffer);
		  }
	 } else {
      x = 0;
      while(1) {
         sprintf((char*)buffer, "TestMsg %d",x);
         nrf24_transmite(buffer);
         x++;
      }
   }

	 return 0;

}
