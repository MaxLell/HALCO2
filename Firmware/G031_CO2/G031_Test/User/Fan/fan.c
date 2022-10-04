/*
 * Fan.c
 *
 *  Created on: 04.10.2022
 *      Author: maxlell
 */

#include "main.h"
#include "tim.h"

void Fan_enable()
{
	/* Enable PWM Signal @25% Dutycycle */
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
}

void Fan_disable()
{
	/* Enable PWM Signal @25% Dutycycle */
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
}
