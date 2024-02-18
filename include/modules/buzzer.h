#pragma once

#include <modules/module.h>
#include <modules/lcd.h>

static const int buzzer_pin = 5;

static const unsigned long buzzer_freq = 1000;
static const unsigned long alarm_freq = 4000;

inline const char* alarm_modes[2]
{
    "OFF",
    "ON",
};

void buzzer_setup();

void buzz(unsigned long buzz_time);

void alarm(bool flag);

void print_setting_alarm();