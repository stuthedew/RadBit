
#include "RadLED.h"


RadLED::RadLED(int ledPin) : _ledPin(ledPin){

}


void RadLED::begin(){
	pinMode(_ledPin, OUTPUT);
	off();

}

void RadLED::on(){
	digitalWrite(_ledPin, HIGH);
	_ledState = 1;
}

void RadLED::off(){
	digitalWrite(_ledPin, LOW);
	_ledState = 0;
}

void RadLED::setState(bool state){
	digitalWrite(_ledPin, state);
	_ledState = state;
}

void RadLED::blink(int bDelay, int qty ){
	bool oldState = _ledState;
	for(int i = 0; i < qty < 1; i++) {
		setState(!_ledState);
		delay(bDelay);
	}
}
