/*
 * StatusLed.c
 *
 *  Created on: 28.04.2022
 *      Author: maxlell
 */

#include "StatusLed.h"
#include "delay.h"

/* -------------------------------------------------- */
/* ------------------- Status LED ------------------- */
/* -------------------------------------------------- */

void StatusLed_Disable()
{
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
}
void StatusLed_Toggle()
{
	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
}

void StatusLed_ShowHeartbeat(uint8_t u8Factor)
{
	for (uint8_t i = 0; i < u8Factor; i++)
	{
		StatusLed_Toggle();
		Delay_ms(1);
		StatusLed_Toggle();
		Delay_ms(1);
		Delay_ms(30);
	}
	StatusLed_Disable();
}
