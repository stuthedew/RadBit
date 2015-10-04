#include "RadBean.h"
#include <Time.h>
#include <Wire.h>
#include "Adafruit_FRAM_I2C.h"

const uint8_t radPin = 3;

RadBeanClass Rad(radPin);

void setup() {
    Rad.begin();
}

void loop() {
    

}
