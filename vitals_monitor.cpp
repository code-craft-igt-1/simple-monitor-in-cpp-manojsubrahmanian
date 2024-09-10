#include "vitals_monitor.h"
#include <algorithm>  // For std::for_each, std::find_if, std::none_of
#include <functional>  // For std::function

// Struct to hold conversion information
struct ConversionRule {
    VitalType type;
    VitalUnit fromUnit;
    VitalUnit toUnit;
    std::function<double(double)> convertFunc;
};

// List of conversion rules
std::vector<ConversionRule> conversionRules = {
    {TEMPERATURE, CELSIUS, FAHRENHEIT, [](double value) { return value * 9.0 / 5.0 + 32; }},
    {TEMPERATURE, FAHRENHEIT, FAHRENHEIT, [](double value) { return value; }},
    {PULSE_RATE, BPM, BPM, [](double value) { return value; }},
    {SPO2, PERCENTAGE, PERCENTAGE, [](double value) { return value; }},
};

// Function to convert values to the appropriate unit using vector functions
double convertToCommonUnit(double value, VitalType type, VitalUnit unit) {
    // Find the matching conversion rule
    auto it = std::find_if(conversionRules.begin(), conversionRules.end(),
                           [type, unit](const ConversionRule& rule) {
                               return rule.type == type && rule.fromUnit == unit;
                           });

    // Apply the conversion function if a rule is found
    return (it != conversionRules.end()) ? it->convertFunc(value) : value;
}

// Function to check and update the vital status based on the thresholds
void checkVitalStatus(VitalData& vital) {
    double convertedValue = convertToCommonUnit(vital.value, vital.type, vital.unit);
    const VitalLimits& limits = vitalThresholds.at(vital.type);

    // Array of thresholds to map ranges to status
    std::vector<std::pair<double, VitalStatus>> thresholds = {
        {limits.low, LOW},
        {limits.nearLow, NEAR_LOW},
        {limits.nearHigh, NORMAL},
        {limits.high, NEAR_HIGH}
    };

    // Use std::find_if to determine the correct status and update the vital status directly
    vital.status = std::find_if(thresholds.begin(), thresholds.end(),
                                [convertedValue](const std::pair<double, VitalStatus>& limit) {
                                    return convertedValue <= limit.first;
                                })->second;
}

// Function to check if all vitals are okay, without using any == or && operators
bool vitalsOk(std::vector<VitalData>& vitalArray) {
    std::vector<VitalStatus> criticalStatuses = {LOW, HIGH};

    // First, update the status of each vital
    std::for_each(vitalArray.begin(), vitalArray.end(), [](VitalData& vital) {
        checkVitalStatus(vital);
    });

    // Then, check if none of the vitals have a critical status
    return std::none_of(vitalArray.begin(), vitalArray.end(), [&criticalStatuses](const VitalData& vital) {
        // Use std::find instead of == to check if the vital status is in criticalStatuses
        return std::find(criticalStatuses.begin(), criticalStatuses.end(), vital.status) != criticalStatuses.end();
    });
}
