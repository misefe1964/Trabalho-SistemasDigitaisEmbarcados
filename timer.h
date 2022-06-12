#ifndef _TIMER_
#define _TIMER_
#include "LPC17xx.h"

void timer_init(void (*f)(void));
void desabilita_int(void);
void habilita_int(void);

#endif

