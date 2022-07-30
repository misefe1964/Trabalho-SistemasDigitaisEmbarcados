#include "digital.h"
#include <string.h>
#include <stdio.h>
#include "nrf24.hpp"
#include "delay.hpp"
#include "uart.hpp"
#include "lcd.hpp"

int main(void)
{
   int receiver_mode = 1;

   SystemInit();
   lcd_init();
	 UART0_Init(115200);
     char *buffer_rec = 0;
	 /* uint16_t x; */
	 nrf24_init();

	 if(receiver_mode) {
          while(1) {
            scanf("%s", buffer_rec);
          }
	 } else {
          while(1) {
              printf("OI");
              delay_ms(2000);
              printf("OI1");
              delay_ms(2000);
              printf("OI2");
              delay_ms(2000);
              printf("OI3");
              delay_ms(2000);
              printf("OI4");
              delay_ms(2000);
              printf("OI5");
              delay_ms(2000);
              printf("OI6");
              delay_ms(2000);
              printf("OI7");
              delay_ms(2000);
              printf("OI8");
              delay_ms(2000);
              printf("OI9");
              delay_ms(2000);
              printf("OI10");
              delay_ms(2000);
          }
   }

	 return 0;

}
