#pragma once

#include <Time.h>
#include "Arduino.h"
#define MAX_PACKET_SIZE 20
#define CONFIG_HEADER_SIZE 20
#define PACKET_HEADER_SIZE 5
#define PACKET_BODY_SIZE MAX_PACKET_SIZE - PACKET_HEADER_SIZE

typedef union  {

  struct{
      uint8_t
        H_Offset;

        uint16_t
            version ;

        uint32_t
            head ,
            tail ;
  };

uint8_t packet[ CONFIG_HEADER_SIZE ] ;

}radConfig_t;




typedef enum {
    ONE_SEC=0,
    THIRTY_SEC,
    ONE_MIN,
    TWO_MIN,
    FIVE_MIN,
    TEN_MIN
} timejmp_e;


typedef struct{
    time_t      refTime;
    timejmp_e   jmptime:8; //only want first byte. Can't make enum uint8_t

}dataHeader_t;

typedef union  {

  struct{
    dataHeader_t
        header;
    uint8_t
        data[ PACKET_BODY_SIZE ] ;
  };

uint8_t packet[ MAX_PACKET_SIZE ] ;

}radData_t;
