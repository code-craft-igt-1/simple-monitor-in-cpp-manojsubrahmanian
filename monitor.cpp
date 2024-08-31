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
    return false;
  }
  return true;
}

// Updated function with units in comments
bool areVitalsNormal(float temperatureCelsius, float pulseRateBpm, float spo2Percentage) {
  return validateAndAlert(
           isWithinRange(temperatureCelsius, 95.0, 102.0),
           "Temperature (°F) is critical!"
         ) &&
         validateAndAlert(
           isWithinRange(pulseRateBpm, 60, 100),
           "Pulse Rate (bpm) is out of range!"
         ) &&
         validateAndAlert(
           isWithinRange(spo2Percentage, 0, 90),
           "Oxygen Saturation (SpO2 %) is out of range!"
         );
}



