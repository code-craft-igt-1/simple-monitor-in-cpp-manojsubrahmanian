#include "gtest/gtest.h"
#include "./monitor.h"

// Test Case: Temperature Just Below Lower Limit
TEST(AreVitalsNormalTest, TemperatureJustBelowLowerLimit) {
    EXPECT_FALSE(areVitalsNormal(TEMPERATURE_LOWER_LIMIT, 75, 95));
}

// Test Case: Temperature Just Above Lower Limit
TEST(AreVitalsNormalTest, TemperatureJustAboveLowerLimit) {
    EXPECT_TRUE(areVitalsNormal(TEMPERATURE_LOWER_LIMIT + 0.1, 75, 95));
}

// Test Case: Temperature Just Below Upper Limit
TEST(AreVitalsNormalTest, TemperatureJustBelowUpperLimit) {
    EXPECT_TRUE(areVitalsNormal(TEMPERATURE_UPPER_LIMIT - 0.1, 75, 95));
}

// Test Case: Temperature Just Above Upper Limit
TEST(AreVitalsNormalTest, TemperatureJustAboveUpperLimit) {
    EXPECT_FALSE(areVitalsNormal(TEMPERATURE_UPPER_LIMIT, 75, 95));
}

// Test Case: Pulse Rate Just Below Lower Limit
TEST(AreVitalsNormalTest, PulseRateJustBelowLowerLimit) {
    EXPECT_FALSE(areVitalsNormal(98.6, PULSE_RATE_LOWER_LIMIT, 95));
}

// Test Case: Pulse Rate Just Above Lower Limit
TEST(AreVitalsNormalTest, PulseRateJustAboveLowerLimit) {
    EXPECT_TRUE(areVitalsNormal(98.6, PULSE_RATE_LOWER_LIMIT + 0.1, 95));
}

// Test Case: Pulse Rate Just Below Upper Limit
TEST(AreVitalsNormalTest, PulseRateJustBelowUpperLimit) {
    EXPECT_TRUE(areVitalsNormal(98.6, PULSE_RATE_UPPER_LIMIT - 0.1, 95));
}

// Test Case: Pulse Rate Just Above Upper Limit
TEST(AreVitalsNormalTest, PulseRateJustAboveUpperLimit) {
    EXPECT_FALSE(areVitalsNormal(98.6, PULSE_RATE_UPPER_LIMIT, 95));
}

// Test Case: SpO2 Just Below Lower Limit
TEST(AreVitalsNormalTest, Spo2JustBelowLowerLimit) {
    EXPECT_FALSE(areVitalsNormal(98.6, 75, SPO2_LOWER_LIMIT));
}

// Test Case: SpO2 Just Above Lower Limit
TEST(AreVitalsNormalTest, Spo2JustAboveLowerLimit) {
    EXPECT_TRUE(areVitalsNormal(98.6, 75, SPO2_LOWER_LIMIT + 0.1));
}

// Test Case: SpO2 Just Below Upper Limit
TEST(AreVitalsNormalTest, Spo2JustBelowUpperLimit) {
    EXPECT_TRUE(areVitalsNormal(98.6, 75, SPO2_UPPER_LIMIT - 0.1));
}

// Test Case: SpO2 Just Above Upper Limit
TEST(AreVitalsNormalTest, Spo2JustAboveUpperLimit) {
    EXPECT_FALSE(areVitalsNormal(98.6, 75, SPO2_UPPER_LIMIT));
}

// Test Case: All Vitals Within Normal Range
TEST(AreVitalsNormalTest, AllVitalsWithinNormalRange) {
    EXPECT_TRUE(areVitalsNormal(98.6, 75, 95));
}

// Test Case: All Vitals Just Inside Lower Limits
TEST(AreVitalsNormalTest, AllVitalsJustInsideLowerLimits) {
    EXPECT_TRUE(areVitalsNormal(TEMPERATURE_LOWER_LIMIT + 0.1, PULSE_RATE_LOWER_LIMIT + 0.1,
                                SPO2_LOWER_LIMIT + 0.1));
}

// Test Case: All Vitals Just Inside Upper Limits
TEST(AreVitalsNormalTest, AllVitalsJustInsideUpperLimits) {
    EXPECT_TRUE(areVitalsNormal(TEMPERATURE_UPPER_LIMIT - 0.1, PULSE_RATE_UPPER_LIMIT - 0.1,
                                SPO2_UPPER_LIMIT - 0.1));
}

// Test Case: All Vitals Out of Range (Temperature out of range)
TEST(AreVitalsNormalTest, TemperatureOutOfRange) {
    EXPECT_FALSE(areVitalsNormal(TEMPERATURE_LOWER_LIMIT - 0.1, 75, 95));
}

// Test Case: All Vitals Out of Range (Pulse Rate out of range)
TEST(AreVitalsNormalTest, PulseRateOutOfRange) {
    EXPECT_FALSE(areVitalsNormal(98.6, PULSE_RATE_UPPER_LIMIT + 0.1, 95));
}

// Test Case: All Vitals Out of Range (SpO2 out of range)
TEST(AreVitalsNormalTest, Spo2OutOfRange) {
    EXPECT_FALSE(areVitalsNormal(98.6, 75, SPO2_LOWER_LIMIT - 0.1));
}

// Test Case: All Vitals Borderline (Temperature at upper limit, Pulse Rate at upper limit,
// SpO2 at lower limit)
TEST(AreVitalsNormalTest, VitalsBorderline) {
    EXPECT_FALSE(areVitalsNormal(TEMPERATURE_UPPER_LIMIT, PULSE_RATE_UPPER_LIMIT, 
                                SPO2_LOWER_LIMIT));
}

// Test Case: Only Temperature Out of Range (Temperature above upper limit, Pulse Rate
// and SpO2 within range)
TEST(AreVitalsNormalTest, OnlyTemperatureOutOfRange) {
    EXPECT_FALSE(areVitalsNormal(TEMPERATURE_UPPER_LIMIT + 0.1, 75, 95));
}

// Test Case: Only Pulse Rate Out of Range (Pulse Rate above upper limit, Temperature
// and SpO2 within range)
TEST(AreVitalsNormalTest, OnlyPulseRateOutOfRange) {
    EXPECT_FALSE(areVitalsNormal(98.6, PULSE_RATE_UPPER_LIMIT + 0.1, 95));
}

// Test Case: Only SpO2 Out of Range (SpO2 above upper limit, Temperature and
// Pulse Rate within range)
TEST(AreVitalsNormalTest, OnlySpo2OutOfRange) {
    EXPECT_FALSE(areVitalsNormal(98.6, 75, SPO2_UPPER_LIMIT + 0.1));
}
