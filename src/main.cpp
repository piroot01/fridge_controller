#include <Arduino.h>
#include <Wire.h>
#include <display_init.h>
#include <menu.h>
#include <pins.h>
#include <temperature_change.h>
#include <Encoder.h>
#include <utils.h>
#include <structs.h>
#include <setting_data.h>
#include <color_change.h>

Encoder Enc(11, 10);

const int menu_size = 4;
const int temp_range = 11;
long old_encoder_value = 0;
bool call_control = false;
bool button_rising = false;
bool change_flag = false;
const int color_range = 12;

MIDDLE_LVL_STATE mid_lvl;
TOP_LVL_STATE top_lvl;

Encoder_values encoder_values = {false, 0};

bool button_change(Encoder_values& state);
void update_top_lvl(Encoder_values& state);
void update_mid_lvl_btn(Encoder_values& state);
void update_mid_lvl_enc(Encoder_values& state);
bool encoder_change(Encoder_values& state);
void update_bot_lvl(Encoder_values& state);

void setup () 
{
  pinMode(button, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();
  temp_setup();
  time_setup();
  led_setup();
  top_lvl = TOP_LVL_STATE::INFO;
  Serial.begin(9600);
}

void loop () 
{
  encoder_values.button_state = digitalRead(button);
  encoder_values.encoder_value = Enc.read() / 2;

  if (button_change(encoder_values))
  {
    update_top_lvl(encoder_values);
    update_mid_lvl_btn(encoder_values);
    change_flag = true;
  }
  if (encoder_change(encoder_values))
  {
    //Serial.println(encoder_values.encoder_value);
    update_mid_lvl_enc(encoder_values);
    update_bot_lvl(encoder_values);
    change_flag = true;
  }
  if (change_flag == true)
  {
    update_lcd_once(top_lvl, mid_lvl);
    change_flag = false;
  }

  update_lcd(top_lvl, mid_lvl);

}

bool button_change(Encoder_values& state)
{
  static bool button_rising = false;

  if (state.button_state == true)
  {
    button_rising = true;
  }
  if (state.button_state == false and button_rising == true)
  {
    button_rising = false;
    return true;
  }
  else
  {
    return false;
  }
}

void update_top_lvl(Encoder_values& state)
{
  switch (top_lvl)
  {
  case TOP_LVL_STATE::INFO:
    top_lvl = TOP_LVL_STATE::MENU;
    break;
  case TOP_LVL_STATE::MENU:
    if ((MIDDLE_LVL_STATE)crop_encoder(state, menu_size) == MIDDLE_LVL_STATE::EXIT)
    {
      top_lvl = TOP_LVL_STATE::INFO;
    }
    else
    {
      top_lvl = TOP_LVL_STATE::SETTING;
    }
    break;
  case TOP_LVL_STATE::SETTING:
    top_lvl = TOP_LVL_STATE::INFO;
    break;
  default:
    break;
  }
}

bool encoder_change(Encoder_values& state)
{
  static int old_encoder_value = 0;
  
  if (old_encoder_value != state.encoder_value)
  {
    old_encoder_value = state.encoder_value;
    return true;
  }
  else
  {
    return false;
  }
}

void update_mid_lvl_enc(Encoder_values& state)
{
  if (top_lvl == TOP_LVL_STATE::MENU)
  {
    mid_lvl = (MIDDLE_LVL_STATE)crop_encoder(state, menu_size);
  }
}

void update_mid_lvl_btn(Encoder_values& state)
{

}

void update_bot_lvl(Encoder_values& state)
{
  if (top_lvl == TOP_LVL_STATE::SETTING)
  {
    switch (mid_lvl)
    {
      case MIDDLE_LVL_STATE::TEMPERATURE:
        Serial.println(requested_color);
        requested_temp = crop_encoder(state, temp_range);
        break;
      case MIDDLE_LVL_STATE::COLOR:
        requested_color = crop_encoder(state, color_range);
        break;
      default:
        break;
    }
  }
}