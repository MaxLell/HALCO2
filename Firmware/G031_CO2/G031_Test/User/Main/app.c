/*
 * app.c
 *
 *  Created on: Apr 7, 2022
 *      Author: maxlell
 */

#include "app.h"
#include "main.h"
#include "StatusLed.h"
#include "Co2Sensor.h"
#include "WatchDog.h"
#include "PowerLed.h"
#include "fan.h"
#include "delay.h"
#include "AirQuality.h"

void SetOutputsAccordingToAirQuality(AirQuality_e);
void app_init(void);

/**
 * Make sure to first execute the G031_BoardBringUp Project
 * Otherwise the Microcontroller will enable the FAN, which is
 * connectected to the Boot Pin. Therefore the Microcontroller
 * will restart itself.
 */

void SetOutputsAccordingToAirQuality(AirQuality_e eAirQuality)
{
    /* Switch Outputs according to Air Quality */
    switch (eAirQuality)
    {
    case PERFECT_AIR:
        /* Outputs for Perfect Air Quality */
        PowerLed_PerfectAirQuality();
        Fan_disable();
        break;

    case GOOD_AIR:
        /* Outputs for Good Air Quality */
        PowerLed_GoodAirQuality();
        Fan_enable();
        break;

    case MEDIUM_AIR:
        /* Outputs for Medium Air Quality */
        PowerLed_MediumAirQuality();
        Fan_enable();
        break;

    case BAD_AIR:
        /* Outputs for Bad Air Quality */
        PowerLed_BadAirQuality();
        Fan_enable();
        break;

    default:
        /*
         * This Point shall be never reached
         * Get into an infinite loop and wait for
         * the Watchdog to restart the system
         */
        while (1)
            ;

        break;
    }
}

void app_main(void)
{
	app_init();
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

			// Calculate the average Value over 5 Samples
			uint16_t u16AveragedCo2Reading = AirQuality_getAverageOverFiveSamples(u16Co2Reading);

			/* Interpret the sample */
			AirQuality_e eAirQuality = AirQuality_GetFromCO2(u16AveragedCo2Reading);

			/* Act on the air quality */
			SetOutputsAccordingToAirQuality(eAirQuality);

			/* Feed the Watchdog */
			Watchdog_Feed();
		}
		/* Indicate Heartbeat with the LED that the System is still active */
		StatusLed_ShowHeartbeat(REGULAR_HEARTBEAT);

		/* Wait for 2sec, before polling again on the Sensor */
		Delay_ms(2000);
	}
}

void app_init(void)
{
	/*
	 * The Init function serves 2 functions:
	 * 1. Initialize the Hardware components
	 * 2. Provide visual indicators that these hardware components actually work
	 */

	/* Status LED Indicate a Reboot */
	StatusLed_ShowHeartbeat(RESTART_HEARTBEAT);

	/* Power LED */
	PowerLed_Init();

	/* Wait 1 sec in order to have time to witness the init led flashing sequence */
	Delay_ms(1000);

	/* Init the Co2Sensor */
	Co2Sensor_Init();
	Delay_ms(50);

	/* Fan Enable */
	Fan_enable();

	/* Wait 2 sec in order to have time to witness the fan spinning */
	Delay_ms(2000);
}
