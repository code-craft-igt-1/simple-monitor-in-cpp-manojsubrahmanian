#include "./monitor.h"
#include "gtest/gtest.h"

// Test Case: Temperature Just Below Lower Limit
TEST(AreVitalsNormalTest, TemperatureJustBelowLowerLimit) {
    EXPECT_FALSE(areVitalsNormal(95.0, 75, 89));
}

// Test Case: Temperature Just Above Lower Limit
TEST(AreVitalsNormalTest, TemperatureJustAboveLowerLimit) {
    EXPECT_TRUE(areVitalsNormal(95.1, 75, 89));
}

// Test Case: Temperature Just Below Upper Limit
TEST(AreVitalsNormalTest, TemperatureJustBelowUpperLimit) {
    EXPECT_TRUE(areVitalsNormal(101.9, 75, 89));
}

// Test Case: Temperature Just Above Upper Limit
TEST(AreVitalsNormalTest, TemperatureJustAboveUpperLimit) {
    EXPECT_FALSE(areVitalsNormal(102.0, 75, 89));
}

// Test Case: Pulse Rate Just Below Lower Limit
TEST(AreVitalsNormalTest, PulseRateJustBelowLowerLimit) {
    EXPECT_FALSE(areVitalsNormal(98.6, 60.0, 89));
}

// Test Case: Pulse Rate Just Above Lower Limit
TEST(AreVitalsNormalTest, PulseRateJustAboveLowerLimit) {
    EXPECT_TRUE(areVitalsNormal(98.6, 60.1, 89));
}

// Test Case: Pulse Rate Just Below Upper Limit
TEST(AreVitalsNormalTest, PulseRateJustBelowUpperLimit) {
    EXPECT_TRUE(areVitalsNormal(98.6, 99.9, 89));
}

// Test Case: Pulse Rate Just Above Upper Limit
TEST(AreVitalsNormalTest, PulseRateJustAboveUpperLimit) {
    EXPECT_FALSE(areVitalsNormal(98.6, 100.0, 89));
}

// Test Case: SpO2 Just Below Lower Limit
TEST(AreVitalsNormalTest, Spo2JustBelowLowerLimit) {
    EXPECT_FALSE(areVitalsNormal(98.6, 75, 0.0));
}

// Test Case: SpO2 Just Above Lower Limit
TEST(AreVitalsNormalTest, Spo2JustAboveLowerLimit) {
    EXPECT_TRUE(areVitalsNormal(98.6, 75, 1.0));
}

// Test Case: SpO2 Just Below Upper Limit
TEST(AreVitalsNormalTest, Spo2JustBelowUpperLimit) {
    EXPECT_TRUE(areVitalsNormal(98.6, 75, 89.9));
}

// Test Case: SpO2 Just Above Upper Limit
TEST(AreVitalsNormalTest, Spo2JustAboveUpperLimit) {
    EXPECT_FALSE(areVitalsNormal(98.6, 75, 90.0));
}

// Test Case: All Vitals Within Normal Range
TEST(AreVitalsNormalTest, AllVitalsWithinNormalRange) {
    EXPECT_TRUE(areVitalsNormal(98.6, 75, 89));
}

// Test Case: All Vitals Just Inside Lower Limits
TEST(AreVitalsNormalTest, AllVitalsJustInsideLowerLimits) {
    EXPECT_TRUE(areVitalsNormal(95.1, 60.1, 1.0));
}

// Test Case: All Vitals Just Inside Upper Limits
TEST(AreVitalsNormalTest, AllVitalsJustInsideUpperLimits) {
    EXPECT_TRUE(areVitalsNormal(101.9, 99.9, 89.9));
}
