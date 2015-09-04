#include "radBean.h"

//namespace rad{

RadBeanClass RadBean;

RadBeanClass::RadBeanClass():_radFram(){
    _default.version = RAD_VERSION;
    _default.H_Offset = HEADER_OFFSET;
    _default.minAddr = MIN_ADDR;
    _default.maxAddr = MAX_ADDR;

}

void RadBeanClass::begin( void ){
    _radFram.begin();
    _radFram.getPacket(&_config);
    configDump();

    if(_config.version != _default.version){
        _radFram.writePacket(&_default);
        _radFram.getPacket(&_config);
        configDump();
    }
}

void RadBeanClass::configDump( void ){
    Serial.print(F("Fram Version: "));
    Serial.println(_config.version);
    Serial.print(F("Fram Header Offset: "));
    Serial.println(_config.H_Offset);
    Serial.print(F("Fram Min Address: "));
    Serial.println(_config.minAddr);
    Serial.print(F("Fram Max Address: "));
    Serial.println(_config.maxAddr);
}
//}
