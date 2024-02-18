#pragma once

#include <modules/module.h>
#include <modules/buzzer.h>

static const int threshold = 100;
static const int interval_strip = 6000;
static const int interval_buzzer = 10000;
static const int magnet = A3;

inline bool buzz_flag = false;
inline unsigned long prev_mag_state_strip = 0;
inline unsigned long prev_mag_state_buzzer = 0;

void magnet_setup();

bool get_magnet();

void change_alarm();