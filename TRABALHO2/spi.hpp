
#include <inttypes.h>
#include "digital.h"

#ifndef __SPI__
#define __SPI__

#define MISO PIN1_24
#define MOSI PIN1_23
#define SCK  PIN1_26
#define CS   PIN1_25

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
