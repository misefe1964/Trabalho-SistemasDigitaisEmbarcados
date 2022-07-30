#ifndef __LCD__
#define __LCD__
#include <stdint.h>
#define RS PIN2_12
#define E  PIN2_13
#define D0 PIN0_04
#define D1 PIN0_05
#define D2 PIN0_06
#define D3 PIN0_07
#define D4 PIN0_08
#define D5 PIN0_09
#define D6 PIN0_10
#define D7 PIN0_11
void lcd_init (void);
void lcd_msg(char *s);

#define TAMANHO_MSG 32

#endif
