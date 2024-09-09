#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

struct VitalLimits {
    double low;
    double nearLow;
    double nearHigh;
    double high;
};



bool isWithinRange(double value, double lowerLimit, double upperLimit) {
  return (value > lowerLimit) && (value < upperLimit);
}

void showAlertWithAnimation(const std::string &message, int durationInSeconds) {
  cout << message << "\n";
  for (int i = 0; i < durationInSeconds / 2; i++) {
    cout << "\r* " << flush;
    sleep_for(seconds(1));
    cout << "\r *" << flush;
    sleep_for(seconds(1));
  }
}

void validateAndAlert(bool isInRange, const std::string &message) {
  if (!isInRange) {
    showAlertWithAnimation(message, 2);
  }
}

// Updated function with units in comments
bool areVitalsNormal(double temperatureFahrenheit, double pulseRateBpm, double spo2Percentage) {
  bool temperatureInRange =
    isWithinRange(temperatureFahrenheit, TEMPERATURE_LOWER_LIMIT, TEMPERATURE_UPPER_LIMIT);
  validateAndAlert(temperatureInRange, "Temperature (°F) is critical!");
  bool pulseInRange =
    isWithinRange(pulseRateBpm, PULSE_RATE_LOWER_LIMIT, PULSE_RATE_UPPER_LIMIT);
  validateAndAlert(pulseInRange, "Pulse Rate (bpm) is out of range!");
  bool spo2InRange = isWithinRange(spo2Percentage, SPO2_LOWER_LIMIT, SPO2_UPPER_LIMIT);
  validateAndAlert(spo2InRange, "Oxygen Saturation (SpO2 %) is out of range!");

  return temperatureInRange && pulseInRange && spo2InRange;
}
