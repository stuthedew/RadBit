
#include "RadBit.h"
#include "RadLED.h"
#include <Time.h>
#include <Wire.h>
#include "Adafruit_FRAM_I2C.h"

RadLED led;


void begin(){
    //Serial
    Serial.begin(SERIAL_BAUD_RATE);

    //TODO Bluetooth

    //TODO RTC

    //TODO Radiation Sensor

    //TODO FRAM

    //LED
    led.begin();

    //TODO Power Manegment

}


void setup(){

begin();

}


void loop(){
    led.blink(1000, 3);
    delay(4000);

}
