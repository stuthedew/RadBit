/*
   Rad Sensor
   Copyright (c)  All right reserved.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <time.h>
#include "RadSensor.h"


voidFuncPtr RadT_callBack = NULL;

RadSensor::RadSensor()
{
	_configured = false;
}

void RadSensor::begin(bool resetTime)
{
	PM->APBAMASK.reg |= PM_APBCMASK_TC3; // turn on digital interface clock
	uint16_t tmp_reg = 0;





	PM->APBAMASK.reg |= PM_APBCMASK_TC3; // turn on digital interface clock

	CTRLA.WAVEGEN = 0;
	CTRLBSET.ONESHOT = 1;
	CTRLC.CAPTEN3 = 1;
	CTRLC.COPEN3 = 1;
	EVCTRL.TCEI = 1;



	// Setup clock GCLK2 with OSC32K divided by 32
	GCLK->GENDIV.reg = GCLK_GENDIV_ID(3);
	while (GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY)
		;
	GCLK->GENCTRL.reg = (GCLK_GENCTRL_GENEN | GCLK_GENCTRL_SRC_XOSC32K | GCLK_GENCTRL_ID(2) | GCLK_GENCTRL_DIVSEL );
	while (GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY)
		;
	GCLK->CLKCTRL.reg = (uint32_t)((GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK2 | (RTC_GCLK_ID << GCLK_CLKCTRL_ID_Pos)));
	while (GCLK->STATUS.bit.SYNCBUSY)
		;


	_configured = true;

}
