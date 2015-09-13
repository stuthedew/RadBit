#include "RadFram.h"



RadFram::RadFram():_fram(){

}

void RadFram::begin( void ){
    _fram.begin();
}

uint16_t RadFram::version( void ){
    Serial.print(F("Fram version: "));
    uint16_t tempVal = _fram.read8(1);
    tempVal |= _fram.read8(2) << 1;
    return(tempVal);

}


void RadFram::memcpy_F(uint8_t* b, uint16_t index, uint16_t size){
    for(uint16_t i = 0; i < size; i++){
        *b = _fram.read8(i + index);
        b++;
    }
}

void RadFram::memset_F(uint8_t* b, uint16_t index, uint16_t size){
    for(uint16_t i = 0; i < size; i++){
        _fram.write8(i + index, *b);
        b++;
    }
}

void RadFram::getFramConfig( radConfig_t* c ){
    memcpy_F(c->packet, 0, sizeof(radConfig_t));
}

void RadFram::setFramConfig( radConfig_t* c ){
    memset_F(c->packet, 0, sizeof(radConfig_t));
}
