


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

#include "LPC17xx.h"
#include "uart.h"
#include "digital.h"
#include <stdio.h>
#include <string.h>
#include "nrf24.h"
#include "delay.h"

int main ( void ) 
{ 
    SystemInit();
    delay_init();
	uart_init();
	nrf24_init();

	uint8_t buffer[50];

	printf("Rodando receptor...\n");


	while(1)
	{
		

		//codigo para o receptor
		nrf24_recebe(buffer);
		buffer[TAMANHO_MSG]=0;
		printf("recebido=%s\n",(char *)buffer);
		
	}

	return 0 ;
}


