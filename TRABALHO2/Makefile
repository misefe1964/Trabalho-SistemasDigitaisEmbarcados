
GCC_BIN =  /usr/bin/X11/
PROJECT = main
OBJECTS = system_LPC17xx.o startup_LPC17xx.o main.o digital.o delay.o uart.o spi.o
SYS_OBJECTS = 
INCLUDE_PATHS = -I. -I./LPC1768 
LIBRARY_PATHS = 
LIBRARIES = 
LINKER_SCRIPT = ./LPC1768/LPC1768.ld
BUILD_DIR = build/

############################################################################### 
AS      = $(GCC_BIN)arm-none-eabi-as
CC      = $(GCC_BIN)arm-none-eabi-gcc
CPP     = $(GCC_BIN)arm-none-eabi-g++
LD      = $(GCC_BIN)arm-none-eabi-gcc
OBJCOPY = $(GCC_BIN)arm-none-eabi-objcopy

CCLOCAL = gcc

CPU = -mcpu=cortex-m3 -mthumb
FLAGS = $(CPU) -c -fno-common -fmessage-length=0 -Wall -fno-exceptions -ffunction-sections -fdata-sections -g 
CC_SYMBOLS = -DTARGET_LPC1769 -DTOOLCHAIN_GCC_ARM -DNDEBUG -D__CORTEX_M3

LD_FLAGS = -mcpu=cortex-m3 -mthumb -Wl,--gc-sections,-Map=$(PROJECT).map,--cref 
LD_SYS_LIBS = -lc -lgcc -lnosys

all: $(PROJECT).bin

.c.o:
	mkdir -p $(BUILD_DIR)
	$(CC)  $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu99   $(INCLUDE_PATHS) -o $(addprefix $(BUILD_DIR), $@) $<


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

# This is needed for NXP Cortex M devices
nxpsum:
	$(CCLOCAL) nxpsum.c -std=c99 -o nxpsum

$(PROJECT).elf: $(OBJECTS) $(SYS_OBJECTS)
	$(LD) $(LD_FLAGS) -T$(LINKER_SCRIPT) $(LIBRARY_PATHS) -o $@ $(addprefix $(BUILD_DIR), $^) $(LIBRARIES) $(LD_SYS_LIBS) $(LIBRARIES) $(LD_SYS_LIBS)

$(PROJECT).bin: $(PROJECT).elf nxpsum
	$(OBJCOPY) -O binary $< $@
	# Compute nxp checksum on .bin file here
	./nxpsum $@

	
spi.o:	spi.c delay.h digital.o spi.h
	$(CC) $(FLAGS) spi.c -c

nrf24.o:	 spi.o delay.h  nrf24.c nrf24.h
	$(CC) $(FLAGS) nrf24.c -c



uart.o: uart.c uart.h
	$(CC) $(FLAGS) uart.c -c

digital.o: digital.c digital.h
	$(CC) $(FLAGS) digital.c -c

clean:
	rm -f *.o *.hex *~

install:
	 lpc21isp -control -bin main.bin /dev/ttyUSB0 115200 12000

