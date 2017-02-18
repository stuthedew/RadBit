
#include "RadBit.h"
#include "RadSensor.h"
#include "RadData.h"
#include "RadFram.h"
#include "stu_scheduler.h"
#include <Time.h>
#include "RTClib.h"
#include <Wire.h>
#include "Adafruit_FRAM_SPI.h"

RTC_Millis rtc;

//Bean --> Computer
const uint8_t timeOutCodeBC = 0xDD;
const uint8_t moreDataCodeBC = 0xCC;
const uint8_t endOfDataCodeBC = 0xEE;
const uint8_t clockNotSetCodeBC = 0xBD;

//Computer --> Bean
const uint8_t requestDataCodeCB = 0xBB;


time_t countInterval = 60000;
//time_t countInterval = 10000;


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

/*
  if (rtc.lostPower()) {
    Serial.println(F("RTC lost power, lets set the time!"));
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.begin(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    //rtc.adjust(DateTime(2017, 2, 14, 17, 1, 0));
  }
*/

  radFram.begin();

  for (int i = 1; i <= 5; i++) {
    Bean.setScratchNumber(i, 0);
  }
  //Software RTC
  rtc.begin(DateTime(F(__DATE__), F(__TIME__))); //set compile time. Will set real time and adjust data on first computer sync
  Bean.setScratchNumber(5, 0xBD);


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
    case 0xBD:
    
    case 0xBB;
    dumpData();
 } 
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

RadItr tempHead(sizeof(raw_data_t), 65536);
void dumpData(){
    int startPos = 0;
    
    RadItr tempTail(sizeof(raw_data_t), 65536);
    tempHead.setPos(radHead.getPos());
    tempTail.setPos(radTail.getPos());
    int i = startPos;
    while (tempHead.getPos() < tempTail.getPos()) {
      raw_data_t t;
      getNextData(&t);

      Bean.setScratchNumber(1, t.count);
      Bean.setScratchNumber(2, t.eventTime);
      Serial.print(i++);
      Serial.print(F(","));
      Serial.print(t.eventTime-60);
      Serial.print(F(","));
      Serial.println(t.count);
      tempHead.increment();
      //Bean.setScratchNumber(5, 0xBB);
      
      const long timeOut = 30000;
      long startTime = millis();
      while (Bean.readScratchNumber(5) == moreDataCodeBC ) {
        if (millis() - startTime > timeOut) {
          Bean.setScratchNumber(5, timeOutCode);
          return;
        }
      } 
    }
    Bean.setScratchNumber(5, endOfDataCode);
  }


int getNextData(raw_data_t* d){
    int dSz = sizeof(raw_data_t);
    uint8_t tempData[dSz];

    radFram.getData(tempData, dSz, tempHead.getPos()*dSz);

    memmove(d, tempData, dSz);
    return tempHead.increment();

}

int setNextData(raw_data_t* d){
    int dSz = sizeof(raw_data_t);
    uint8_t tempData[dSz];
    memmove(tempData, d, dSz);
    //Serial.print(F("Tail Position: "));
    //Serial.println(radTail.getPos());
    radFram.writeData(tempData, dSz, radTail.getPos()*dSz);

    return radTail.increment();


}
