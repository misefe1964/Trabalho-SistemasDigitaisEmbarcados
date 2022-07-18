#ifndef _INTERRUPCAO_EXTERNA_
#define _INTERRUPCAO_EXTERNA_

#include "LPC17xx.h"
#include "inttypes.h"
#define PIN_2_10_INT_EXT_0 0
#define PIN_2_11_INT_EXT_1 1
#define PIN_2_12_INT_EXT_2 2
#define PIN_2_13_INT_EXT_3 3

#define BORDA_DESCIDA 0
#define BORDA_SUBIDA  1

void configura_interrupcao_externa(void (*f)(void) , uint8_t numero, uint8_t borda);
void desabilita_interrupcao_externa (void);
void habilita_interrupcao_externa (void);


#endif
