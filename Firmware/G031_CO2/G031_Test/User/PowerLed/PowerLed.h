/*
 * PowerLed.h
 *
 *  Created on: 28.04.2022
 *      Author: maxlell
 */

#ifndef POWERLED_POWERLED_H_
#define POWERLED_POWERLED_H_

#include "main.h"
#include "stdint.h"

void PowerLed_Init();

void PowerLed_Enable();

void PowerLed_Disable();

void PowerLed_Level3AirQuality();

void PowerLed_Level2AirQuality();

void PowerLed_Level1AirQuality();

void PowerLed_Level0AirQuality();

void PowerLed_CreatePwmArray();

uint32_t PowerLed_ClipSignalAccordingToBoundaries(uint32_t number);

#endif /* POWERLED_POWERLED_H_ */
