/*
 * Co2Sensor.h
 *
 *  Created on: 28.04.2022
 *      Author: maxlell
 */

#ifndef CO2SENSOR_CO2SENSOR_H_
#define CO2SENSOR_CO2SENSOR_H_

#include "main.h"
#include "scd4x_i2c.h"
#include "sensirion_common.h"
#include "sensirion_i2c_hal.h"

void Co2Sensor_Init();
bool Co2Sensor_IsNewSampleReady();
uint16_t Co2Sensor_GetSample();


#endif /* CO2SENSOR_CO2SENSOR_H_ */
