#include "RadFram.h"


RadFram::RadFram(uint32_t framSize) : _size(framSize), _fram(clkPin, misoPin, mosiPin, csPin){

}

void RadFram::begin( ){
	_fram.begin();

}

bool RadFram::getBytes( uint8_t* c, uint8_t sz, uint32_t loc){
	for(uint32_t i = 0; i < sz; i++) {

		uint32_t curPos = i+loc;
		if(_overflow(curPos)) {
			return false;
		}

		c[i] = _fram.read8(curPos);
	}
	return true;
}



bool RadFram::writeBytes( uint8_t* c, uint8_t sz, uint32_t loc){
	for(uint32_t i = 0; i < sz; i++) {

		uint32_t curPos = i+loc;
		if(_overflow(curPos)) {
			return false;
		}
		_write8(c[i], curPos);
	}
	return true;
}

bool RadFram::putBytes( uint8_t* c, uint8_t sz, uint32_t loc ){
	for(uint32_t i = 0; i < sz; i++) {

		uint32_t curPos = i+loc;

		if(_overflow(curPos)) {
			return false;
		}

		if(_fram.read8(curPos) != c[i]) {
			_write8(c[i], curPos);
		}
	}
	return true;
}

bool RadFram::_overflow(uint32_t pos){
	if(pos < _size) {
		return false;
	}
	return true;
}

void RadFram::_write8(uint8_t c, uint32_t loc){
	_fram.writeEnable(true);
	_fram.write8(loc, c);
	_fram.writeEnable(false);
}
