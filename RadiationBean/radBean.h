#pragma once
#include "rad_bean_config.h"

//class RadFram;
//namespace rad{

class RadBeanClass :public BeanClass{

public:
  RadBeanClass();

  void
    begin( void ),
    configDump( void ) ;


private:
    RadFram _radFram;

    radConfig_t _config;
    radConfig_t _default;



};

extern RadBeanClass RadBean;

//};
