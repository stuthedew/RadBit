#include "RadBit.h"
#include "RadData.h"
#include "RadFram.h"

int headAddr, tailAddr;
const int dataSz = sizeof(raw_data_t);

const uint8_t timeOutCode = 0xDD;
const uint8_t moreDataCode = 0xCC;
const uint8_t endOfDataCode = 0xEE;

RadFram radFram;

RadItr radHead(sizeof(raw_data_t), 64000);
RadItr radTail(sizeof(raw_data_t), 64000);

void setup() {
  Bean.setScratchNumber(5, 0xAF);
  radFram.begin();
  delay(5000);
  Serial.println(F("Hello!"));
  

}

void loop() {
 if (Bean.readScratchNumber(5) == 0xBB) {
    dumpData();
 } 
 delay(50);
}

void dumpData(){
    int startPos = 428;
    //radHead.setPos(Bean.readScratchNumber(3));
    //radTail.setPos(Bean.readScratchNumber(4));
    radHead.setPos(startPos);
    radTail.setPos(501);
    int i = startPos;
    while (radHead.getPos() < radTail.getPos()) {
      raw_data_t t;
      getNextData(&t);

      Bean.setScratchNumber(1, t.count);
      Bean.setScratchNumber(2, t.eventTime);
      Serial.print(i++);
      Serial.print(F(","));
      Serial.print(t.eventTime-60);
      Serial.print(F(","));
      Serial.println(t.count);
      
      //Bean.setScratchNumber(5, 0xBB);
      
      const long timeOut = 30000;
      long startTime = millis();
      while (Bean.readScratchNumber(5) == moreDataCode ) {
        if (millis() - startTime > timeOut) {
          Bean.setScratchNumber(5, timeOutCode);
          return;
        }
      } 
    }
    Bean.setScratchNumber(5, endOfDataCode);
  }


  int getNextData(raw_data_t* d) {
    int dSz = sizeof(raw_data_t);
    uint8_t tempData[dSz];

    radFram.getData(tempData, dSz, radHead.getPos());

    memmove(d, tempData, dSz);
    return radHead.increment();

  }
