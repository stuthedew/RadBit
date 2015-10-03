//#include "RadBean_config.h"
#include "RadBean.h"
#include <Time.h>
#include <Wire.h>
#include "Adafruit_FRAM_I2C.h"

uint8_t radPin = 3;
volatile boolean countFlag = 0;

radConfig_t testUnion;

void setup(){
    //delay(10000);
    Serial.begin(115200);
    Serial.println(F("Serial Test"));
    RadBean.begin();
    RadBean.configDump();
    pinMode(radPin, INPUT);
    for(int i = 0; i < 4; i++){
        blink();

    }

}


void loop(){

    if(digitalRead(radPin)){
        blink();

    }

}

void blink(){
    Bean.setLedRed(100);
    delayMicroseconds(100);
    Bean.setLedRed(0);
    delayMicroseconds(100);
}

void setCountFlag(){
    Bean.detachChangeInterrupt(radPin);
    if(digitalRead(radPin)){
        countFlag = 1;

    }
    Bean.attachChangeInterrupt(radPin, setCountFlag);
}
