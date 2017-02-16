#ifndef __RADDATA_H__
#define __RADDATA_H__
#include "RadBit.h"
#include "Arduino.h"
#include "RTClib.h"
#include <FastCRC.h>
#include <LinkedList.h>

typedef struct __attribute__((__packed__)){
    long eventTime;
    int16_t count;

    }raw_data_t;



typedef struct __attribute__((__packed__)){
    raw_data_t
        *data;
    uint16_t
        CRC;

}proc_data_t;



class RadStorage{
public:
    void
        constructor();
    virtual bool
        push(raw_data_t *d)=0;
    virtual proc_data_t* pop()=0;
    virtual proc_data_t* peek()=0;
    virtual int
        size()=0;
protected:
    proc_data_t* proccessData(raw_data_t *d);
    uint16_t _getCRC(raw_data_t *r);

private:
    FastCRC16 _CRC16;

};


class LocalStorage : public RadStorage{
public:
    LocalStorage();
    uint16_t getCRC(raw_data_t *r);
    bool
        push(raw_data_t *d);

    proc_data_t* peek();
    proc_data_t* pop();


    int
        size();

    void
        destroy();

private:
    LinkedList<proc_data_t*> _tempList;

};
/*
class FramStorage : public RadStorage{
public:
    FramStorage();

};

*/
#endif
