#include "interrupcao_externa.h"
#include "digital.h"

#include <stdio.h>


static LPC_GPIO_TypeDef   (* const LPC_GPIO[5] ) = { LPC_GPIO0, LPC_GPIO1, LPC_GPIO2, LPC_GPIO3, LPC_GPIO4  };

void (*funcao[4])(void); 

#define EINT0_CLR (1 << 0)
#define EINT0_EDGE	1

#define EINT1_CLR (1 << 1)
#define EINT1_EDGE	2

#define EINT2_CLR (1 << 2)
#define EINT2_EDGE	4

#define EINT3_CLR (1 << 3)
#define EINT3_EDGE	8

// Apenas alguns pinos geram interrupcao externa. O pino 2.13 gera int ext3, o pino 2.12 gera int ext 2, o pino 2.11 gera int ext 1 e o pino 2.10 gera int ext 0
// deve-se escolher o pino a usar, configurar o registrador PINSEL para coloca-lo em funcao alternativa (bits 01)

// escolhe o modo, interrupcao por borda ou nivel
// se for por borda eh descida ou subida 
// habilita o tratador 0, 1, 2 ou 3 dependendo do pino usado

// escreve o tratador de interrupcao
// ele deve limpar um flag
static __IO uint32_t * LPC_MODE;


void habilita_interrupcao_externa (void)
{
	NVIC_EnableIRQ(EINT3_IRQn);   
}

void desabilita_interrupcao_externa(void)
{
	NVIC_DisableIRQ(EINT3_IRQn);  
}
/////
void configura_interrupcao_externa(void (*f)(void) , uint8_t numero, uint8_t borda)
{
	LPC_MODE = &(LPC_PINCON->PINMODE4);

	funcao[numero] = f;
	// Borda
	LPC_SC->EXTMODE &= ~(1<<numero);  //
	LPC_SC->EXTMODE |= (1<<numero);   //  eh borda  
 
	LPC_SC->EXTPOLAR &= ~(1 <<numero);	// por padrao eh borda descida
	switch (numero)
	{
		case PIN_2_13_INT_EXT_3:
				if (borda==BORDA_DESCIDA) pinMode(PIN_2_13, INPUT_PULLUP);
				else 
				{
					LPC_SC->EXTPOLAR |= (1 <<numero);
					pinMode(PIN_2_13, INPUT_PULLDOWN);
				}
				LPC_PINCON->PINSEL4 &= ~(0x3 << 26); // limpa os 2 bits
				LPC_PINCON->PINSEL4 |= (0x01<<26);   // escreve os 2 bits
				//NVIC_EnableIRQ(EINT3_IRQn);  		
				break;
		case PIN_2_12_INT_EXT_2:
				*(LPC_MODE) = (*LPC_MODE) | (3<<24);
				if (borda==BORDA_SUBIDA) LPC_SC->EXTPOLAR |= (1 <<numero);

				// Configura para int externa
				LPC_PINCON->PINSEL4 &= ~(0x3 << 24); // limpa os 2 bits
				LPC_PINCON->PINSEL4 |= (0x01<<24);   // escreve os 2 bits
				NVIC_EnableIRQ(EINT2_IRQn);  		
				break;
		case PIN_2_11_INT_EXT_1:
				if (borda==BORDA_DESCIDA)	pinMode(PIN_2_11, INPUT_PULLUP);
				else 
				{
					LPC_SC->EXTPOLAR |= (1 <<numero);
					pinMode(PIN_2_11, INPUT_PULLDOWN);
				}
				// Enabled External Interrupt 0 (the ISP button on RDB1768).
				LPC_PINCON->PINSEL4 &= ~(0x3 << 22); // limpa os 2 bits
				LPC_PINCON->PINSEL4 |= (0x01<<22);   // escreve os 2 bits
				NVIC_EnableIRQ(EINT1_IRQn);  
				break;				
		case PIN_2_10_INT_EXT_0:
				if (borda==BORDA_DESCIDA)	pinMode(PIN_2_10, INPUT_PULLUP);
				else 
				{
					LPC_SC->EXTPOLAR |= (1 <<numero);
					pinMode(PIN_2_10, INPUT_PULLDOWN);
				}		
				// Enabled External Interrupt 0 (the ISP button on RDB1768).
				LPC_PINCON->PINSEL4 &= ~(0x3 << 20); // limpa os 2 bits
				LPC_PINCON->PINSEL4 |= (0x01<<20);   // escreve os 2 bits
				NVIC_EnableIRQ(EINT0_IRQn);  
				break;
	}

}

void EINT3_IRQHandler (void)
{
		// Clear interrupt
	LPC_SC->EXTINT = EINT3_CLR;
	(*funcao[3])();
}

void EINT2_IRQHandler (void)
{
		// Clear interrupt
	LPC_SC->EXTINT = EINT2_CLR;
	(*funcao[2])();
}
void EINT1_IRQHandler (void)
{
		// Clear interrupt
	LPC_SC->EXTINT = EINT1_CLR;
	(*funcao[1])();
}
void EINT0_IRQHandler (void)
{
		// Clear interrupt
	LPC_SC->EXTINT = EINT0_CLR;
	(*funcao[0])();
}

