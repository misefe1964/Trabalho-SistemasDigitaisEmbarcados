


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



#define BOTAO PIN_2_10

void configura_chaves(void)
{
	pinMode(PIN_1_08, INPUT);
	pinMode(PIN_1_04, INPUT);
	pinMode(PIN_1_01, INPUT);
	pinMode(PIN_1_00, INPUT);

	pinMode(PIN_2_10, INPUT);


}

uint8_t le_configuracao_chaves(void)
{
	uint8_t v=0;

	v = ((digitalRead(PIN_1_08) << 3) | 
         (digitalRead(PIN_1_04) << 2) | 
        (digitalRead(PIN_1_01) << 1) | 
         (digitalRead(PIN_1_00) )) ;
	return v;
}
int main ( void ) 
{
	uint8_t x, mesa, solicita_atendimento;
	uint8_t buffer[10];


	SystemInit();
   	UART0_Init(9600);

	
	

	nrf24_init ();
	
	configura_chaves();
	mesa=le_configuracao_chaves();
	printf("Cliente mesa %d\n",mesa);
	solicita_atendimento = 0;
	while(1)
	{
		if (digitalRead(BOTAO)==0)
		{
			printf("botao apertado\n");
			solicita_atendimento=1;
		}
		if (solicita_atendimento)
		{
			buffer[0]=mesa;
			buffer[1]=0;
			nrf24_transmite(buffer);
			delay_ms(100);
		}

		x = nrf24_recebe(buffer);
		if (x)
		{
			printf("recebida confirmacao da mesa=%d\n",buffer[0]);
			if (buffer[0]==mesa)
			{		
				printf("mensagem atendida\n");
				solicita_atendimento=0;
			}
		}
		
	}

	return 0 ;
}


