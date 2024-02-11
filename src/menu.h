#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <menu_location.h>
#include <pins.h>

void menu();
void print_options(char option[]);

bool option_button = false;
bool menu_active = false;

char opt1[] = "Change temperature";
char opt2[] = "Change LED color";
char opt3[] = "Change LED mode";
char opt4[] = "Exit";

void menu()
{
    position(menu_position);
    option_button = digitalRead(button);

    switch (menu_position)
    {
        case 0:
            print_options(opt1);
            break;
        case 1:
            print_options(opt2);
            if (option_button == true)
            {
                
            }
            break;
        case 2:
            print_options(opt3);
            break;
        case 3:
            print_options(opt4);
            if (option_button == true)
            {
                menu_active = false;
            }
            break;
    }
}

void print_options(char option[])
{
    static long old_pos = 0;
    static unsigned long last_update = 0;
    static unsigned long debounce_delay = 100;
    
    long new_pos = Enc.read();

    if (old_pos != new_pos and millis() - last_update > debounce_delay)
    {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(option);
        old_pos = new_pos;
        last_update = millis();
    }
}