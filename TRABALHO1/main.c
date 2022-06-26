// TRABALHO 1 - Carlos Eduardo e Milena
// para compilar:  
//                    make
// para gravar na placa (usando o bootloader): 
//                   lpc21isp -control -bin main.bin /dev/ttyUSB0 115200 12000
//
// para gravar na placa (usando o JTAG)
//                   openocd -f lpc1768.cfg
// abrir outro shell
// telnet localhost 4444
// > reset halt
// > flash write_image erase main.bin 0x0 bin

#include "LPC17xx.h"
#include "digital.h"
#include <stdint.h>
#include "periodica.h"
#include "delay.h"
#include "uart.h"
#include "seg.h"
#include "mcp.h"

uint8_t contador;

int main() {
    SystemInit();
    periodica_init();
    delay_init();
    seg_init();
    mcp23S17_init();

    uint8_t status;
    contador = 0;

    mcp23S17_conf_pin(7, OUTPUT);
    mcp23S17_conf_pin(6, OUTPUT);
    mcp23S17_conf_pin(5, OUTPUT);
    mcp23S17_conf_pin(4, OUTPUT);
    mcp23S17_conf_pin(3, INPUT);
    mcp23S17_conf_pin(2, INPUT);
    mcp23S17_conf_pin(1, INPUT);
    mcp23S17_conf_pin(0, INPUT);

    mcp23S17_write_pin(7, 1, WRITE);
    mcp23S17_write_pin(6, 1, WRITE);
    mcp23S17_write_pin(5, 1, WRITE);
    mcp23S17_write_pin(4, 1, WRITE);

    while(1) {
        status = mcp23S17_write_pin(3, 0, READ);
        seg_apresenta(status);
        if (status == 0) {
            mcp23S17_invert_pin(contador+4);
            contador = (contador +1) % 4;
        }
        delay_ms(100);
    }
}

