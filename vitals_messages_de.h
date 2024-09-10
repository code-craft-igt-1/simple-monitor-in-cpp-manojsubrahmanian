#pragma once
#include "./vitals_monitor.h"
#include <map>
#include <string>

// Static map associating VitalType with corresponding error messages in German
static const std::map<VitalType, std::map<VitalStatus, std::string>> vitalMessagesDe = {
    {TEMPERATURE, {
        {LOW, "Die Temperatur ist kritisch niedrig!"},
        {NEAR_LOW, "Warnung: Annäherung an Hypothermie."},
        {NORMAL, "Die Temperatur ist normal."},
        {NEAR_HIGH, "Warnung: Annäherung an Hyperthermie."},
        {HIGH, "Die Temperatur ist kritisch hoch!"}
    }},
    {PULSE_RATE, {
        {LOW, "Die Pulsfrequenz ist zu niedrig!"},
        {NEAR_LOW, "Warnung: Annäherung an das untere Limit der Pulsfrequenz."},
        {NORMAL, "Die Pulsfrequenz ist normal."},
        {NEAR_HIGH, "Warnung: Annäherung an das obere Limit der Pulsfrequenz."},
        {HIGH, "Die Pulsfrequenz ist zu hoch!"}
    }},
    {SPO2, {
        {LOW, "Die Sauerstoffsättigung ist kritisch niedrig!"},
        {NEAR_LOW, "Warnung: Annäherung an das untere Limit der Sauerstoffsättigung."},
        {NORMAL, "Die Sauerstoffsättigung ist normal."},
        {NEAR_HIGH, "Warnung: Annäherung an das obere Limit der Sauerstoffsättigung."},
        {HIGH, "Die Sauerstoffsättigung ist zu hoch!"}
    }}
};

