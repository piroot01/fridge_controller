#pragma once

#include <modules/module.h>
#include <modules/lcd.h>

const static int alarm_pin = A0;

void alarm_setup();

bool get_alarm();

void print_alarm();