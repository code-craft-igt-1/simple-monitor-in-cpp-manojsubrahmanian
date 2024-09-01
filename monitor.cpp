#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

bool isWithinRange(double value, double lowerLimit, double upperLimit) {
  return (value > lowerLimit) && (value < upperLimit);
}

void showAlertAnimation(int durationInSeconds) {
  for (int i = 0; i < durationInSeconds / 2; i++) {
    cout << "\r* " << flush;
    sleep_for(seconds(1));
    cout << "\r *" << flush;
    sleep_for(seconds(1));
  }
}

bool validateAndAlert(bool condition, const std::string &message) {
  if (!condition) {
    cout << message << "\n";
    showAlertAnimation(2);
  }
  return condition;
}

// Updated function with units in comments
bool areVitalsNormal(double temperatureFahrenheit, double pulseRateBpm, double spo2Percentage) {
  bool temperatureNormal = validateAndAlert(
           isWithinRange(temperatureFahrenheit, TEMPERATURE_LOWER_LIMIT, TEMPERATURE_UPPER_LIMIT),
           "Temperature (°F) is critical!");
  bool pulseNormal = validateAndAlert(
           isWithinRange(pulseRateBpm, PULSE_RATE_LOWER_LIMIT, PULSE_RATE_UPPER_LIMIT),
           "Pulse Rate (bpm) is out of range!");
  bool spo2Normal = validateAndAlert(
           isWithinRange(spo2Percentage, SPO2_LOWER_LIMIT, SPO2_UPPER_LIMIT),
           "Oxygen Saturation (SpO2 %) is out of range!");

  return temperatureNormal && pulseNormal && spo2Normal;
}
