#pragma once

#include "vitals_monitor.h"
#include <map>

// Static map associating VitalType with corresponding error messages in English
static const std::map<VitalType, std::map<VitalStatus, std::string>> vitalMessagesEn = {
    {TEMPERATURE, {
        {LOW, "Temperature is critically low!"},
        {NEAR_LOW, "Warning: Approaching hypothermia."},
        {NORMAL, "Temperature is normal."},
        {NEAR_HIGH, "Warning: Approaching hyperthermia."},
        {HIGH, "Temperature is critically high!"}
    }},
    {PULSE_RATE, {
        {LOW, "Pulse rate is too low!"},
        {NEAR_LOW, "Warning: Pulse rate is approaching lower limit."},
        {NORMAL, "Pulse rate is normal."},
        {NEAR_HIGH, "Warning: Pulse rate is approaching upper limit."},
        {HIGH, "Pulse rate is too high!"}
    }},
    {SPO2, {
        {LOW, "Oxygen saturation is critically low!"},
        {NEAR_LOW, "Warning: Oxygen saturation is approaching lower limit."},
        {NORMAL, "Oxygen saturation is normal."},
        {NEAR_HIGH, "Warning: Oxygen saturation is approaching upper limit."},
        {HIGH, "Oxygen saturation is too high!"}
    }}
};

