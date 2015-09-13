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
    radConfig_t tempConfig;
    memcpy_P(&tempConfig, &_flashConfig, sizeof(radConfig_t));
    Serial.print(F("Flash Version: "));
    Serial.println(tempConfig.version);
    if(tempConfig.version == _fram.version()){
        _fram.getFramConfig(&_config);
        Serial.println(F("Get Fram"));
    }
    else{
        Serial.println(F("Set Fram"));
        memcpy(&_config, &tempConfig, sizeof(radConfig_t));
        _fram.setFramConfig(&_config);

    }
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
