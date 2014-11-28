#pragma once

#include <Time.h>

#define MAX_PACKET_SIZE 64
#define PACKET_HEADER_SIZE 2
#define PACKET_BODY_SIZE MAX_PACKET_SIZE - PACKET_HEADER_SIZE - sizeof(time_t) - sizeof(jumpSize_t)


namespace rad{

typedef enum jumpSize_e{
  ONE_MIN     =    60 ,
  FIVE_MIN    =   300 ,
  TEN_MIN     =   600 ,
  FIFTEEN_MIN =   900 ,
  TWENTY_MIN  =  1200 ,
  THIRTY_MIN  =  1800 ,
  SIXTY_MIN   =  3600
}jumpSize_t;

typedef struct  header_t{
  uint8_t type ; //reserved
  uint8_t length ;

}header_t;

typedef union  {

  struct{
    header_t    header ;
    time_t      refTime;
    jumpSize_t  jumpInterval;
    uint8_t     datapoint[ PACKET_BODY_SIZE ] ;

  }message;

uint8_t packet[ MAX_PACKET_SIZE ] ;

}radData;

};
