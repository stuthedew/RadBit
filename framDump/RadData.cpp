#include "RadData.h"

void RadStorage::constructor(){
};


uint16_t RadStorage::_getCRC(raw_data_t *d){
	uint8_t bArry[sizeof(raw_data_t)];
	memmove(bArry, d, sizeof(raw_data_t));
	return _CRC16.kermit(bArry, sizeof(raw_data_t));
}

proc_data_t* RadStorage::proccessData(raw_data_t *d){
	proc_data_t* p = new proc_data_t;
	memmove(p->data, d, sizeof(raw_data_t));
	p->CRC = _getCRC(p->data);
    return p;
}

LocalStorage::LocalStorage() : _tempList(){

}

bool LocalStorage::push(raw_data_t *d){
    //TODO Fix
	return _tempList.unshift(proccessData(d));
}

proc_data_t* LocalStorage::pop(){
	return _tempList.pop();
}
proc_data_t* LocalStorage::peek(){
	return _tempList.get(0);
}

int LocalStorage::size(){
	return _tempList.size();
}
void LocalStorage::destroy(){
	for(int i =0; i < _tempList.size(); i++) {
		proc_data_t *p = _tempList.pop();
		delete(p);
	}
}

uint16_t LocalStorage::getCRC(raw_data_t *d){
	return _getCRC(d);
}
