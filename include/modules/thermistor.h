#pragma once

#include <modules/module.h>
#include <modules/lcd.h>

static const int thermistor_pin = A1;
static const int RT0 = 10000;   
static const int B = 3977;  
static const int VCC = 5; 
static const int R = 10000;
static const float T0 = 298.15;

void thermistor_setup();

void print_temp();

float get_temp();

void print_setting_temp();