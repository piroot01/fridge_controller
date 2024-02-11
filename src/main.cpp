#include <Arduino.h>
#include <Wire.h>
#include <time_print.h>
#include <temp_print.h>
#include <LiquidCrystal_I2C.h>
#include <menu.h>
#include <pins.h>
#include <menu_location.h>

extern bool button_state;
extern int menu_position;

long old_encoder_value = 0;
bool call_control = false;
bool button_rising = false;

void update_vars(bool button_state);
void display_control();

void setup () 
{
  pinMode(button, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();
  temp_setup();
  time_setup();
  state = State::INFO;
  Serial.begin(9600);
}

void loop () 
{
  button_state = !digitalRead(button);

  update_vars(button_state);
  display_control();
}

void update_vars(bool button_state)
{
  if (button_state == true and button_rising == false)
  {
    button_rising = true;
  }  
  if (button_state == false and button_rising == true and state == State::INFO)
  {
    lcd.clear();
    state = State::MENU;
    call_control = true;
    button_rising = false;
  }
  else if(button_state == false and button_rising == true and state == State::MENU and menu_position == 3)
  {
    lcd.clear();
    state = State::INFO;
    call_control = true;
    button_rising = false;
  }
  else if (button_state == false and button_rising == true)
  {
    button_rising = false;
  }

  position(menu_position);
}

void display_control()
{
  if (state == State::MENU)
  {
    menu();
  }
  if (state == State::INFO)
  {
    print_temp();
    print_time();
  }
}