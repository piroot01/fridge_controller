// sloucit s color_cange.h do strip.h
#pragma once

#include <Arduino.h>
#include <display_init.h>
#include <enums.h>
#include <color_change.h>
#include <magnet.h>
#include <setting_data.h>

STRIP_MODES mode;

const char* strip_modes[3]
{
    "Always ON",
    "Always OFF",
    "Auto",
};

void print_setting_mode()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Choose strip mode:");
    lcd.setCursor(0,2);
    lcd.print(strip_modes[requested_mode]);
}

void mode_control(STRIP_MODES mode)
{
    switch (mode)
    {
        case STRIP_MODES::ON:
            color_control();
            break;
        case STRIP_MODES::AUTO:
            if (magnet_logic())
            {
                color_control();
            }
            else
            {
                change_color(CRGB::Black);
            }
            break;
        case STRIP_MODES::OFF:
            change_color(CRGB::Black);
            break;
        default:
            break;
    }
}
