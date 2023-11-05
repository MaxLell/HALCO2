#include "AirQuality.h"
#include "stdint.h"

static uint32_t u32PerfectAirQualityThreshold = 600;
static uint32_t u32GoodAirQualityThreshold = 800;
static uint32_t u32BadAirQualityThreshold = 1200;

uint16_t AirQuality_getAverageOverFiveSamples(uint16_t u16CurrentSample)
{
    uint16_t u16AverageSample;
#define u16NofSamples 5
    static uint16_t au16Samples[u16NofSamples] = {0};
    static uint16_t idx = 0;

    // Add sample to array at idx
    au16Samples[idx] = u16CurrentSample;

    // Calculate the average value of the array
    for (int i = 0; i < u16NofSamples; i++)
    {
        u16AverageSample += au16Samples[i];
    }
    u16AverageSample /= u16NofSamples;

    // increment idx
    idx++;

    // if idx > 5 -> Set to 0
    if (idx >= u16NofSamples)
    {
        idx = 0;
    }

    // return average value
    return u16AverageSample;
}

AirQuality_e AirQuality_GetFromCO2(uint16_t u16Co2Reading)
{
    /* Decide on the Air Quality */
    AirQuality_e eAirQuality = PERFECT_AIR;

    /* Perfect Air */
    if (u16Co2Reading <= u32PerfectAirQualityThreshold)
    {
        eAirQuality = PERFECT_AIR;
    }
    /* Good Air */
    else if ((u16Co2Reading > u32PerfectAirQualityThreshold) &&
             (u16Co2Reading <= u32GoodAirQualityThreshold))
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
    return eAirQuality;
}