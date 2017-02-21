#pragma once
#include "RadBit.h"
#include <Wire.h>
#include "Adafruit_FRAM_SPI.h"

//namespace rad{

class RadFram{

public:
    RadFram();

    void
        begin( void ) ,
        getData( uint8_t*, uint8_t sz, int loc),
        writeData( uint8_t*, uint8_t sz, int loc );




private:
    Adafruit_FRAM_SPI _fram;

};

class RadItr{

    public:
        RadItr(uint8_t dataSz, long storageSz);

        int
            increment(),
            decrement(),
            getPos() const;

        void
            setPos( long pos);

    private:
        const uint8_t
            _dataSz;

        const long
            _storageSz;
        long
            _position;


};

 extern RadFram radFram;

//};
