#pragma once
#include "Arduino.h"
#include <Wire.h>
#include "Adafruit_FRAM_I2C.h"
#include "RadData.h"
#include "RadBean_config.h"



class RadFram{

public:
    RadFram();

    void
        begin( void ),
        getFramConfig(radConfig_t*),
        setFramConfig(radConfig_t*),
        put8(uint16_t index, uint8_t value);

    uint16_t
        version( void );

    void
        memcpy_F(uint8_t *b, uint16_t index, uint16_t size),    //Fram memcpy
        memset_F(uint8_t *b, uint16_t index, uint16_t size);    //Fram memset
    uint16_t
        memcmp_F(uint8_t *b, uint16_t index, uint16_t size);

private:

    Adafruit_FRAM_I2C
        _fram;
};
