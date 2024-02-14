#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <display_init.h>
#include <encoder_location.h>
#include <setting_data.h>
#include <bytes.h>

extern volatile int requsted_temp;

void print_setting_temp()
{
    //Serial.println(requested_temp);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Choose temperature:");
    lcd.setCursor(0,2);
    lcd.print(5 + requested_temp);
    lcd.setCursor(2,2);
    lcd.write((byte)0);
    lcd.setCursor(3,2);
    lcd.print("C");
}