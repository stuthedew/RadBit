//#include "RadBean_config.h"
#include "RadBean.h"
#include <Time.h>
#include <Wire.h>
#include "Adafruit_FRAM_I2C.h"



radConfig_t testUnion;

void setup(){
    //delay(10000);
    Serial.begin(115200);
    Serial.println(F("Serial Test"));
    RadBean.begin();
    RadBean.configDump();
    
}


void loop(){


}
