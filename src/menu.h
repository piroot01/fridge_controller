#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <menu_location.h>
#include <pins.h>

void menu();
void menu_control();
void print_options(char option[]);

bool button_state = false;

enum State
{
    INFO, MENU
};

State state;

char opt1[] = "Change temperature";
char opt2[] = "Change LED color";
char opt3[] = "Change LED mode";
char opt4[] = "Exit";

void menu()
{
    //position(menu_position);
    if (encoder_control == true)
    {
        lcd.clear();
        Serial.println(menu_position);
        switch (menu_position)
        {
            case 0:
                print_options(opt1);
                break;
            case 1:
                print_options(opt2);
                break;
            case 2:
                print_options(opt3);
                break;
            case 3:         
                print_options(opt4);
                break;
        }
        encoder_control = false;
    }
}

void menu_control(bool menu_active)
{
  if (menu_active == true)
  {
    menu();
  }
  else if (menu_active == false)
  {

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