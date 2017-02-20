#pragma once

#include "Arduino.h"

//Bean --> Computer
const uint8_t timeOutCodeBC = 0xBA;
const uint8_t moreDataCodeBC = 0xBB;
const uint8_t endOfDataCodeBC = 0xBC;
const uint8_t clockNotSetCodeBC = 0xBD;
const uint8_t updatingDataBC = 0xBE;

//Computer --> Bean
const uint8_t requestDataCodeCB = 0xCA;
const uint8_t setTimeCodeCB = 0xCB;
