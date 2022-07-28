


// Testa o acesso ao protocolo i2c enviado caracteres para serem gravados em posicoes sequenciais da memoria 24c64 EEPROM
// para compilar:  
//                    make
// para gravar na SystemInit();placa (usando o bootloader): 
//                   lpc21isp -control -bin main.bin /dev/ttyUSB0 115200 12000
//
// para gravar na placa (usando o JTAG)
//                   openocd -f lpc1768.cfg
// abrir outro shell
// telnet localhost 4444
// > reset halt
// > flash write_image erase main.bin 0x0 bin
// Este programa usa os pinos (PIN_0_27, PIN_0_28); que sao os usados pela EEPROM no kit
// Para usar no MBED deve-se trocar os pinos

#include "uart.h"
#include "digital.hpp"
#include <stdio.h>
#include <string.h>
#include "nrf24.hpp"
#include "delay.hpp"

int main ( void ) 
{
	SystemInit();
	nrf24_init();
	UART0_Init(9600);
	
	uint8_t buffer[20];
	uint16_t x;
	
	printf("Rodando transmissor...\n");

	x=0;
	
	while(1)
	{
		sprintf((char *)buffer, "lips %d",x);
	    	nrf24_transmite(buffer); 
	    	x++;
	}

	return 0 ;
}


