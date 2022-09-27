/*
 * delay.c
 *
 *  Created on: Apr 8, 2022
 *      Author: maxlell
 */

#include "delay.h"

static TIM_HandleTypeDef *tim;

void Delay_SetTimer(TIM_HandleTypeDef *htim)
{
	tim = htim;
	HAL_TIM_Base_Start(htim);
}

void Delay_us(uint16_t us)
{
	__HAL_TIM_SET_COUNTER(tim,0);  // set the counter value a 0
	while (__HAL_TIM_GET_COUNTER(tim) < us);  // wait for the counter to reach the us input in the parameter
}
void Delay_ms(uint32_t ms)
{
	HAL_Delay(ms);
}


