#include "digital.h"
#include "nrf24.h"
#include "spi.h"
#include "delay.h"
#include <avr/interrupt.h>

void modo_RX(void);
void modo_TX(void);
void nrf24_flush_TX (void);
void reset (void);
void limpa_FIFO(void);
void nrf24_le_registrador (uint8_t reg, uint8_t qtd, uint8_t vet[]);

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

	// configura os pinos que serao usados para o CSN, MISO, MOSI, SCK
	_delay_ms(100);
	spi_configura (10,12,11,13);
	pino_CE = 8;
	pinMode(pino_CE, OUTPUT);
	CE_LOW();
	power_DOWN();
	_delay_ms(300);
	power_UP();
	_delay_ms(3000);

	limpa_FIFO();	
	
	parametros[0] = 0x01;
    nrf24_escreve_registrador (EN_RXADDR, 1, parametros);

	
    
	parametros[0] = 0x00;
    nrf24_escreve_registrador (EN_AA, 1, parametros);

	parametros[0] = 0x01;
    nrf24_escreve_registrador (SETUP_AW, 1, parametros);
	
	

	parametros[0] = 0x01;
    nrf24_escreve_registrador (RF_CH, 1, parametros);


	parametros[0]=0;
	nrf24_escreve_registrador (SETUP_RETR, 1, parametros);

	parametros[0] = 0x27;
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

	

}

void nrf24_transmite(uint8_t buffer[])
{
	uint8_t x, status;
   
   	modo_TX();
	spi_habilita();
		spi_write(FLUSH_TX);
	spi_desabilita();

	spi_habilita();
		spi_write(W_TX_PAYLOAD);
		for (x=0;x<TAMANHO_MSG;x++)	spi_write(buffer[x]);
	spi_desabilita();
	

	CE_HIGH();
	_delay_us(20);
	CE_LOW();
	_delay_us(20);
	while  (  (le_registrador(STATUS) & (1<<5)) ==0);
	status = le_registrador(STATUS); 
	status = (status | (1<<5));
	nrf24_escreve_registrador(STATUS,1,(uint8_t *)&status);
	_delay_ms(10);
	modo_RX();
	

	



}

void reset (void)
{
	_delay_us(10);
	spi_habilita();
	_delay_us(10);
	spi_write(W_REGISTER+STATUS);
	_delay_us(10);
	spi_write(0x70);
	_delay_us(10);
	spi_desabilita();
}
void modo_TX(void)
{
	uint8_t reg_config;

	// le o valor corrente do registrador CONFIG
	nrf24_le_registrador(1,CONFIG, &reg_config);
	reg_config = (   (reg_config | _BV(PWR_UP) )    & ~_BV(PRIM_RX));
	nrf24_escreve_registrador(CONFIG,1,(uint8_t *)&reg_config);
	_delay_us(150);
}

void modo_RX(void)
{
	uint8_t reg_config;

	// le o valor corrente do registrador CONFIG
	nrf24_le_registrador(CONFIG, 1, &reg_config);
	reg_config = reg_config | 3;
	nrf24_escreve_registrador(CONFIG,1, (uint8_t *)&reg_config);

	delay_us(20);
	
}

void limpa_FIFO(void)
{
	uint8_t origem;
	
	nrf24_le_registrador(CONFIG, 1, &origem);
	
	_delay_us(10);
	

	modo_TX();
	spi_habilita();
		spi_write(FLUSH_TX);
	spi_desabilita();

    modo_RX();
	spi_habilita();
		spi_write(FLUSH_RX);
	spi_desabilita();

	nrf24_escreve_registrador (CONFIG,1,(uint8_t *)&origem);
}
void nrf24_recebe(uint8_t buffer[])
{
	uint8_t x,valor;

	CE_HIGH();

	while  (  (le_registrador(STATUS) & (1<<6)) ==0);

	spi_habilita();
		spi_write(R_RX_PAYLOAD);
		for (x=0;x<TAMANHO_MSG;x++) buffer[x] = spi_write(0xff);	
	spi_desabilita();
	spi_habilita();
		spi_write(FLUSH_RX);
	spi_desabilita();
	
	// limpa o flag de recepcao de pacote
	valor=le_registrador(STATUS);
	valor = valor | (1<<6);
	nrf24_escreve_registrador (STATUS, 1, &valor);
	
	return;				
}
void nrf24_le_registrador (uint8_t reg, uint8_t qtd, uint8_t vet[])
{
	uint8_t x;
	spi_habilita();
		spi_write(R_REGISTER|reg);
		for (x=0;x<qtd;x++)  vet[x] = spi_write(0x00);
	spi_desabilita();
}
void nrf24_flush_TX (void)
{
	spi_habilita();
		spi_write(FLUSH_TX);
	spi_desabilita();
}
void nrf24_escreve_registrador (uint8_t reg, uint8_t qtd, uint8_t vet[])
{
	uint8_t x;

	spi_habilita();
		spi_write(W_REGISTER|reg);
		for (x=0;x<qtd;x++)  spi_write(vet[x]);
	spi_desabilita();
}
uint8_t le_registrador (uint8_t reg)
{
	uint8_t x;
	spi_habilita();
		spi_write(R_REGISTER|reg);
		x = spi_write(0x00);
	spi_desabilita();
	return x;
}



