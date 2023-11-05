/*
 * PowerLed.c
 *
 *  Created on: 28.04.2022
 *      Author: maxlell
 */

#include "PowerLed.h"
#include "delay.h"

#define PWM_ARRAY_SIZE 80
uint32_t ua32PwmArray[PWM_ARRAY_SIZE] = {0};
uint8_t bPulseLedFlag = 0;

void PowerLed_Enable()
{
	/* Start PWM Signal Generation */
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
}
void PowerLed_Disable()
{
	/* Stop PWM Signal Generation */
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_4);
}

void PowerLed_Init()
{
	PowerLed_Enable();

	/* Wait 1 Second: Make it visually seperable that the system starts up */
	Delay_ms(1000);

	/* Change the Dutycycle to indicate Start Up */
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 60);

	/* Start TIM ISR */
	HAL_TIM_Base_Start_IT(&htim16);

	/* Create the PWM Array for the Pulsed LED (Bad Air Quality) */
	PowerLed_CreatePwmArray();

	/* Disable functionality of the TIM ISR */
	bPulseLedFlag = 0;
	return;
}
void PowerLed_Level3AirQuality()
{
	/*
	 * Blinking of the Signal LED:
	 * This pattern is chosen, because it is a pattern,
	 * that grabs attention in a negative way - it gets
	 * on your nerves
	 */
	PowerLed_Enable();

	/* Set Up Timers correctly */
	__HAL_TIM_SET_PRESCALER(&htim1, 32000 - 1);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 20);

	/* Disable functionality of the TIM ISR */
	bPulseLedFlag = 0;
	return;
}
void PowerLed_Level2AirQuality()
{
	/*
	 * Pulse LED slowly:
	 * This pattern is chosen, because it is a
	 * lightning pattern that only indicates, but does not
	 * force you to act on it.
	 */

	PowerLed_Enable();

	/* Signal LED stays constantly on at 80% max Brightness */
	__HAL_TIM_SET_PRESCALER(&htim1, 3200 - 1);

	/* Enable functionality of the TIM ISR */
	bPulseLedFlag = 1;

	return;
}
void PowerLed_Level1AirQuality()
{
	/* Disable functionality of the TIM ISR */
	bPulseLedFlag = 0;

	/*
	 * Signal LED stays constantly on at 10% max Brightness
	 * This is for indicating purposes, that the system works
	 * and is running - 2kHz
	 * Max Switching Frequency of the PAM2804 -> 1kHz
	 */
	PowerLed_Enable();

	__HAL_TIM_SET_PRESCALER(&htim1, 3200 - 1);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 10);
	return;
}

void PowerLed_Level0AirQuality()
{
	/*
	 * Signal LED is switched off completely to increase
	 * the LEDs lifetime. This functionality will especially active
	 * during the times, where the window is open in either way.
	 * There is no need for HALCO to be active if the CO2 Levels
	 * are that low.
	 */
	PowerLed_Disable();
}

uint32_t PowerLed_ClipSignalAccordingToBoundaries(uint32_t number)
{
	/*
	 * Make sure that the LED PWM Dutycycles stay within bounds
	 * The PAM2804 LED Driver Chip can only take max 2ms switching
	 * times. Therefore the boundaries are clipped
	 */
	uint32_t lower_boundary = 10;
	uint32_t upper_boundary = 90;

	if (number <= lower_boundary)
	{
		number = lower_boundary;
	}
	if (number >= upper_boundary)
	{
		number = upper_boundary;
	}

	return number;
}

void PowerLed_CreatePwmArray()
{

	/*
	 * Signal shall go off completely:
	 * Overwrite lowest value (10% Brightness)
	 * with 0% Brightness
	 */
	// ua32PwmArray[0] = 0;

	uint32_t modif = 2;
	uint32_t u32PwmArrayHalfSize = PWM_ARRAY_SIZE / 2;
	for (uint32_t i = 0; i < PWM_ARRAY_SIZE; i++)
	{
		ua32PwmArray[i] = PowerLed_ClipSignalAccordingToBoundaries(ua32PwmArray[i]);
		/*
		 * First Half of the array -> INcrement values,
		 * but also check on boundaries
		 */
		if (i < u32PwmArrayHalfSize)
		{
			ua32PwmArray[i] = ua32PwmArray[i - 1] + modif;

			/* Run Boundary Check */
			ua32PwmArray[i] = PowerLed_ClipSignalAccordingToBoundaries(ua32PwmArray[i]);
		}
		else if (i == u32PwmArrayHalfSize)
		{
			/*
			 * Signal LED shall go on completely:
			 * overwrite brightest Pulse (90% brigthness) with 100% Brightness
			 */
			ua32PwmArray[u32PwmArrayHalfSize] = 100;
			ua32PwmArray[i] = PowerLed_ClipSignalAccordingToBoundaries(ua32PwmArray[i]);
		}
		/*
		 * First Half of the array -> DEcrement values,
		 * but also check on boundaries
		 */
		else
		{
			ua32PwmArray[i] = ua32PwmArray[i - 1] - modif;

			/* Run Boundary Check */
			ua32PwmArray[i] = PowerLed_ClipSignalAccordingToBoundaries(ua32PwmArray[i]);
		}
	}
	return;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	/* Only pulse the LED, when the flag is set */
	if (bPulseLedFlag == 1)
	{
		/*
		 * Have an incrementor run through the previously
		 * prepared array, in which the PWM duty-cycles are
		 * created.
		 */
		static uint32_t ctr = 0;
		uint32_t tmp = 0;

		ctr++;
		if (ctr >= PWM_ARRAY_SIZE)
		{
			ctr = 0;
		}
		/* Assign Dutycycles to the Timer */
		tmp = ua32PwmArray[ctr];
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, tmp);
	}
	return;
}
