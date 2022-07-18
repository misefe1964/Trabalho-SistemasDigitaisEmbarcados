#include "digital.h"
#include "nrf24.h"
#include "spi.h"
#include "delay.h"
#include "interrupcao_externa.h"

#define USA_INTERRUPCAO


void nrf24_flush_TX (void);
void reset (void);
void limpa_FIFO(void);
void nrf24_le_registrador (uint8_t reg, uint8_t qtd, uint8_t vet[]);
void MEU_TRATADOR_INT_EXT (void);
uint8_t pino_CE;

uint8_t MSG_RECEBIDA[20];
uint8_t nova_msg=0;


void nrf24_init (void)
{
	uint8_t parametros[5];

	// configura os pinos que serao usados para o CSN, MISO, MOSI, SCK
	spi_configura (PIN1_26, PIN1_25, PIN1_24, PIN1_23);
	pino_CE = PIN_1_22;
	delay_ms(500);
	reset();
	limpa_FIFO();
	parametros[0] = 0x01;
    nrf24_escreve_registrador (EN_RXADDR, 1, parametros);

	
    
	parametros[0] = 0x00;
    nrf24_escreve_registrador (EN_AA, 1, parametros);

	parametros[0] = 0x01;
    nrf24_escreve_registrador (SETUP_AW, 1, parametros);
	
	

	parametros[0] = 0x00;
    nrf24_escreve_registrador (RF_CH, 1, parametros);


	parametros[0]=0;
	nrf24_escreve_registrador (SETUP_RETR, 1, parametros);

	parametros[0] = 0x26;
    nrf24_escreve_registrador (RF_SETUP, 1, parametros);

	parametros[0] = 0x20;
	parametros[1] = 0x20;
	parametros[2] = 0x20;
	
	nrf24_escreve_registrador (RX_ADDR_P0, 3, parametros);
	parametros[0] = 0x10;
	parametros[1] = 0x10;
	parametros[2] = 0x10;
	nrf24_escreve_registrador (TX_ADDR, 3, parametros);

	parametros[0] = 0x08;
	nrf24_escreve_registrador (RX_PW_P0, 1, parametros);

	parametros[0]=0x0E;
	nrf24_escreve_registrador (STATUS,1,parametros);

	digitalWrite(pino_CE, HIGH);
   
#ifdef USA_INTERRUPCAO
	parametros[0] = 0x3b;
    nrf24_escreve_registrador (CONFIG, 1, parametros);
    configura_interrupcao_externa(MEU_TRATADOR_INT_EXT, PIN_2_13_INT_EXT_3, BORDA_DESCIDA);   
	habilita_interrupcao_externa();
#else
	parametros[0] = 0x7b;
    nrf24_escreve_registrador (CONFIG, 1, parametros);
#endif
}

void nrf24_transmite(uint8_t buffer[])
{
	uint8_t x, valor;

	digitalWrite(pino_CE, LOW);

	//configura como transmissor
	valor = 0x7A;
    nrf24_escreve_registrador (CONFIG, 1, &valor);
	


    nrf24_flush_TX();

	spi_habilita();
		spi_write(W_TX_PAYLOAD);
		for (x=0;x<8;x++)	spi_write(buffer[x]);
	spi_desabilita();

	digitalWrite(pino_CE, HIGH);
	delay_us(10);
	digitalWrite(pino_CE, LOW);
	

	//delay_ms(1000);
	while  (  (le_registrador(STATUS) & (1<<5)) ==0);
	valor=le_registrador(STATUS);
	valor = valor | (1<<5);
	nrf24_escreve_registrador (STATUS, 1, &valor);

	// configura como receptor
	valor = 0x7b;
    nrf24_escreve_registrador (CONFIG, 1, &valor);

}

void MEU_delay(void)
{
	volatile long x, y;
	volatile double s;
	for (x=0;x<10000;x++)
	{
		for (y=0;y<10;y++);
		{
			s = x+y*2;
		}
	}
}
void reset (void)
{
	digitalWrite(pino_CE, LOW);
	MEU_delay();
	spi_habilita();
	MEU_delay();
	spi_write(W_REGISTER|STATUS);
	MEU_delay();
	spi_write(0x70);
	MEU_delay();
	spi_desabilita();
	digitalWrite(pino_CE, HIGH);
}
void modo_TX(void)
{
	uint8_t reg_config;

	// le o valor corrente do registrador CONFIG
	 nrf24_le_registrador(CONFIG, 1, &reg_config);
	reg_config = (   (reg_config | (1<<1) )    & 0xFE);
	nrf24_escreve_registrador(CONFIG,1, (uint8_t *)&reg_config);
MEU_delay();
	MEU_delay();
	MEU_delay();
}

void modo_RX(void)
{
	uint8_t reg_config;

	// le o valor corrente do registrador CONFIG
	nrf24_le_registrador(CONFIG, 1, &reg_config);
	reg_config = reg_config | 3;
	nrf24_escreve_registrador(CONFIG,1, (uint8_t *)&reg_config);

	MEU_delay();
	MEU_delay();
	MEU_delay();
	
}

void limpa_FIFO(void)
{
	uint8_t origem;
	
	nrf24_le_registrador(CONFIG, 1, &origem);
	
	MEU_delay();
	modo_RX();
	spi_habilita();
		spi_write(FLUSH_RX);
	spi_desabilita();

	modo_TX();
	spi_habilita();
		spi_write(FLUSH_TX);
	spi_desabilita();

	nrf24_escreve_registrador (CONFIG,1,(uint8_t *)&origem);
}


#ifdef USA_INTERRUPCAO
void MEU_TRATADOR_INT_EXT (void)
{
	uint8_t x,valor;

	printf("Esta no tratador\n");
	spi_habilita();
		spi_write(R_RX_PAYLOAD);
		for (x=0;x<8;x++) MSG_RECEBIDA[x] = spi_write(0x00);
		nova_msg=1;	
	spi_desabilita();
	

    valor=0x70;
	nrf24_escreve_registrador (STATUS,1,(uint8_t *)&valor);
	printf("Fim tratador\n");
	
	limpa_FIFO();
	reset();

	
}
uint8_t nrf24_recebe(uint8_t buffer[])
{
	uint8_t x;

	desabilita_interrupcao_externa();
	if (nova_msg)
	{
		for (x=0;x<8;x++) buffer[x]=MSG_RECEBIDA[x];
		nova_msg=0;
		x=1;
		
	}
	else x=0;
	habilita_interrupcao_externa();
	return x;
   	
}
#else



uint8_t nrf24_recebe(uint8_t buffer[])
{
	uint8_t x,valor;

	digitalWrite(pino_CE, HIGH);

	while  (  (le_registrador(STATUS) & (1<<6)) ==0);
	
	spi_habilita();
		spi_write(R_RX_PAYLOAD);
		for (x=0;x<8;x++) buffer[x] = spi_write(0x00);	
	spi_desabilita();
	
	// limpa o flag de recepcao de pacote
	valor=le_registrador(STATUS);
	valor = valor | (1<<6);
	nrf24_escreve_registrador (STATUS, 1, &valor);

	return 1;				
}
#endif

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



