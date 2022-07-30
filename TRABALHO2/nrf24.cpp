#include "digital.h"
#include "nrf24.hpp"
#include "spi.hpp"
#include "delay.hpp"
#include <stdio.h>
void modoRX(void);
void modoTX(void);
void nrf24_flush_TX (void);
void reset (void);
void limpa_FIFO(void);
//void nrf24_le_registrador (uint8_t reg, uint8_t qtd, uint8_t vet[]);

uint8_t pino_CE;

void CE_HIGH(void)
{
	digitalWrite(pino_CE, HIGH);
}
void CE_LOW(void)
{
	digitalWrite(pino_CE, LOW);
}
void power_DOWN (void)
{
	uint8_t reg_config;

	reg_config = le_registrador(CONFIG);

	reg_config = reg_config & 0xFD;
	nrf24_escreve_registrador(CONFIG,1,(uint8_t *)&reg_config);
}
void power_UP (void)
{
	uint8_t reg_config;

	reg_config = le_registrador(CONFIG);
	reg_config = reg_config | 0x02;
	nrf24_escreve_registrador(CONFIG,1,(uint8_t *)&reg_config);
}
void nrf24_init (void)
{
	uint8_t parametros[5];

	// MISO, uint8_t MOSI, uint8_t SCK, uint8_t CS
	_delay_ms(100);
	spi.init();
	pino_CE = PIN3_25;
	pinMode(pino_CE, OUTPUT);
	CE_LOW();
	power_DOWN();
	_delay_ms(300);
	power_UP();
	_delay_ms(3000);

	limpa_FIFO();


	parametros[0] = 0;
    nrf24_escreve_registrador (DYNPD, 1, parametros);

    		parametros[0] = 1;
        nrf24_escreve_registrador (EN_RX_ADDR, 1, parametros);


	parametros[0] = 0x01;
    nrf24_escreve_registrador (EN_RXADDR, 1, parametros);

	parametros[0] = 0;
    nrf24_escreve_registrador (FEATURE, 1, parametros);

	parametros[0] = 0x00;
    nrf24_escreve_registrador (EN_AA, 1, parametros);

	parametros[0] = 0x01;
    nrf24_escreve_registrador (SETUP_AW, 1, parametros);



	parametros[0] = 0x6E;
    nrf24_escreve_registrador (RF_CH, 1, parametros);


	parametros[0]=0;
	nrf24_escreve_registrador (SETUP_RETR, 1, parametros);

	parametros[0] = 0x07;
    nrf24_escreve_registrador (RF_SETUP, 1, parametros);

	parametros[0] = 1;
	parametros[1] = 1;
	parametros[2] = 1;

    nrf24_escreve_registrador (RX_ADDR_P0, 3, parametros);


	nrf24_escreve_registrador (TX_ADDR, 3, parametros);

	parametros[0] = TAMANHO_MSG;
	nrf24_escreve_registrador (RX_PW_P0, 1, parametros);

	parametros[0]=0x0E;
	nrf24_escreve_registrador (STATUS,1,parametros);

	parametros[0] = 0x77;
    nrf24_escreve_registrador (CONFIG, 1, parametros);



	parametros[0]=0x11;
	nrf24_escreve_registrador (FIFO_STATUS, 1, parametros);

		limpa_FIFO();

}

void nrf24_transmite(uint8_t buffer[])
{
	uint8_t x, status;

   	modoTX();
	spi.start();
		spi.write(FLUSH_TX);
	spi.stop();

	uint8_t crc = 0xff;

	for (x=0;x<TAMANHO_MSG-1;x++)	crc=crc+buffer[x];
	buffer[TAMANHO_MSG-1]=crc;
	spi.start();
		spi.write(W_TX_PAYLOAD);
		for (x=0;x<TAMANHO_MSG;x++)	spi.write(buffer[x]);
	spi.stop();


	CE_HIGH();
	_delay_us(20);
	CE_LOW();
	_delay_us(20);
	while  (  (le_registrador(STATUS) & (1<<5)) ==0);
	status = le_registrador(STATUS);
	status = (status | (1<<5));
	nrf24_escreve_registrador(STATUS,1,(uint8_t *)&status);
	//_delay_ms(10);
	modoRX();






}

void reset (void)
{
	_delay_us(10);
	spi.start();
	_delay_us(10);
	spi.write(W_REGISTER|STATUS);
	_delay_us(10);
	spi.write(0x70);
	_delay_us(10);
	spi.stop();
}
void modoRX(void)
{
	uint8_t buffer[10];
	buffer[0]=0x72;
	nrf24_escreve_registrador(CONFIG, 1, (uint8_t *)&buffer);

}

void modoTX(void)
{
uint8_t buffer[10];
	buffer[0]=0x7a;
	nrf24_escreve_registrador(CONFIG, 1, (uint8_t *)&buffer);
	digitalWrite(PIN1_22, LOW);
}

void limpa_FIFO(void)
{
	uint8_t origem;

	nrf24_le_registrador(CONFIG, 1, &origem);

	_delay_us(10);


	modoTX();
	spi.start();
		spi.write(FLUSH_TX);
	spi.stop();

    modoRX();
	spi.start();
		spi.write(FLUSH_RX);
	spi.stop();

	nrf24_escreve_registrador (CONFIG,1,(uint8_t *)&origem);
}
void nrf24_recebe(uint8_t buffer[])
{
	uint8_t x,valor;

	while (1){
		CE_HIGH();

		while  (  (le_registrador(STATUS) & (1<<6)) ==0);
		CE_LOW();
		spi.start();
			spi.write(R_RX_PAYLOAD);
			for (x=0;x<TAMANHO_MSG;x++) buffer[x] = spi.write(0xff);
		spi.stop();
		spi.start();
			spi.write(FLUSH_RX);
		spi.stop();

		// limpa o flag de recepcao de pacote
		valor=le_registrador(STATUS);
		valor = valor | (1<<6);
		nrf24_escreve_registrador (STATUS, 1, &valor);
			CE_HIGH();
		uint8_t crc = 0xff;
		for (x=0;x<TAMANHO_MSG-1;x++)	crc=crc+buffer[x];
		if (crc==buffer[TAMANHO_MSG-1]) return;

	}

}
void nrf24_le_registrador (uint8_t reg, uint8_t qtd, uint8_t vet[])
{
	uint8_t x;
	spi.start();
		spi.write(R_REGISTER|reg);
		for (x=0;x<qtd;x++)  vet[x] = spi.write(0x00);
	spi.stop();
}
void nrf24_flush_TX (void)
{
	spi.start();
		spi.write(FLUSH_TX);
	spi.stop();
}
void nrf24_escreve_registrador (uint8_t reg, uint8_t qtd, uint8_t vet[])
{
	uint8_t x;

	spi.start();
		spi.write(W_REGISTER|reg);
		for (x=0;x<qtd;x++)  spi.write(vet[x]);
	spi.stop();
}
uint8_t le_registrador (uint8_t reg)
{
	uint8_t x;
	spi.start();
		spi.write(R_REGISTER|reg);
		x = spi.write(0x00);
	spi.stop();
	return x;
}
