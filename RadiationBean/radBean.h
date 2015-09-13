#pragma once
#include "Arduino.h"
#include "RadBean_config.h"
#include "RadFram.h"



//class RadBeanClass:public BeanClass{  // For use with Lightblue bean
class RadBeanClass{     //  For testing with uno
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
