#include "./vitals_monitor.h"
#include "./vitals_messages.h"
#include <algorithm>  // For std::for_each, std::find_if, std::none_of
#include <functional>  // For std::function
#include <utility>
#include <vector>  // For std::vector
#include <iostream>  // For std::cout
#include <thread>  // For std::this_thread::sleep_for

// Struct to hold conversion information
struct ConversionRule {
    VitalUnit fromUnit;
    VitalUnit toUnit;
    std::function<double(double)> convertFunc;
};

// List of conversion rules
std::vector<ConversionRule> conversionRules = {
    {CELSIUS, FAHRENHEIT, [](double value) { return value * 9.0 / 5.0 + 32; }},
    {FAHRENHEIT, FAHRENHEIT, [](double value) { return value; }},
    {BPM, BPM, [](double value) { return value; }},
    {PERCENTAGE, PERCENTAGE, [](double value) { return value; }},
};

// Critical statuses that require animation
static const std::vector<VitalStatus> criticalStatuses = {LOW, HIGH};

// Star animation function for critical alerts
void showAlertAnimation(int durationInSeconds) {
    for (int i = 0; i < durationInSeconds * 2; ++i) {
        std::cout << (i % 2 == 0 ? "\r* " : "\r *") << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    std::cout << "\n";
}

// Function to print alert based on the vital's status using the selected message map and language
void printAlert(const VitalData& vital, Language language) {
    // Find the alert message for the current vital type and status in the selected language
    auto messageIt = vitalMessages.at(language).find(vital.type);

    if (messageIt != vitalMessages.at(language).end()) {
        auto statusIt = messageIt->second.find(vital.status);
        if (statusIt != messageIt->second.end()) {
            std::cout << statusIt->second << "\n";
        }
    }

    // Check if status is critical and trigger animation
    if (std::find(criticalStatuses.begin(), criticalStatuses.end(), vital.status) != criticalStatuses.end()) {
        showAlertAnimation(2);
    }
}

// Function to convert values to the appropriate unit using vector functions
double convertToCommonUnit(double value, VitalUnit fromUnit) {
    // Find the matching conversion rule
    auto it = std::find_if(conversionRules.begin(), conversionRules.end(),
                           [fromUnit](const ConversionRule& rule) {
                               return rule.fromUnit == fromUnit;
                           });

    // Apply the conversion function if a rule is found
    return (it != conversionRules.end()) ? it->convertFunc(value) : value;
}

// Function to check and update the vital status based on the thresholds
void checkVitalStatus(VitalData* vital) {
    if (vital == nullptr) return;  // Guard clause for null pointers

    double convertedValue = convertToCommonUnit(vital->value, vital->unit);
    const VitalLimits& limits = vitalThresholds.at(vital->type);

    // Array of thresholds to map ranges to status
    std::vector<std::pair<double, VitalStatus>> thresholds = {
        {limits.low, LOW},
        {limits.nearLow, NEAR_LOW},
        {limits.nearHigh, NORMAL},
        {limits.high, NEAR_HIGH}
    };

    // Use std::find_if to determine the correct status and update the vital status directly
    auto statusIt = std::find_if(thresholds.begin(), thresholds.end(),
                                [convertedValue](const std::pair<double, VitalStatus>& limit) {
                                    return convertedValue <= limit.first;
                                });

    if (statusIt != thresholds.end()) {
        vital->status = statusIt->second;
    }
}

// Function to check if all vitals are okay, without using any == or && operators
bool vitalsOk(std::vector<VitalData>* vitalArray, Language language) {
    if (vitalArray == nullptr) return true;  // Guard clause for null pointers

    // First, update the status of each vital
    std::for_each(vitalArray->begin(), vitalArray->end(), [](VitalData& vital) {
        checkVitalStatus(&vital);  // Pass a pointer to each vital
    });

    // After processing all the vitals, print alerts for each one
    std::for_each(vitalArray->begin(), vitalArray->end(), [=](const VitalData& vital) {
        printAlert(vital, language);  // Pass the message array and vital
    });

    // Then, check if none of the vitals have a critical status
    return std::none_of(vitalArray->begin(), vitalArray->end(),
                       [](const VitalData& vital) {
        return std::find(criticalStatuses.begin(),
                         criticalStatuses.end(),
                         vital.status) != criticalStatuses.end();
    });
}
