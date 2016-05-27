
#ifndef __RADLED_H__
#define __RADLED_H__

#include "Arduino.h"

/////////////////
// DEFINITIONS //
/////////////////


/** LED Definitions **/
const unsigned int LED_PIN = 13;

/** Serial Definitions **/
const unsigned long SERIAL_BAUD_RATE = 115200;

typedef struct {
	uint32_t epoch;
	uint16_t value;
	uint16_t period;
}sensor_event_t;

class EventStorage {
public:

    virtual void begin()=0;
    virtual void storeEvent( sensor_event_t e ) = 0;

};



#endif
