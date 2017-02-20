#ifndef __COMPROTOCOL_H__
#define __COMPROTOCOL_H__

//Bean --> Computer
const uint8_t timeOutCodeBC = 0xBD;
const uint8_t moreDataCodeBC = 0xBC;
const uint8_t endOfDataCodeBC = 0xBE;
const uint8_t clockNotSetCodeBC = 0xBD;

//Computer --> Bean
const uint8_t requestDataCodeCB = 0xCA;
const uint8_t setTimeCodeCB = 0xCB;



#endif
