

#include "rad_fram.h"

//namespace rad{

RadFram::RadFram():_fram(){

}

void RadFram::begin( void ){
    _fram.begin();

}

void RadFram::getPacket( radConfig_t* c){
    for(uint16_t i = 0; i < CONFIG_HEADER_SIZE; i++){
        c->packet[i] = _fram.read8(i);
    }
}

void RadFram::getPacket( radData_t* d){

}

void RadFram::writePacket( radConfig_t* c){
    for(uint16_t i = 0; i < CONFIG_HEADER_SIZE; i++){
        _fram.write8(i, c->packet[i]);
    }
}

void RadFram::writePacket( radData_t* d){

}



//};
