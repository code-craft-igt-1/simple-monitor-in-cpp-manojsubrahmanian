#ifndef VITALS_MONITOR_H
#define VITALS_MONITOR_H

#include <string>
#include <map>
#include <vector>

// Enum for vital types
enum VitalType { TEMPERATURE, PULSE_RATE, SPO2 };

// Enum for vital units
enum VitalUnit { FAHRENHEIT, CELSIUS, BPM, PERCENTAGE };

// Enum for vital status
enum VitalStatus { LOW, NEAR_LOW, NORMAL, NEAR_HIGH, HIGH, UNKNOWN };

// Struct to store thresholds for a vital
struct VitalLimits {
    double low;
    double nearLow;
    double nearHigh;
    double high;
};

// Struct to hold the vital type, unit, value, and status (initially UNKNOWN)
struct VitalData {
    VitalType type;
    VitalUnit unit;
    double value;
    VitalStatus status = UNKNOWN;  // Initialize as UNKNOWN
};


// Static map associating VitalType with corresponding thresholds
static const std::map<VitalType, VitalLimits> vitalThresholds = {
    {TEMPERATURE, {95.0, 96.53, 100.47, 102.0}},
    {PULSE_RATE, {60.0, 63.0, 100.0, 105.0}},
    {SPO2, {90.0, 92.0, 98.0, 100.0}}
};

// Function declarations
double convertToCommonUnit(double value, VitalType type, VitalUnit unit);
VitalStatus checkVitalStatus(double value, const VitalLimits& limits);
bool vitalsOk(std::vector<VitalData>& vitalArray);

#endif
