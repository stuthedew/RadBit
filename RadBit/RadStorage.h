#pragma once
#include "RadBit.h"
//#include "RadFram.h"
//#include <Wire.h>
//#include "Adafruit_FRAM_SPI.h"

typedef struct __attribute__((__packed__)){     //packed for straight forward storage on FRAM
    long eventTime;
    int16_t count;

    }data_t;

const uint8_t headAddr = 0;
const uint8_t tailAddr =  headAddr + sizeof(uint32_t);


typedef enum{
    SUCCESS,
    OVERFLOW

}storage_write_ret_code_e;

typedef enum{
    MORE_DATA,
    END_OF_DATA

}storage_read_ret_code_e;



class RadStorageDevice{

public:
    //RadStorageDevice(uint32_t framSize);

    virtual void
        begin( ) =0;

    virtual bool
        getBytes( uint8_t*, uint8_t sz, uint32_t loc)=0,
        putBytes( uint8_t*, uint8_t sz, uint32_t loc)=0,
        writeBytes( uint8_t*, uint8_t sz, uint32_t loc )=0;


/*private:


    void
        _write8(uint8_t c, uint32_t loc);

    bool
        _overflow(uint32_t pos);

    const uint32_t
        _size;
*/
};

class RadItr{

    public:
        RadItr(uint8_t dataSz, uint32_t startPos),
        RadItr(uint8_t dataSz);

        uint32_t
            increment(),
            decrement(),
            getRawPos() const,
            getPos() const;

        void
          setPos( uint32_t pos),
          setRawPos(uint32_t pos);

    private:
        const uint8_t
            _dataSz;

        uint32_t
            _position;


};

class RadStorage{
    public:
        RadStorage(RadStorageDevice* d);

    void
        begin(),
        setSync( void ),
        setSync( bool sync );

    storage_write_ret_code_e
        storeData(data_t* d);

    int32_t
        peekData(data_t* d),
        getData(data_t* d);

    bool
        getSync() const;


    private:
        RadStorageDevice*
            _storage;

        RadItr
            _head,
            _tail;

        bool
            _syncStatus;

        void
            _setHeadPos(uint32_t pos);
};



//};
