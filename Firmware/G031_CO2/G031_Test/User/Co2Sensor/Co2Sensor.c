/*
 * Co2Sensor.c
 *
 *  Created on: 28.04.2022
 *      Author: maxlell
 */

#include "Co2Sensor.h"
#include "delay.h"
#include "StatusLed.h"

/* -------------------------------------------------- */
/* ------------------- CO2 Sensor ------------------- */
/* -------------------------------------------------- */

void Co2Sensor_Init()
{
	sensirion_i2c_hal_init();

	/* Clean up potential previous states */
	scd4x_wake_up();
	scd4x_stop_periodic_measurement();
	scd4x_reinit();

	/* receive the serial Number, just for testing purposes */
	int16_t error = 0;
	uint16_t serial_0;
	uint16_t serial_1;
	uint16_t serial_2;
	error = scd4x_get_serial_number(&serial_0, &serial_1, &serial_2);
	while (error)
	{
		/*
		 * If an error is reported back, the System will stuck indefinitly, until the watchdog restarts the system
		 * It means that somethings wrong on the I2C Com
		 */

		/* Retry reading the serial number */
		error = scd4x_get_serial_number(&serial_0, &serial_1, &serial_2);

		/* Toggle the Status LED to indicate error */
		StatusLed_Toggle();

		/* Wait for 500ms */
		Delay_ms(500);
	}

	/*
	 * Start the periodic measurement
	 * - scd4x_start_periodic_measurement(): It takes measures every 5sec. The Sensor requires around 20mA in this mode
	 * - scd4x_start_low_power_periodic_measurement(): Measures every 30sec. Power Consumption: 4mA
	 */
	scd4x_start_periodic_measurement(); // Start periodic 5 sec interval measurement
	//scd4x_start_low_power_periodic_measurement(); // Start periodic 30 sec interval measurement

	/* Wait for 5 Seconds - The sensor needs some warm up time */
	Delay_ms(5000);
}
bool Co2Sensor_IsNewSampleReady()
{
	/* Check whether new data can be taken from the sensor */
	bool data_ready_flag = false;
	scd4x_get_data_ready_flag(&data_ready_flag);
	return data_ready_flag;
}
uint16_t Co2Sensor_GetSample()
{
	static uint16_t u16Co2NewValue;
	static uint16_t u16Co2OldValue;
	int32_t temperature_tmp;
	int32_t humidity_tmp;

	/* Get the data from the scd40 sensor */
	scd4x_read_measurement(&u16Co2NewValue, &temperature_tmp, &humidity_tmp);

	/* Filter out invalid readings */
	if (u16Co2NewValue == 0)
	{
		u16Co2NewValue = u16Co2OldValue;
	}
	else
	{
		u16Co2OldValue = u16Co2NewValue;
	}
	return u16Co2NewValue;
}
