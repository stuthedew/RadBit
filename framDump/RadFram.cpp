

#include "RadFram.h"

//namespace rad{

RadFram::RadFram():_fram(clkPin, misoPin, mosiPin, csPin){

}

void RadFram::begin( void ){
    _fram.begin();

}

void RadFram::getData( uint8_t* c, uint8_t sz, int loc){
    for(uint16_t i = 0; i < sz; i++){
        c[i] = _fram.read8((i+loc));
    }
}


void RadFram::writeData( uint8_t* c, uint8_t sz, int loc){
    for(uint16_t i = 0; i < sz; i++){
        _fram.writeEnable(true);
        _fram.write8(i+loc, c[i]);
        _fram.writeEnable(false);
    }
}


RadItr::RadItr(uint8_t dataSz, long storageSz):_dataSz(dataSz), _storageSz(storageSz){

    _position = 0; //TODO: Add checking old position from FRAM


}

void RadItr::setPos(long pos){
  _position = pos*_dataSz;

}

int RadItr::increment(){
    _position += _dataSz;
    _position = min(_position, _storageSz);
    return _position;
}

int RadItr::decrement(){
    _position -= _dataSz;
    _position = max(_position, 0);
    return _position;
}

int RadItr::getPos()const{

    return _position;
}



//};
