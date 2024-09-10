#include "gtest/gtest.h"
#include "vitals_monitor.h"

// Test for checking the vitals and updating status correctly with conversions
TEST(VitalMonitorTest, VitalsOkWithConversionsTest) {
    std::vector<VitalData> vitalArray = {
        {TEMPERATURE, CELSIUS, 37.0},   // Initially UNKNOWN, converted to Fahrenheit
        {PULSE_RATE, BPM, 59.0},        // Initially UNKNOWN
        {SPO2, PERCENTAGE, 97.0},       // Initially UNKNOWN
        {TEMPERATURE, FAHRENHEIT, 101.0} // Initially UNKNOWN
    };

    // Process the vitals and check their status
    bool result = vitalsOk(vitalArray);

    // Check that vitalsOk returns false since there are critical vitals
    EXPECT_FALSE(result);

    // Check that the correct statuses are set
    EXPECT_EQ(vitalArray[0].status, NORMAL);    // 37.0C converted to 98.6F for temperature
    EXPECT_EQ(vitalArray[1].status, LOW);       // 59 bpm for pulse rate
    EXPECT_EQ(vitalArray[2].status, NORMAL);    // 97% for SPO2
    EXPECT_EQ(vitalArray[3].status, NEAR_HIGH); // 101.0F for temperature
}

// Test for vitals that do not require conversion
TEST(VitalMonitorTest, VitalsNoConversionTest) {
    std::vector<VitalData> vitalArray = {
        {TEMPERATURE, FAHRENHEIT, 98.6},   // Normal
        {PULSE_RATE, BPM, 72.0},           // Normal
        {SPO2, PERCENTAGE, 96.0},          // Normal
    };

    // Process the vitals and check their status
    bool result = vitalsOk(vitalArray);

    // Check that vitalsOk returns true since all vitals are in normal range
    EXPECT_TRUE(result);

    // Check that the correct statuses are set
    EXPECT_EQ(vitalArray[0].status, NORMAL);    // 98.6F for temperature
    EXPECT_EQ(vitalArray[1].status, NORMAL);    // 72 bpm for pulse rate
    EXPECT_EQ(vitalArray[2].status, NORMAL);    // 96% for SPO2
}
