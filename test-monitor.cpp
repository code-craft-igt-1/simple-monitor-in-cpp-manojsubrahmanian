#include "./monitor.h"

#include "gtest/gtest.h"

// Test Case: All vitals within normal range
TEST(AreVitalsNormalTest, VitalsWithinNormalRange) {
    EXPECT_FALSE(areVitalsNormal(98.6, 75, 95));
}

// Test Case: Temperature out of range - lower limit
TEST(AreVitalsNormalTest, TemperatureBelowLowerLimit) {
    EXPECT_FALSE(areVitalsNormal(94.9, 75, 95));
}

// Test Case: Temperature out of range - upper limit
TEST(AreVitalsNormalTest, TemperatureAboveUpperLimit) {
    EXPECT_FALSE(areVitalsNormal(102.1, 75, 95));
}

// Test Case: Pulse rate out of range - lower limit
TEST(AreVitalsNormalTest, PulseRateBelowLowerLimit) {
    EXPECT_FALSE(areVitalsNormal(98.6, 59.9, 95));
}

// Test Case: Pulse rate out of range - upper limit
TEST(AreVitalsNormalTest, PulseRateAboveUpperLimit) {
    EXPECT_FALSE(areVitalsNormal(98.6, 100.1, 95));
}

// Test Case: Oxygen saturation out of range - lower limit
TEST(AreVitalsNormalTest, Spo2BelowLowerLimit) {
    EXPECT_FALSE(areVitalsNormal(98.6, 75, -0.1));
}

// Test Case: Oxygen saturation out of range - upper limit
TEST(AreVitalsNormalTest, Spo2AboveUpperLimit) {
    EXPECT_FALSE(areVitalsNormal(98.6, 75, 90));
}

// Test Case: Temperature at the lower limit
TEST(AreVitalsNormalTest, TemperatureAtLowerLimit) {
    EXPECT_FALSE(areVitalsNormal(95, 75, 95));
}

// Test Case: Temperature at the upper limit
TEST(AreVitalsNormalTest, TemperatureAtUpperLimit) {
    EXPECT_FALSE(areVitalsNormal(102, 75, 95));
}

// Test Case: Pulse rate at the lower limit
TEST(AreVitalsNormalTest, PulseRateAtLowerLimit) {
    EXPECT_FALSE(areVitalsNormal(98.6, 60, 95));
}

// Test Case: Pulse rate at the upper limit
TEST(AreVitalsNormalTest, PulseRateAtUpperLimit) {
    EXPECT_FALSE(areVitalsNormal(98.6, 100, 95));
}

// Test Case: Oxygen saturation at the lower limit
TEST(AreVitalsNormalTest, Spo2AtLowerLimit) {
    EXPECT_FALSE(areVitalsNormal(98.6, 75, 0));
}

// Test Case: Oxygen saturation at the upper limit
TEST(AreVitalsNormalTest, Spo2AtUpperLimit) {
    EXPECT_FALSE(areVitalsNormal(98.6, 75, 90));
}
