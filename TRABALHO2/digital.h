#ifndef _DIGITAL_
#define _DIGITAL_

#include <inttypes.h>
#include <avr/io.h>

#define HIGH 1U
#define LOW 0U

#define INPUT 0
#define OUTPUT 1

#define PIN_0 0
#define PIN_1 1
#define PIN_2 2
#define PIN_3 3
#define PIN_4 4
#define PIN_5 5
#define PIN_6 6
#define PIN_7 7
#define PIN_8 8
#define PIN_9 9
#define PIN_10 10
#define PIN_11 11
#define PIN_12 12
#define PIN_13 13
#define PIN_14 14 // usados pelo cristal
#define PIN_15 15 // usados pelo cristal
#define PIN_16 16 // C0
#define PIN_17 17 // C1
#define PIN_18 18 // C2
#define PIN_19 19 // C3
#define PIN_20 20 // C4
#define PIN_21 21 // C5
#define PIN_22 22 // usado pelo RESET

#define A0 PIN_16
#define A1 PIN_17
#define A2 PIN_18
#define A3 PIN_19
#define A4 PIN_20
#define A5 PIN_21
#define A6 PIN_22 // usado pelo RESET

void digitalWrite(uint8_t pino, uint8_t valor);
unsigned char digitalRead (int pino);
void pinMode (int8_t pino, int8_t valor);

#endif
