#pragma once

#include <Time.h>
#include "Arduino.h"
#define MAX_PACKET_SIZE 32
#define CONFIG_HEADER_SIZE 32
#define PACKET_HEADER_SIZE 2
#define PACKET_BODY_SIZE MAX_PACKET_SIZE - PACKET_HEADER_SIZE


//namespace rad{

typedef struct  header_t{
  uint8_t type ; //reserved
  uint8_t length ;

}header_t;


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

typedef union  {

  struct{
    header_t    header ;
    time_t      refTime;
    uint8_t     datapoint[ PACKET_BODY_SIZE ] ;

  }message;

uint8_t packet[ MAX_PACKET_SIZE ] ;

}radData_t;

//};
