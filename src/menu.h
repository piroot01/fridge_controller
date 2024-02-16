#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <display_init.h>
#include <enums.h>
#include <thermistor.h>
#include <time.h>
#include <temperature_change.h>
#include <color_change.h>
#include <setting_data.h>
#include <strip_mode.h>

void menu(MIDDLE_LVL_STATE mid_lvl);
void print_options(char option[]);
void update_lcd_once(TOP_LVL_STATE top_state, MIDDLE_LVL_STATE mid_state);
void update_lcd(TOP_LVL_STATE top_state, MIDDLE_LVL_STATE mid_state);
void setting(MIDDLE_LVL_STATE mid_lvl);

const int menu_size = 6;

const char* options[menu_size] = 
{
    "Change temperature",
    "Change LED color",
    "Change LED mode",
    "Change alarm mode",
    "Change time",
    "Exit",
};



long info_update_time = 500;
long old_millis = 0;

void menu(MIDDLE_LVL_STATE mid_lvl)
{
    print_options(options[(MIDDLE_LVL_STATE)mid_lvl]);
}

void print_options(char option[])
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(option);
}

void update_lcd_once(TOP_LVL_STATE top_state, MIDDLE_LVL_STATE mid_state)
{
    if (top_state == TOP_LVL_STATE::INFO)
    {
        lcd.clear();
    }
    else if (top_state == TOP_LVL_STATE::MENU)
    {
        //Serial.print(mid_state);
        menu(mid_state);
    }
    else if (top_state == TOP_LVL_STATE::SETTING)
    {
        //Serial.println(requested_color);
        setting(mid_state);
    }
}

void update_lcd(TOP_LVL_STATE top_state, MIDDLE_LVL_STATE mid_state)
{
    if (top_state == TOP_LVL_STATE::INFO)
    {        
        if (millis() > old_millis + info_update_time)
        {
            print_temp();
            print_time();
            old_millis = millis();
        }
    }
}

void setting(MIDDLE_LVL_STATE mid_lvl)
{
    //Serial.println(mid_lvl);
    switch (mid_lvl)
    {
        case MIDDLE_LVL_STATE::TEMPERATURE:
            //Serial.println("temp");
            print_setting_temp();
            break;
        case MIDDLE_LVL_STATE::COLOR:
            print_setting_color();
            break;
        case MIDDLE_LVL_STATE::MODE:
            print_setting_mode(); 
            break;
        case MIDDLE_LVL_STATE::ALARM:
            print_setting_alarm();
            break;
        case MIDDLE_LVL_STATE::TIME:
            print_setting_time();
        default:
            break;
    } 
}