
#include "RadBit.h"
#include "RadSensor.h"

#include "RadStorage.h"
#include "RadFram.h"
#include "ComProtocol.h"
#include <Time.h>
#include "RTClib.h"
#include <Wire.h>
#include "Adafruit_FRAM_SPI.h"

RTC_Millis rtc;

time_t countInterval = 60000;  // Sums counts per 60 seconds

RadFram rFram(framSzBytes);

RadStorage radStorage(&rFram);

Task countTask(&countFunc, countInterval, 0);


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


inline void startRadSensor() {
  attachInterrupt(radSensor.getPin(), radEvent, FALLING);
}

inline void stopRadSensor() {
  detachInterrupt(0);
}

void begin() {
  blinkBean();
  blinkBean();
  blinkBean();
  delay(2000);


  radStorage.begin();

  for (int i = 1; i <= 5; i++) {
    Bean.setScratchNumber(i, 0);
  }
  //Software RTC
  rtc.begin(DateTime(F(__DATE__), F(__TIME__))); //set compile time. Will set real time and adjust data on first computer sync
  Bean.setScratchNumber(5, clockNotSetCodeBC);


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
  int statusReg = Bean.readScratchNumber(5);

  switch(statusReg){
    case setTimeCodeCB:
      adjustBeanTime();
      break;

    case requestDataCodeCB:
    dumpData();
    break;
 }

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

  data_t d;

  d.eventTime = temp.unixtime();
  d.count = radCnt;
  Bean.setScratchNumber(3, d.count);
  Bean.setScratchNumber(4, d.eventTime);

  radStorage.storeData(&d);

  radCnt = 0;

  startRadSensor();
  countTask.enable();
  if(radStorage.getSync()){
      Bean.setScratchNumber(5, moreDataCodeBC);
  }
}


void dumpData(){
    data_t d;

    while (radStorage.getData(&d) > 0) {

      Bean.setScratchNumber(1, d.count);
      Bean.setScratchNumber(2, d.eventTime);

      Serial.print(d.eventTime-60);
      Serial.print(F(","));
      Serial.println(d.count);
  }

  radStorage.setHeadPos(0); //Reset Head position for debugging
  
  Bean.setScratchNumber(5, endOfDataCodeBC);
 }


void adjustBeanTime(){
    Bean.setScratchNumber(5, updatingDataBC);

    DateTime beanTime = rtc.now();
    uint32_t actualT = Bean.readScratchNumber(4);

    DateTime realTime(actualT);
    rtc.adjust(realTime);
    radStorage.adjustTime(beanTime.unixtime(), realTime.unixtime());

    Bean.setScratchNumber(5, moreDataCodeBC);
}
