#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <display_init.h>
#include <enums.h>
#include <temp_print.h>
#include <time_print.h>

void menu();
void print_options(char option[]);
void update_lcd_once(TOP_LVL_STATE top_state, MIDDLE_LVL_STATE mid_state);
void update_lcd(TOP_LVL_STATE top_state, MIDDLE_LVL_STATE mid_state);

char opt1[] = "Change temperature";
char opt2[] = "Change LED color";
char opt3[] = "Change LED mode";
char opt4[] = "Exit";

void menu(MIDDLE_LVL_STATE mid_lvl)
{
    switch (mid_lvl)
    {
        case MIDDLE_LVL_STATE::TEMPERATURE:
            print_options(opt1);
            break;
        case MIDDLE_LVL_STATE::COLOR:
            print_options(opt2);
            break;
        case MIDDLE_LVL_STATE::MODE:
            print_options(opt3);
            break;
        case MIDDLE_LVL_STATE::EXIT:         
            print_options(opt4);
            break;
    }
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
        Serial.print(mid_state);
        menu(mid_state);
    }
}

void update_lcd(TOP_LVL_STATE top_state, MIDDLE_LVL_STATE mid_state)
{
    if (top_state == TOP_LVL_STATE::INFO)
    {
        print_temp();
        print_time();
    }
    else if (top_state == TOP_LVL_STATE::MENU)
    {
        //nic
    }
}