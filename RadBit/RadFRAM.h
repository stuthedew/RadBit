#pragma once
#include "RadBit.h"
#include "RadStorage.h"
#include <Wire.h>
#include "Adafruit_FRAM_SPI.h"



class RadFram : public RadStorageDevice{

public:
    RadFram(uint32_t framSize);

    void
        begin( ) ;

    bool
        getBytes( uint8_t*, uint8_t sz, uint32_t loc),
        putBytes( uint8_t*, uint8_t sz, uint32_t loc),
        writeBytes( uint8_t*, uint8_t sz, uint32_t loc );


private:
    Adafruit_FRAM_SPI _fram;

    void
        _write8(uint8_t c, uint32_t loc);

    bool
        _overflow(uint32_t pos);

    const uint32_t
        _size;

};
