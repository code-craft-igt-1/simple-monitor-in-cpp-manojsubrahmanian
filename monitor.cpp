#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

bool isValueInRange(double value, double lowerLimit, double upperLimit) {
  return (value > lowerLimit) && (value < upperLimit);
}

void displayAlert() {
  for (int i = 0; i < 6; i++) {
    cout << "\r* " << flush;
    sleep_for(seconds(1));
    cout << "\r *" << flush;
    sleep_for(seconds(1));
  }
}

int areVitalsNormal(float temperature, float pulseRate, float spo2) {
  if (!isValueInRange(temperature, 95, 102)) {
    cout << "Temperature is critical!\n";
    displayAlert();
    return 0;
  } else if (!isValueInRange(pulseRate, 60, 100)) {
    cout << "Pulse Rate is out of range!\n";
    displayAlert();
    return 0;
  } else if (!isValueInRange(spo2, 0, 90)) {
    cout << "Oxygen Saturation out of range!\n";
    displayAlert();
    return 0;
  }
  return 1;
}
