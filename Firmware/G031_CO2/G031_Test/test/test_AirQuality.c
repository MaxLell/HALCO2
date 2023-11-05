#include "unity.h"

#include "AirQuality.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_AirQuality_AirQuality_getAverageOverFiveSamples_shall_calculateTheAverageOver5Samples(void)
{
    uint16_t u16Samples[5] = {1, 2, 3, 4, 5};
    uint16_t u16Average;
    for (int i = 0; i < 5; i++)
    {
        u16Average = AirQuality_getAverageOverFiveSamples(u16Samples[i]);
    }
    TEST_ASSERT_EQUAL_UINT16(3, u16Average);
}
