
#include "digital.h"
#include <stdint.h>
#include <stdio.h>

#include "spi.hpp"
#include "delay.hpp"

void SPI::init ()
{
	miso = MISO;
	mosi = MOSI;
	sck  = SCK;
	cs   = CS;
	pinMode(cs,   OUTPUT);
	pinMode(mosi, OUTPUT);
	pinMode(sck,  OUTPUT);
	pinMode(miso, INPUT);
	digitalWrite(mosi, LOW);
	digitalWrite(sck,  LOW);
	digitalWrite(cs,   HIGH);
}

void SPI::start (void)
{
	digitalWrite(cs, LOW);
}

void SPI::stop (void)
{
	digitalWrite(cs, HIGH);
}

uint8_t SPI::write (uint8_t valor)
{
	uint8_t bit, recebido = 0, bit_resposta;
	for (int x=0;x<8;x++)
	{
		bit = (valor>>(7-x)) & 1;
		digitalWrite(mosi, bit);
		digitalWrite(sck, HIGH);
		bit_resposta  = digitalRead(miso);
		delay_us(50);
		digitalWrite(sck, LOW);
		//bit_resposta  = ead(miso);

		recebido = (recebido << 1) | bit_resposta;
		delay_us(50);
	}
	return recebido;
}

SPI spi;
