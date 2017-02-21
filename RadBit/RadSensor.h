#pragma once

#include "RadBit.h"
#include "Arduino.h"

const int modelStrSize = 6;

class RadSensor {

public:

    RadSensor(int pin, float convertV):_sensePin(pin), _convertFactor(convertV){};

    float getConvertFactor() const;
    int getPin( void ) const;
    void getModelStr(char dArry[6]);


protected:
    const int
        _sensePin;

    const float
        _convertFactor;

    char _modelStr[modelStrSize];

    void _setModelStr(char tStr[6]);


};

class Tevisio_RD2014 : public RadSensor{
public:
    Tevisio_RD2014(int sensorPin);
};

class Tevisio_RD3024 : public RadSensor{
public:
    Tevisio_RD3024(int sensorPin);
};
