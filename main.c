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

int main() {
    SystemInit();
    periodica_init();
    delay_init();
    seg_init();
    mcp23S17_init();


    mcp23S17_conf_pin(7, OUTPUT);
    mcp23S17_conf_pin(6, OUTPUT);
    mcp23S17_conf_pin(5, OUTPUT);
    mcp23S17_conf_pin(4, OUTPUT);

    mcp23S17_write_pin(7, 1, WRITE);
    mcp23S17_write_pin(6, 1, WRITE);
    mcp23S17_write_pin(5, 1, WRITE);
    mcp23S17_write_pin(4, 1, WRITE);

    uint8_t tmp = mcp23S17_write_pin(6, 0, READ);
    seg_apresenta(tmp);

    while(1) {}
}

