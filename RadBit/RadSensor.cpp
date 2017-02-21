#include "RadSensor.h"

float RadSensor::getConvertFactor()const{
    return _convertFactor;
}
void RadSensor::_setModelStr(char mStr[6]){
    strncpy(_modelStr, mStr, modelStrSize);
}

int RadSensor::getPin()const{
    return _sensePin;
}

void RadSensor::getModelStr(char destAry[6]){
    strncpy(destAry, _modelStr, modelStrSize);
}


Tevisio_RD2014::Tevisio_RD2014(int readPin):RadSensor(readPin, 3.4){
    char tmpArr[] = "RD2014";
    _setModelStr(tmpArr);

}


Tevisio_RD3024::Tevisio_RD3024(int readPin):RadSensor(readPin, 5.8){
    char tmpArr[] = "RD3024";
    _setModelStr(tmpArr);

}
