// prejmenovat na lcd_logic.h

#pragma once

/* tady bude pouze
#include <must_be_included.h>
#include <setting_data.h>

to je vse
*/

#include <Arduino.h>
#include <Wire.h>
#include <display_init.h>
// enums rozhodit do jednotivych modulu
#include <enums.h>
#include <thermistor.h>
#include <time.h>
#include <temperature_change.h>
// color_change + strip_mode pujde do modulu strip.h
#include <color_change.h>
#include <setting_data.h>
#include <strip_mode.h>


// neni treba
void menu(MIDDLE_LVL_STATE mid_lvl);
void print_options(char option[]);
void update_lcd_once(TOP_LVL_STATE top_state, MIDDLE_LVL_STATE mid_state);
void update_lcd(TOP_LVL_STATE top_state, MIDDLE_LVL_STATE mid_state);
void setting(MIDDLE_LVL_STATE mid_lvl);

// consts.h
const int menu_size = 6;

// menu.h
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

// menu.h
void menu(MIDDLE_LVL_STATE mid_lvl)
{
    print_options(options[(MIDDLE_LVL_STATE)mid_lvl]);
}

// menu.h
void print_options(char option[])
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(option);
}

// menu_logic.h
void update_lcd_once(TOP_LVL_STATE top_state, MIDDLE_LVL_STATE mid_state)
{
    if (top_state == TOP_LVL_STATE::INFO)
    {
        lcd.clear();
    }
    else if (top_state == TOP_LVL_STATE::MENU)
    {
        menu(mid_state);
    }
    else if (top_state == TOP_LVL_STATE::SETTING)
    {
        setting(mid_state);
    }
}

// menu_logic.h
void update_lcd(TOP_LVL_STATE top_state, MIDDLE_LVL_STATE mid_state)
{
    if (top_state == TOP_LVL_STATE::INFO)
    {        
        if (millis() > old_millis + info_update_time)
        {
            // print_info() do menu.h
            print_temp();
            print_time();
            old_millis = millis();
        }
    }
}

// menu_logic.h
void setting(MIDDLE_LVL_STATE mid_lvl)
{
    switch (mid_lvl)
    {
        case MIDDLE_LVL_STATE::TEMPERATURE:
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
