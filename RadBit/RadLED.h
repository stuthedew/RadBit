
#ifndef __RADLED_H
#define __RADLED_H
#include "RadBit.h"
#include "Arduino.h"

class RadLED {
public:
RadLED(int ledPin=13);


void begin( void );
void on();
void off();
void blink(int bDelay, int qty );
void setState(bool state);

private:
const int _ledPin;
bool _ledState;

};

#endif
