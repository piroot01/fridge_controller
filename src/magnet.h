#pragma once

#include <pins.h>
#include <Arduino.h>
#include <buzzer.h>

const int threshold = 100;
unsigned long prev_mag_state_strip = 0;
unsigned long prev_mag_state_buzzer = 0;
const int interval_strip = 6000;
const int interval_buzzer = 10000;
bool buzz_flag = false;

void magnet_setup()
{
    pinMode(magnet, INPUT);
}

bool get_magnet()
{
    return (analogRead(magnet) > threshold)? true:false;
}

bool magnet_logic()
{
    static bool open_flag = false;
    
    if (get_magnet())
    {
        open_flag = true;
        if (millis() - prev_mag_state_buzzer > interval_buzzer)
        {
            buzz_flag = true;
            prev_mag_state_buzzer = millis();
        }
        return true;
    }
    else if (!get_magnet() and open_flag == true)
    {
        buzz_flag = false;
        if (millis() - prev_mag_state_strip > interval_strip)
        {
            prev_mag_state_strip = millis();
            open_flag = false;
            return false;
        }
        else
        {
            return true;
        }
    }
    return false;
}

void change_alarm()
{
    if (requested_alarm == 1)
    {
        alarm(buzz_flag);
    }
}