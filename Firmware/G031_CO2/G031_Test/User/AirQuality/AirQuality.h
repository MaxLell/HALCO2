#ifndef AIRQUALITY_H
#define AIRQUALITY_H

#include <stdint.h>

typedef enum
{
    PERFECT_AIR,
    GOOD_AIR,
    MEDIUM_AIR,
    BAD_AIR
} AirQuality_e;

AirQuality_e AirQuality_GetFromCO2(uint16_t);
uint16_t AirQuality_getAverageOverFiveSamples(uint16_t u16CurrentSample);

#endif // AIRQUALITY_H
