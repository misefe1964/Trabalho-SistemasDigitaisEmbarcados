#ifndef _TIMER_
#define _TIMER_
#include "LPC17xx.h"

void timer_init(void (*f)(void));

void delay_ms(uint16_t);
void delay_init(void);

void desabilita_int(void);
void habilita_int(void);
#endif
