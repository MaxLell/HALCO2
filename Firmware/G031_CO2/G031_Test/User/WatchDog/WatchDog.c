/*
 * WatchDog.c
 *
 *  Created on: 28.04.2022
 *      Author: maxlell
 */

#include "WatchDog.h"
#include "iwdg.h"
#include "main.h"

void Watchdog_Feed()
{
	/*
	 * Feed the Watchdog, so that it doesn't bite you.
	 * In its current configuration the Watchdog needs to be
	 * fed at least once every 32 seconds (approx.).
	 */
	HAL_IWDG_Refresh(&hiwdg);
}
