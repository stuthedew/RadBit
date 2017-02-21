#pragma once
#include "RadBit.h"
#include <Time.h>
//#include "RadFram.h"
//#include <Wire.h>
//#include "Adafruit_FRAM_SPI.h"

typedef struct __attribute__((__packed__)){     //packed for straight forward storage on FRAM
    long eventTime;
    int16_t count;

    }data_t;


typedef struct __attribute__((__packed__)){     //packed for straight forward storage on FRAM
    uint32_t headVal;
    uint32_t tailVal;
    uint32_t timeAdjustVal; // which data still need to be adjusted for time.

}settings_t;



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
        setClockSynced( void ),
        setClockSynced( bool sync ),
        setHeadPos(uint32_t pos),
        adjustTime(time_t beanTime, time_t actualTime);

    storage_write_ret_code_e
        storeData(data_t* d, RadItr* itr),
        storeData(data_t* d);

    int32_t
        peekData(data_t* d),
        peekData(data_t* d, RadItr* itr),
        getData(data_t* d),
        dataRemaining(RadItr* itr) ,
        dataRemaining() ;

    bool
        getClockSynced() const;


    private:
        RadStorageDevice*
            _storage;

        RadItr
            _head,
            _tail,
            _timeAdjust;

        bool
            _syncStatus;

/*
        void
            _setHeadPos(uint32_t pos);
            */
};



//};
