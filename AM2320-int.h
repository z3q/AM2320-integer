#ifndef AM2320_H
#define AM2320_H

#include <Arduino.h>

#define AM2320_address (0xB8 >> 1) 

class AM2320
{
	public:
		AM2320();
		int t;
		byte h;
		byte Read(void); 
};

#endif
