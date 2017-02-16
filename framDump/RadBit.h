
#ifndef __RADBIT_H__
#define __RADBIT_H__
#include "Arduino.h"

#include <TimeLib.h>

/////////////////
// DEFINITIONS //
/////////////////

/** SPI PINS **/
const int clkPin = 9;
const int misoPin = 8;
const int mosiPin = 7;
const int csPin = 6;

/** TIME OFFSET **/
//Seconds from UNIX epoch to Sept 17, 2016. Added to datapoint time value to convert back.



/** Serial Definitions **/
const unsigned long SERIAL_BAUD_RATE = 115200;




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
