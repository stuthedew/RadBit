
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
time_t advertisingInterval = 30000;

volatile unsigned long pulseStart;
const unsigned long pulseWidth = 50;


RadFram rFram(framSzBytes);

RadStorage radStorage(&rFram);

Task countTask(&countFunc, countInterval, 0);
Task advertisingTask(&enableAdvertising, advertisingInterval, 1);


volatile bool radFlag = 0;
volatile bool timerFlag = 0;
volatile int radCnt = 0;
const int intPin = 0;

Tevisio_RD3024 radSensor(intPin);

void enableAdvertising(){
    Bean.enableAdvertising(true, 10000);
}

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

void powerSettings(){
    Bean.setAccelerometerPowerMode(0x80); //Suspend mode (~0.5uA)

    // Disable the ADC by setting the ADEN bit (bit 7)  of the
    // ADCSRA register to zero.
    ADCSRA = ADCSRA & B01111111;

    // Disable the analog comparator by setting the ACD bit
    // (bit 7) of the ACSR register to one.
    ACSR = B10000000;

}


inline void startRadSensor() {
  attachInterrupt(radSensor.getPin(), radEventRise, RISING);
}

inline void stopRadSensor() {
  detachInterrupt(0);
}

void begin() {
  blinkBean();
  blinkBean();
  blinkBean();
  Bean.enableAdvertising(true);



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
  scheduler.addEvent(&advertisingTask);
  Bean.enableAdvertising(true);
  delay(5000);

}


void setup() {

  begin();

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


void radEventRise() {
  stopRadSensor();
  pulseStart = micros();
  attachInterrupt(radSensor.getPin(), radEventFall, FALLING);


}

void radEventFall() {
  stopRadSensor();
  if(micros() - pulseStart >= pulseWidth){
      radFlag = 1;
      radCnt++;
  }
  attachInterrupt(radSensor.getPin(), radEventRise, RISING);


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
