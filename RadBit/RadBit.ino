
#include "RadBit.h"
#include "RadSensor.h"
#include "RadData.h"
#include "RadFram.h"
#include "stu_scheduler.h"
#include <Time.h>
#include "RTClib.h"
#include <Wire.h>
#include "Adafruit_FRAM_SPI.h"

RTC_DS3231 rtc;

time_t countInterval = 60000;


RadFram radFram;

Task countTask(&countFunc, countInterval, 0);


RadItr radHead(sizeof(raw_data_t), 65536);
RadItr radTail(sizeof(raw_data_t), 65536);

volatile bool radFlag = 0;
volatile bool timerFlag = 0;
volatile int radCnt = 0;
const int intPin = 0;

Tevisio_RD3024 radSensor(0);

void blinkBean() {
  Bean.setLed(0, 250, 0);
  delay(500);
  Bean.setLed(0, 0, 0);
  delay(500);
}

void blinkBeanRed() {
  Bean.setLed(250, 0, 0);
  delay(75);
  Bean.setLed(0, 0, 0);
  delay(75);
}

void startRadSensor() {
  attachInterrupt(radSensor.getPin(), radEvent, FALLING);

}

inline void stopRadSensor() {
  detachInterrupt(0);

}

void begin() {
  //Serial
  Serial.begin(57600);
  //Bean.enablePairingPin(true);
  //Bean.setPairingPin(440916);
  blinkBean();
  blinkBean();
  blinkBean();
  delay(2000);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1) {
      blinkBeanRed();
      delay(1000);
    }
  }

  if (rtc.lostPower()) {
    Serial.println(F("RTC lost power, lets set the time!"));
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    //rtc.adjust(DateTime(2017, 2, 14, 17, 1, 0));
  }


  radFram.begin();

  for (int i = 1; i <= 5; i++) {
    Bean.setScratchNumber(i, 0);
  }


  //Radiation Sensor


  //TODO FRAM

  //LED


  //TODO Power Manegment

  scheduler.addEvent(&countTask);
}


void setup() {

  begin();
  delay(5000);
  blinkBean();


  countTask.enable();
  startRadSensor();
}


void loop() {
  if (radFlag) {
    Bean.setScratchNumber(3, radCnt);
    blinkBeanRed();
    radFlag = 0;
  }
  dumpDataFunc();
  scheduler.run();
  delay(5);

}


void radEvent() {
  stopRadSensor();
  radFlag = 1;
  radCnt++;
  startRadSensor();

}


void countFunc() {
  countTask.disable();
  stopRadSensor();
  DateTime temp = rtc.now();

  raw_data_t d;

  d.eventTime = temp.unixtime();
  d.count = radCnt;
  Bean.setScratchNumber(3, d.count);
  Bean.setScratchNumber(4, d.eventTime);
  setNextData(&d);

  radCnt = 0;

  startRadSensor();
  countTask.enable();
}

void dumpDataFunc(){
    if(Bean.readScratchNumber(5) == 0xAA){

        while(Bean.readScratchNumber(5) == 0xAA && radHead.getPos() < radTail.getPos()){
            raw_data_t t;
            getNextData(&t);

            Bean.setScratchNumber(1, t.count);
            Bean.setScratchNumber(2, t.eventTime);
            Bean.setScratchNumber(3, radHead.getPos());
            Bean.setScratchNumber(5, 0);

            const long timeOut = 1000;
            long startTime = millis();
            while(Bean.readScratchNumber(5) == 0 ){
                if(millis() - startTime > timeOut){
                    return;
                }
            }
        }
    }

}


int getNextData(raw_data_t* d){
    int dSz = sizeof(raw_data_t);
    uint8_t tempData[dSz];

    radFram.getData(tempData, dSz, radHead.getPos());

    memmove(d, tempData, dSz);
    return radHead.increment();

}

int setNextData(raw_data_t* d){
    int dSz = sizeof(raw_data_t);
    uint8_t tempData[dSz];
    memmove(tempData, d, dSz);
    Serial.print(F("Tail Position: "));
    Serial.println(radTail.getPos());
    radFram.writeData(tempData, dSz, radTail.getPos());

    return radTail.increment();


}
