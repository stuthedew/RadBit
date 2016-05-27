
#ifndef __RADFRAM_H
#define __RADFRAM_H
#include "RadBit.h"


class RadFRAM:public EventStorage {
public:
	RadFRAM(int ledPin=13);


	void begin( void );
	void storeEvent( sensor_event_t e );

private:
	const int _ledPin;
	bool _ledState;

};

#endif
