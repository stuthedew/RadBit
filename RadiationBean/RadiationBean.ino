#include "rad_bean_config.h"
#include <Time.h>


using namespace rad;

radData testUnion;

void setup(){
Serial.begin(57600);
Serial.println(F("Serial Test"));
testUnion.message.header.type = 22;
testUnion.message.header.length = 33;
testUnion.message.refTime = 123;
testUnion.message.jumpInterval = ONE_MIN;
for(int i = 0; i < PACKET_BODY_SIZE; i++){
  testUnion.message.datapoint[i] = i;
}
}


void loop(){
  for(int i = 0; i <PACKET_BODY_SIZE; i++ ){
    Serial.println(testUnion.message.datapoint[i]);
    delay(500);
  }
  delay(5000);

}
