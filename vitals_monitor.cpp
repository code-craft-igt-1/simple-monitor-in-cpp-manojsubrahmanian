#include "vitals_monitor.h"
#include <algorithm>  // For std::find_if
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

// Function to convert values to the appropriate unit (if needed)
double convertToCommonUnit(double value, VitalType type, VitalUnit unit) {
    if (type == TEMPERATURE && unit == CELSIUS) {
        return value * 9.0 / 5.0 + 32;  // Convert Celsius to Fahrenheit
    }
    return value;  // No conversion needed for PULSE_RATE and SPO2
}

// Function to check the vital status using std::find_if
VitalStatus checkVitalStatus(double value, const VitalLimits& limits) {
    // Array of limits and statuses for easier transformation
    std::vector<std::pair<double, VitalStatus>> thresholds = {
        {limits.low, LOW},
        {limits.nearLow, NEAR_LOW},
        {limits.nearHigh, NORMAL},
        {limits.high, NEAR_HIGH}
    };

    // Use std::find_if to locate the appropriate threshold and status
    auto it = std::find_if(thresholds.begin(), thresholds.end(), 
                           [value](const std::pair<double, VitalStatus>& limit) {
        return value <= limit.first;
    });

    // If a threshold is found, return the corresponding status, otherwise return HIGH
    return it != thresholds.end() ? it->second : HIGH;
}

// Function to process the vital data
bool vitalsOk(const std::vector<VitalData>& vitalArray, 
                   const std::map<VitalType, std::map<VitalStatus, std::string>>& vitalMessages) {
    bool allVitalsOk = true;

    for (const auto& vital : vitalArray) {
        // Convert the value to the common unit if necessary
        double convertedValue = convertToCommonUnit(vital.value, vital.type, vital.unit);

        // Get the limits for the current vital type
        const VitalLimits& limits = vitalThresholds.at(vital.type);

        // Check the vital status
        VitalStatus status = checkVitalStatus(convertedValue, limits);

        // Print the corresponding message
        std::cout << vitalMessages.at(vital.type).at(status) << std::endl;

        // If the status is LOW or HIGH, it's critical
        if (status == LOW || status == HIGH) {
            allVitalsOk = false;
            std::cout << "Critical Warning! Immediate action required!" << std::endl;
        }
    }

    return allVitalsOk;
}
