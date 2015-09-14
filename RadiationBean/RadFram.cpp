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

inline void RadFram::put8( uint16_t index, uint8_t value ){
    if(value != _fram.read8(index)){
        _fram.write8(index, value);
    }
}

void RadFram::memcpy_F(uint8_t* b, uint16_t FRAM_index, uint16_t size){
    for(uint16_t i = 0; i < size; i++){
        *b = _fram.read8(i + FRAM_index);
        b++;
    }
}

void RadFram::memset_F(uint8_t* b, uint16_t FRAM_index, uint16_t size){
    for(uint16_t i = 0; i < size; i++){
        put8(i + FRAM_index, *b);
        b++;
    }
}

uint16_t RadFram::memcmp_F(uint8_t* b, uint16_t FRAM_index, uint16_t size){
    uint16_t delta = 0;
    for(uint16_t i = 0; i < size; i++){
        if(*b++ != _fram.read8(i + FRAM_index)){
            delta++;
        }
    }
    return delta;
}

void RadFram::getFramConfig( radConfig_t* c ){
    memcpy_F(c->packet, 0, sizeof(radConfig_t));
}

void RadFram::setFramConfig( radConfig_t* c ){
    memset_F(c->packet, 0, sizeof(radConfig_t));
}
