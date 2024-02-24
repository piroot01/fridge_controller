#pragma once

#include <modules/module.h>
#include <modules/lcd.h>

static const int time_delay = 22;
static const int io_pin = 4;
static const int sclk_pin = 2;
static const int ce_pin = 3;

enum SET_TIME
{
    HOUR, MINUTE
};

extern ThreeWire wire;

extern RtcDS1302<ThreeWire> rtc;

extern SET_TIME time_state;

void printDateTime(const RtcDateTime& dt);

void rtc_setup();

void print_time();

void print_dash();

void print_setting_time();

void set_time(int hours, int minutes);
