#ifndef _NRF24_
#define _NRF24_
#include <inttypes.h>


#define BLOQUEANTE 0
#define NBLOQUEANTE 1

// COMANDOS
#define FLUSH_TX     0xE1
#define FLUSH_RX      0xE2
#define W_TX_PAYLOAD 0xA0
#define R_RX_PAYLOAD 0x61

// definicoes dos comandos
#define R_REGISTER 0x00
#define W_REGISTER 0x20
#define EN_AA      0x01
#define SETUP_AW   0x03
#define RF_CH      0x05
#define SETUP_RETR  0x04
#define RF_SETUP   0x06
#define RX_ADDR_P0 0x0A
#define TX_ADDR    0x10
#define RX_PW_P0   0x11
#define EN_RXADDR  0x02

void    nrf24_init (void);
uint8_t le_registrador (uint8_t reg);
void    nrf24_le_registrador (uint8_t reg, uint8_t qtd, uint8_t vet[]);
void    nrf24_escreve_registrador (uint8_t reg, uint8_t qtd, uint8_t vet[]);
void    nrf24_transmite(uint8_t buffer[]);
uint8_t nrf24_recebe(uint8_t buffer[]);

// definicoes dos registradores
#define STATUS 7
#define CONFIG 0

#endif
