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
        memcpy_F(uint8_t *b, uint16_t index, uint16_t size),
        memset_F(uint8_t *b, uint16_t index, uint16_t size);

    uint16_t
        version( void );

    void
        getFramConfig(radConfig_t*);

    void
        setFramConfig(radConfig_t*);

private:

    Adafruit_FRAM_I2C
        _fram;
};
