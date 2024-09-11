#pragma once
#include "./vitals_monitor.h"
#include <map>
#include <string>

// Combined message map with language as the outer index
static const std::map<Language, std::map<VitalType, 
                                std::map<VitalStatus, 
                                std::string>>> vitalMessages = {
    // English messages
    {
        ENGLISH, {
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
                {NEAR_HIGH, "Oxygen saturation is normal."},
                {HIGH, "Oxygen saturation is normal."}
            }}
        }
    },

    // German messages
    {
        GERMAN, {
            {TEMPERATURE, {
                {LOW, "Die Temperatur ist kritisch niedrig!"},
                {NEAR_LOW, "Warnung: Nähern sich der Unterkühlung."},
                {NORMAL, "Die Temperatur ist normal."},
                {NEAR_HIGH, "Warnung: Nähern sich der Überhitzung."},
                {HIGH, "Die Temperatur ist kritisch hoch!"}
            }},
            {PULSE_RATE, {
                {LOW, "Der Puls ist zu niedrig!"},
                {NEAR_LOW, "Warnung: Der Puls nähert sich dem unteren Grenzwert."},
                {NORMAL, "Der Puls ist normal."},
                {NEAR_HIGH, "Warnung: Der Puls nähert sich dem oberen Grenzwert."},
                {HIGH, "Der Puls ist zu hoch!"}
            }},
            {SPO2, {
                {LOW, "Der Sauerstoffgehalt ist kritisch niedrig!"},
                {NEAR_LOW, "Warnung: Der Sauerstoffgehalt nähert sich dem unteren Grenzwert."},
                {NORMAL, "Der Sauerstoffgehalt ist normal."},
                {NEAR_HIGH, "Warnung: Der Sauerstoffgehalt nähert sich dem oberen Grenzwert."},
                {HIGH, "Der Sauerstoffgehalt ist zu hoch!"}
            }}
        }
    }
};
