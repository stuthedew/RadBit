#include "RadBean.h"


RadBeanClass RadBean;

static const radConfig_t _flashConfig[] PROGMEM ={ HEADER_OFFSET, RAD_VERSION, HEAD, TAIL };

RadBeanClass::RadBeanClass():_fram(){
/*
    _default.version = RAD_VERSION;
    _default.H_Offset = HEADER_OFFSET;
    _default.minAddr = MIN_ADDR;
    _default.maxAddr = MAX_ADDR;
*/
}

void RadBeanClass::begin( void ){
    _fram.begin();

    //Data packet Test
    randomSeed(6);
    radData_t testData;

    testData.header.refTime=1442175281;
    testData.header.jmptime = ONE_SEC;
    for(int i = 0; i< PACKET_BODY_SIZE; i++){
    testData.data[i] = random() % 255;
}
for(int i = 0; i< MAX_PACKET_SIZE; i++){
    Serial.print(testData.packet[i], HEX);
    Serial.print(F(" "));
}
Serial.println();
//Data packet test

/*****************************Initialize configuration**********************/

/*
//  Compare Firmware versions in PROGREM and FRAM.
    1. If PROGMEM vesion == FRAM then no firmware updates and use config from FRAM
    2. Else PROGMEM version != FRAM then inititialize FRAM with default config

*/

    memcpy_P(&_config, &_flashConfig, sizeof(radConfig_t)); //Get PROGMEM Firmware version

    Serial.print(F("Flash Version: "));
    Serial.println(_config.version);

//  Compare Firmware versions in PROGREM and FRAM.
    if(_config.version == _fram.version()){ //  no firmware updates
        _fram.getFramConfig(&_config);      // use FRAM config
        Serial.println(F("Get Fram"));
    }
    else{
        Serial.println(F("Set Fram"));  //  PROGMEM version != FRAM version (Firmware update)
        _fram.setFramConfig(&_config);  //  re-initilize FRAM with default config
    }
    radConfig_t* ptr1 = &_config;
    uint8_t delta = _fram.memcmp_F(ptr1->packet, 0, 20);
    /*
    Serial.print(F("Fram and PROGMEM comparison: "));
    Serial.println(delta);
*/

}

void RadBeanClass::configDump( void ){
    radConfig_t tempConfig;
    _fram.getFramConfig(&tempConfig);
    Serial.print(F("Fram Version: "));
    Serial.println(tempConfig.version);
    Serial.print(F("Fram Header Offset: "));
    Serial.println(tempConfig.H_Offset);
    Serial.print(F("Fram Head: "));
    Serial.println(tempConfig.head);
    Serial.print(F("Fram Tail: "));
    Serial.println(tempConfig.tail);
/*
    Serial.print(F("\nFram Version: "));
    Serial.println(_config.version);
    Serial.print(F("Fram Header Offset: "));
    Serial.println(_config.H_Offset);
    Serial.print(F("Fram Min Address: "));
    Serial.println(_config.minAddr);
    Serial.print(F("Fram Max Address: "));
    Serial.println(_config.maxAddr);
*/
}
