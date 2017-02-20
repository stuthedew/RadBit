

#include "RadStorage.h"


/************************************ Iterator ********************************/


//RadItr::RadItr(uint8_t dataSz, uint32_t startPos, uint32_t minPos, uint32_t maxPos) : _dataSz(dataSz){
RadItr::RadItr(uint8_t dataSz, uint32_t startPos) : _dataSz(dataSz){
    //TODO: Finish adding max and min positions.
	_position = startPos; //TODO: Add checking old position from FRAM


}

RadItr::RadItr(uint8_t dataSz) : _dataSz(dataSz){

	_position = 0;
}


void RadItr::setPos(uint32_t pos){
	_position = pos*_dataSz;

}

void RadItr::setRawPos(uint32_t pos){
	_position = pos;

}

uint32_t RadItr::getPos() const {

	return _position/_dataSz;
}

uint32_t RadItr::getRawPos() const {

	return _position;
}

uint32_t RadItr::increment(){
	_position += _dataSz;
	return _position;
}

uint32_t RadItr::decrement(){
	_position -= _dataSz;
	return _position;
}


/************************************ Storage ********************************/

RadStorage::RadStorage(RadStorageDevice* d): _head(sizeof(data_t)), _tail(sizeof(data_t)){
    _syncStatus = 0;
    _storage = d;
    //TODO: Add storage adjustments for head and tail data.
}

void RadStorage::begin( void ){
    _storage->begin();
}

storage_write_ret_code_e RadStorage::storeData(data_t* d){
    int dSz = sizeof(data_t);
    uint8_t tempData[dSz];
    memmove(tempData, d, dSz);

    bool storageStatus = _storage->writeBytes(tempData, dSz, _tail.getRawPos());

    if(!storageStatus){
        return OVERFLOW;
    }
    _tail.increment();
    //TODO: Check if sync bit is set and Sync tail to FRAM if so
    return SUCCESS;



}

int32_t RadStorage::getData(data_t* d){
    int32_t retVal = peekData(d);
    _head.increment();
    return retVal;

}

int32_t RadStorage::peekData(data_t* d){
    int dSz = sizeof(data_t);
    uint8_t tempData[dSz];

    _storage->getBytes(tempData, dSz, _head.getRawPos());

    memmove(d, tempData, dSz);

    //TODO: Check if sync bit is set and Sync tail to FRAM if so

    return _tail.getPos() - _head.getPos();

}

bool RadStorage::getSync() const{
    return _syncStatus;
}

void RadStorage::setSync(void){
    _syncStatus = true;
}

void RadStorage::setSync(bool sync){
    _syncStatus = sync;
}

void RadStorage::_setHeadPos(uint32_t pos){
    _head.setRawPos(pos);

    if(_tail.getRawPos() > pos){
        _tail.setRawPos(pos);
    }
}

//};
