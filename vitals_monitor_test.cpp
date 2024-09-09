#include "gtest/gtest.h"
#include "vitals_monitor.h"
#include "vitals_messages_en.h"
#include "vitals_messages_de.h"

// Test for converting temperature from Celsius to Fahrenheit
TEST(VitalMonitorTest, ConvertToCommonUnitTest) {
    EXPECT_DOUBLE_EQ(convertToCommonUnit(37.0, TEMPERATURE, CELSIUS), 98.6);
    EXPECT_DOUBLE_EQ(convertToCommonUnit(100.0, TEMPERATURE, FAHRENHEIT), 100.0);
    EXPECT_DOUBLE_EQ(convertToCommonUnit(70.0, PULSE_RATE, BPM), 70.0);  // No conversion
}

// Test for checking the status of vitals based on values
TEST(VitalMonitorTest, CheckVitalStatusTest) {
    // Test temperature thresholds
    EXPECT_EQ(checkVitalStatus(94.0, vitalThresholds.at(TEMPERATURE)), LOW);
    EXPECT_EQ(checkVitalStatus(96.0, vitalThresholds.at(TEMPERATURE)), NEAR_LOW);
    EXPECT_EQ(checkVitalStatus(99.0, vitalThresholds.at(TEMPERATURE)), NORMAL);
    EXPECT_EQ(checkVitalStatus(101.0, vitalThresholds.at(TEMPERATURE)), NEAR_HIGH);
    EXPECT_EQ(checkVitalStatus(103.0, vitalThresholds.at(TEMPERATURE)), HIGH);

    // Test pulse rate thresholds
    EXPECT_EQ(checkVitalStatus(55.0, vitalThresholds.at(PULSE_RATE)), LOW);
    EXPECT_EQ(checkVitalStatus(62.0, vitalThresholds.at(PULSE_RATE)), NEAR_LOW);
    EXPECT_EQ(checkVitalStatus(80.0, vitalThresholds.at(PULSE_RATE)), NORMAL);
    EXPECT_EQ(checkVitalStatus(104.0, vitalThresholds.at(PULSE_RATE)), NEAR_HIGH);
    EXPECT_EQ(checkVitalStatus(106.0, vitalThresholds.at(PULSE_RATE)), HIGH);

    // Test SPO2 thresholds
    EXPECT_EQ(checkVitalStatus(85.0, vitalThresholds.at(SPO2)), LOW);
    EXPECT_EQ(checkVitalStatus(91.0, vitalThresholds.at(SPO2)), NEAR_LOW);
    EXPECT_EQ(checkVitalStatus(96.0, vitalThresholds.at(SPO2)), NORMAL);
    EXPECT_EQ(checkVitalStatus(99.0, vitalThresholds.at(SPO2)), NEAR_HIGH);
    EXPECT_EQ(checkVitalStatus(101.0, vitalThresholds.at(SPO2)), HIGH);
}

// Test for processing vitals with English messages
TEST(VitalMonitorTest, ProcessVitalsEnglishTest) {
    std::vector<VitalData> vitalArray = {
        {TEMPERATURE, FAHRENHEIT, 101.0},  // Near high, normal case
        {PULSE_RATE, BPM, 59.0},           // Low, critical case
        {SPO2, PERCENTAGE, 97.0},          // Normal case
        {TEMPERATURE, CELSIUS, 36.5}       // Near low after conversion to Fahrenheit
    };

    // Capture output to check the displayed messages
    testing::internal::CaptureStdout();
    bool vitalsInRange = vitalsOk(vitalArray, vitalMessagesEn);
    std::string output = testing::internal::GetCapturedStdout();

    // Verify the expected output for each vital
    EXPECT_TRUE(output.find("Warning: Approaching hyperthermia.") != std::string::npos);
    EXPECT_TRUE(output.find("Pulse rate is too low!") != std::string::npos);
    EXPECT_TRUE(output.find("Oxygen saturation is normal.") != std::string::npos);
    //EXPECT_TRUE(output.find("Warning: Approaching hypothermia.") != std::string::npos);

    // Check the final result
    EXPECT_FALSE(vitalsInRange);  // Some vitals are critical (Low)
}

// Test for processing vitals with German messages
TEST(VitalMonitorTest, ProcessVitalsGermanTest) {
    std::vector<VitalData> vitalArray = {
        {TEMPERATURE, FAHRENHEIT, 101.0},  // Near high, normal case
        {PULSE_RATE, BPM, 59.0},           // Low, critical case
        {SPO2, PERCENTAGE, 97.0},          // Normal case
        {TEMPERATURE, CELSIUS, 36.5}       // Near low after conversion to Fahrenheit
    };

    // Capture output to check the displayed messages
    testing::internal::CaptureStdout();
    bool vitalsInRange = vitalsOk(vitalArray, vitalMessagesDe);
    std::string output = testing::internal::GetCapturedStdout();

    // Verify the expected output for each vital in German
    EXPECT_TRUE(output.find("Warnung: Annäherung an Hyperthermie.") != std::string::npos);
    EXPECT_TRUE(output.find("Die Pulsfrequenz ist zu niedrig!") != std::string::npos);
    EXPECT_TRUE(output.find("Die Sauerstoffsättigung ist normal.") != std::string::npos);
    //EXPECT_TRUE(output.find("Warnung: Annäherung an Hypothermie.") != std::string::npos);

    // Check the final result
    EXPECT_FALSE(vitalsInRange);  // Some vitals are critical (Low)
}
