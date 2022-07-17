CC=avr-gcc

FLAGS=   -O2 -Wall -mcall-prologues -mmcu=atmega328p -DF_CPU=16000000UL

LINKER= avr-objcopy

UPLOADER=avrdude

testa_nrf24.hex: finalR.o finalT.o
	$(LINKER)  -O ihex finalR.o testaR_nrf24.hex
	$(LINKER)  -O ihex finalT.o testaT_nrf24.hex

finalR.o:   nrf24.o testaR_nrf24.o spi.o   digital.o uart.o
	$(CC) $(FLAGS)  nrf24.o testaR_nrf24.o spi.o   digital.o uart.o -o finalR.o

finalT.o:   nrf24.o testaT_nrf24.o spi.o   digital.o uart.o
	$(CC) $(FLAGS)  nrf24.o testaT_nrf24.o spi.o   digital.o uart.o -o finalT.o

testaT_nrf24.o: testaT_nrf24.c delay.h  nrf24.o   uart.o spi.o digital.o
	$(CC) $(FLAGS) testaT_nrf24.c -c

testaR_nrf24.o: testaR_nrf24.c delay.h  nrf24.o   uart.o spi.o digital.o
	$(CC) $(FLAGS) testaR_nrf24.c -c


spi.o:	spi.c delay.h digital.o spi.h
	$(CC) $(FLAGS) spi.c -c

nrf24.o:	 spi.o delay.h  nrf24.c nrf24.h
	$(CC) $(FLAGS) nrf24.c -c

uart.o: uart.c
	$(CC) $(FLAGS) uart.c -c

digital.o: digital.c digital.h
	$(CC) $(FLAGS) digital.c -c

clean:
	rm -f *.o *.hex *~

upload_2009:
	${UPLOADER} -F -V -v -c arduino -p ATMEGA328P -P /dev/ttyUSB0 -b 57600  -U flash:w:final.hex

uploadr:
	${UPLOADER} -F -V -v -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200  -U flash:w:testaR_nrf24.hex

uploadt:
	${UPLOADER} -F -V -v -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200  -U flash:w:testaT_nrf24.hex
