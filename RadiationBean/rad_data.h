#pragma once

#include <Time.h>

#define MAX_PACKET_SIZE 64
#define PACKET_HEADER_SIZE 2
#define PACKET_BODY_SIZE MAX_PACKET_SIZE - PACKET_HEADER_SIZE - sizeof(time_t) - sizeof(time_t)


namespace rad{
typedef jumpsize int;
typedef enum jumpSize_e{
  one_min     =    60 ,
  five_min    =   300 ,
  ten_min     =   600 ,
  fifteen_min =   900 ,
  twenty_min  =  1200 ,
  thrity_min  =  1800 ,
  sixty_min   =  3600
}jumpSize_t;

typedef union  {

  struct{
    uint8_t     header[ PACKET_HEADER_SIZE ] ;
    time_t      refTime;
    jumpSize_t  jumpInterval;
    uint8_t     datapoint[ PACKET_BODY_SIZE ] ;

  }message;

uint8_t packet[ MAX_PACKET_SIZE ] ;

}radData;

};
