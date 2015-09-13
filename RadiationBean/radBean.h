#pragma once
#include "Arduino.h"
#include "RadBean_config.h"
#include "RadFram.h"

//const PROGMEM radConfig_t _defaultConfig[];

//class RadBeanClass:public BeanClass{
class RadBeanClass{
public:
  RadBeanClass();

  void
    begin( void ),
    configDump( void ) ;


private:

    radConfig_t _config;


RadFram
    _fram;

};

extern RadBeanClass RadBean;
