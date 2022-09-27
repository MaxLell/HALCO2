/*
 * StatusLed.h
 *
 *  Created on: 28.04.2022
 *      Author: maxlell
 */

#ifndef STATUSLED_STATUSLED_H_
#define STATUSLED_STATUSLED_H_

#include "main.h"

void StatusLed_Disable();
void StatusLed_Toggle();
#define REGULAR_HEARTBEAT 4
#define RESTART_HEARTBEAT 10
void StatusLed_ShowHeartbeat(uint8_t u8Factor);

#endif /* STATUSLED_STATUSLED_H_ */
