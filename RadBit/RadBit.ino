
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

Tevisio_RD3024 radSensor(intPin);

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
    writeScratch(i, 0);
  }
  //Software RTC
  rtc.begin(DateTime(F(__DATE__), F(__TIME__))); //set compile time. Will set real time and adjust data on first computer sync
  writeScratch(scratchRegister, clockNotSetCodeBC);


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
      stopRadSensor();
      delay(40);
    writeScratch(1, radCnt);
    startRadSensor();
    blinkBeanRed();
    radFlag = 0;
  }
  int statusReg = Bean.readScratchNumber(scratchRegister);

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
  writeScratch(1, d.count);
  writeScratch(2, d.eventTime);

  if(radStorage.storeData(&d) == OVERFLOW){
      writeScratch(scratchRegister, StorageOverFlowBC);
  }

  radCnt = 0;

  startRadSensor();
  countTask.enable();

  if(radStorage.getClockSynced()){
      writeScratch(scratchRegister, dataAvailableBC);
  }

}


void dumpData(){
    data_t d;
    writeScratch(3, radStorage.dataRemaining());

    while (radStorage.dataRemaining() > 0) {
        radStorage.getData(&d);
      //writeScratch(1, d.count);
      //writeScratch(2, d.eventTime);

      Serial.print(d.eventTime-60);
      Serial.print(F(","));
      Serial.println(d.count);
  }

  //radStorage.setHeadPos(0); //Reset Head position for debugging

  writeScratch(scratchRegister, endOfDataCodeBC);
 }


void adjustBeanTime(){
    writeScratch(scratchRegister, updatingDataBC);

    DateTime beanTime = rtc.now();
    uint32_t actualT = Bean.readScratchNumber(4);

    DateTime realTime(actualT);
    rtc.adjust(realTime);
    radStorage.adjustTime(beanTime.unixtime(), realTime.unixtime());

    if(radStorage.dataRemaining() > 0){
        writeScratch(scratchRegister, dataAvailableBC);
    }
    else{
        writeScratch(scratchRegister, endOfDataCodeBC);
}
}

void writeScratch(int sNum, int val){
    stopRadSensor();
    Bean.setScratchNumber(sNum, val);
    delay(25);
    startRadSensor();

}
