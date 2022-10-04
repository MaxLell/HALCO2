/*
 * PowerLed.h
 *
 *  Created on: 28.04.2022
 *      Author: maxlell
 */

#ifndef POWERLED_POWERLED_H_
#define POWERLED_POWERLED_H_

#include "main.h"

void PowerLed_Init();

void PowerLed_Enable();

void PowerLed_Disable();

void PowerLed_BadAirQuality();

void PowerLed_MediumAirQuality();

void PowerLed_GoodAirQuality();

void PowerLed_PerfectAirQuality();

void PowerLed_CreatePwmArray();

uint32_t PowerLed_ClipSignalAccordingToBoundaries(uint32_t number);

#endif /* POWERLED_POWERLED_H_ */
