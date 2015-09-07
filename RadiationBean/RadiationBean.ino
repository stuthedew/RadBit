#include "RadFram.h"
#include "RadBean_config.h"
#include "radBean.h"
#include <Time.h>
#include <Wire.h>
#include "Adafruit_FRAM_I2C.h"


//using namespace rad;

radData_t testUnion;

void setup(){
    delay(10000);
    Serial.begin(115200);
    Serial.println(F("Serial Test"));
    RadBean.begin();

}


void loop(){


}
