/*
 * app.c
 *
 *  Created on: Apr 7, 2022
 *      Author: maxlell
 */

#include "main.h"

#include "StatusLed.h"
#include "Co2Sensor.h"
#include "WatchDog.h"
#include "PowerLed.h"

#include "delay.h"

void Fan_Init();

static uint32_t u32GoodAirQualityThreshold = 800;
static uint32_t u32BadAirQualityThreshold = 1200;

typedef enum
{
	GOOD_AIR,
	MEDIUM_AIR,
	BAD_AIR
} AirQuality_e;

/**
 * Make sure to first execute the G031_BoardBringUp Project
 * Otherwise the Microcontroller will enable the FAN, which is
 * connectected to the Boot Pin. Therefore the Microcontroller
 * will restart itself.
 */

void app_main(void)
{
	/* ################## */
	/* ###### Init ###### */
	/* ################## */

	/* Status LED Indicate a Reboot */
	StatusLed_ShowHeartbeat(RESTART_HEARTBEAT);

	/* Power LED */
	PowerLed_Init();

	/* Wait 1 sec */
	Delay_ms(1000);

	/* Set Initial Air Quality */
	AirQuality_e eAirQuality = GOOD_AIR;

	/* Co2Sensor */
	Co2Sensor_Init();

	/* Wait 50ms */
	Delay_ms(50);

	/* Fan Init */
	Fan_Init();

	/* ################## */
	/* ###### Loop ###### */
	/* ################## */

	while (1)
	{
		/* Check for a new Measurement Sample being ready */
		bool bIsNewSampleReady = Co2Sensor_IsNewSampleReady();
		if (bIsNewSampleReady)
		{
			/* Indicate with the Status LED, that a Measurement was taken */
			StatusLed_ShowHeartbeat(REGULAR_HEARTBEAT);

			/* Get the Sample */
			uint16_t u16Co2Reading = Co2Sensor_GetSample();

			/* Decide on the Air Quality */
			/* Good Air */
			if (u16Co2Reading <= u32GoodAirQualityThreshold)
			{
				eAirQuality = GOOD_AIR;
			}
			/* Medium Air Quality */
			else if ((u16Co2Reading > u32GoodAirQualityThreshold) &&
					 (u16Co2Reading < u32BadAirQualityThreshold))
			{
				eAirQuality = MEDIUM_AIR;
			}
			/* Just the worst Air Quality */
			else
			{
				eAirQuality = BAD_AIR;
			}

			/* Switch Outputs according to Air Quality */
			switch(eAirQuality)
			{
			case GOOD_AIR:
				/* Outputs for Good Air Quality */
				PowerLed_GoodAirQuality();
				break;

			case MEDIUM_AIR:
				/* Outputs for Medium Air Quality */
				PowerLed_MediumAirQuality();
				break;

			case BAD_AIR:
				/* Outputs for Bad Air Quality */
				PowerLed_BadAirQuality();
				break;

			default:
				/*
				 * This Point shall be never reached
				 * Get into an infinite loop and wait for
				 * the Watchdog to restart the system
				 */
				while (1);

				break;
			}
			/*
			 * Feed the Watchdog, but only
			 * if a CO2 Data Sample is taken,
			 * otherwise the System will restart
			 * after around 30 Seconds
			 */
			Watchdog_Feed();
		}
		/* Indikate Heartbeat with the LED that the System is still active */
		StatusLed_ShowHeartbeat(REGULAR_HEARTBEAT);

		/* Wait for 2sec, before polling again on the Sensor */
		Delay_ms(2000);
	}
}

void Fan_Init()
{
	/* Enable PWM Signal @50% Dutycycle */
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
}




