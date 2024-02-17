#pragma once

// #include <must_be_included.h>
#include <Arduino.h>
#include <pins.h>

// v podstate takhle bych tvoril kazdy modul
unsigned long buzzer_freq = 1000;
unsigned long alarm_freq = 4000;

const char* alarm_modes[2]
{
    "OFF",
    "ON",
};


void buzzer_setup()
{
    pinMode(buzzer, OUTPUT);
}

void buzz(unsigned long buzz_time)
{
    tone(buzzer, buzzer_freq, buzz_time);
}

void alarm(bool flag)
{
    if (flag == true)
    {
        tone(buzzer, alarm_freq);
    }
    else
    {
        noTone(buzzer);
    }
}

void print_setting_alarm()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Choose alarm mode:");
    lcd.setCursor(0,2);
    lcd.print(alarm_modes[requested_alarm]);
}
