/*
 * delay.h
 *
 *  Created on: Apr 8, 2022
 *      Author: maxlell
 */

#ifndef DELAY_DELAY_H_
#define DELAY_DELAY_H_

#include "tim.h"

void Delay_SetTimer();

void Delay_us(uint16_t us);

void Delay_ms(uint32_t ms);

#endif /* DELAY_DELAY_H_ */
