#pragma once

#include "RadBean_config.h"
#include <Wire.h>
#include "Adafruit_FRAM_I2C.h"

//namespace rad{

class RadFram{

public:
    RadFram();

    void
        begin( void ) ,
        getPacket( radConfig_t*),
        getPacket( radData_t* ),
        writePacket( radConfig_t*),
        writePacket( radData_t* );




private:
    Adafruit_FRAM_I2C _fram;

};


//};
