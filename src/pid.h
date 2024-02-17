// rozdelit do rmodules/relay.h a pid.h
#pragma once

#include <Arduino.h>
#include <AutoPID.h>
#include <thermistor.h>

double set_point;
double input;
bool output;
const double KP = 0.12;
const double KI = 0.0003;
const double KD = 0.0;
const int pulse_width = 10000;

AutoPIDRelay reg(&input, &set_point, &output, pulse_width, KP, KI, KD);

void pid_setup()
{
    set_point = 30.0;
    reg.setBangBang(4);
    reg.setTimeStep(4000);
}

void update_set_temp(const double temp)
{
    set_point = temp;
}

void pid_loop()
{
    input = get_temp();
    reg.run();
    //Serial.print(input);
    //Serial.print(", ");
    //Serial.println(output);
}
