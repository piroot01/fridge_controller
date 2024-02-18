#pragma once

#include <must_be_included.h>
#include <AutoPID.h>

extern double set_point;
extern double input;
extern bool output;

extern AutoPIDRelay pid;

void pid_setup();

void update_set_temp(const double temp);

void pid_loop();