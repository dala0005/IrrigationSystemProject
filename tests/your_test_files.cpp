// tests/your_test_files.cpp
#include <gtest/gtest.h>

// Setting up Arduino
struct Sensor
{
    uint8_t id;
    uint16_t maxDryValue;
    uint16_t maxWetValue;
};

const uint8_t numberOfSensors = 1;

Sensor sensors[numberOfSensors];

void initSensors()
{
     sensors[0].id = 0;
     sensors[0].maxDryValue = 822;
     sensors[0].maxWetValue = 465;
}


TEST(YourTestSuite, TestName) {
    // Your test code here
    initSensors();

    ASSERT_TRUE(true);
}

