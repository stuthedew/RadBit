
#ifndef __RADBIT_H__
#define __RADBIT_H__
#include "Arduino.h"
#include "stu_scheduler.h"
#include <TimeLib.h>

#include "Arduino.h"

/////////////////
// DEFINITIONS //
/////////////////

//----FRAM------//
const unsigned long framSzBytes = 65536;


/** SPI PINS **/
const int clkPin = 9;
const int misoPin = 8;
const int mosiPin = 7;
const int csPin = 6;


const int scratchRegister = 5;


/** TIME OFFSET **/
//Seconds from UNIX epoch to Sept 17, 2016. Added to datapoint time value to convert back.



/** Serial Definitions **/

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





class RadBit{
public:

    RadBit();

    void
        begin(),
        sleep();

private:
    int16_t _radCounter;

};


#endif
