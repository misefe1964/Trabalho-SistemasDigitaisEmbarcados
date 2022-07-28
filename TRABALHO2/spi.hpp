
#include <inttypes.h>
#include "digital.h"

#ifndef __SPI__
#define __SPI__

#define MISO PIN1_00
#define MOSI PIN4_29
#define SCK  PIN4_28
#define CS   PIN3_26

class SPI {

	private:
		uint8_t cs, miso, mosi, sck;
		void delay (void);

	public:
		void     init (void);
		uint8_t  write (uint8_t valor);
		void     start (void);
		void     stop (void);

};

extern SPI spi;



#endif
