/* do must_be_included.h bych dal zakladni include files

// foundation
#include <Arduino.h>
#include <Wire.h>

// modules

// magnet
#include <modules/magnet.h>
// rotary encoder
#include <modules/rotary_encoder.h>
// thermistor
#include <modules/thermistor.h>
// rgb strip
#include <modules/strip.h>
// lcd
#include <modules/lcd.h>
// buzzer
#include <modules/buzzer.h>
// rtc
#include <modules/rtc.h>
// relay
#include <modules/realay.h>



*/

// vytvoril bych main.h

#include <Arduino.h>
#include <Wire.h>
#include <display_init.h>
#include <menu.h>
// pins.h rozdelid do jednotlivych modulu
#include <pins.h>
#include <temperature_change.h>
#include <Encoder.h>
#include <utils.h>
#include <structs.h>
#include <setting_data.h>
#include <color_change.h>
#include <buzzer.h>
#include <pid.h>
#include <magnet.h>

// do modules/rotary_encoder.h
Encoder Enc(11, 10);

// vsechny konstanty do consts.h
const int temp_range = 11;
// neni treba long
long old_encoder_value = 0;
bool call_control = false;
bool button_rising = false;
bool change_flag = false;
const int color_range = 12;
const int mode_range = 3;
const int alarm_range = 2;
const int hour_range = 24;
const int minute_range = 60;
int button_counter_time = 0;

MIDDLE_LVL_STATE mid_lvl;
TOP_LVL_STATE top_lvl;

// do rotary_encoder.h
Encoder_values encoder_values = {false, 0};


// do main.h
bool button_change(Encoder_values& state);
void update_top_lvl(Encoder_values& state);
void update_mid_lvl_btn(Encoder_values& state);
void update_mid_lvl_enc(Encoder_values& state);
bool encoder_change(Encoder_values& state);
void update_bot_lvl_enc(Encoder_values& state);
void update_bot_lvl_btn(Encoder_values& state);

void setup () 
{
  // modules/rotary_encoder.h
  pinMode(button, INPUT_PULLUP);

  // modules/lcd.h
  //lcd_setup();
  lcd.init();
  lcd.backlight();
  // thermistor_setup();
  temp_setup();
  // rtc_setup();
  time_setup();
  // strip_setup();
  led_setup();
  // nice
  buzzer_setup();

  // pid nebude soucasti modulu
  // relay_setup();
  pid_setup();

  top_lvl = TOP_LVL_STATE::INFO;
  // nuke
  Serial.begin(9600);
}

void loop () 
{
  // mozna bych dal do funkce read_rotary_encoder() v modules/rotary_encoder.h
  encoder_values.button_state = digitalRead(button);
  encoder_values.encoder_value = Enc.read() / 2;

  if (button_change(encoder_values))
  {
    update_top_lvl(encoder_values);
    update_mid_lvl_btn(encoder_values);
    update_bot_lvl_btn(encoder_values);
    // 50 bude konstanta button_buzz_time v consts.h
    buzz(50);
    change_flag = true;
  }
  if (encoder_change(encoder_values))
  {
    //Serial.println(encoder_values.encoder_value);
    update_mid_lvl_enc(encoder_values);
    update_bot_lvl_enc(encoder_values);
    change_flag = true;
    // 50 bude konstanta ecoder_buzz_time consts.h
    buzz(50);
  }
  if (change_flag == true)
  {
    // vsechno do edne funkce do_if_change()
    update_lcd_once(top_lvl, mid_lvl);
    change_color(colors[requested_color]);
    change_flag = false;
  }

  // vsechno do jedne funkce do()
  pid_loop();
  mode_control((STRIP_MODES)requested_mode);
  change_alarm();
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
    if (mid_lvl != MIDDLE_LVL_STATE::TIME)
    {
      top_lvl = TOP_LVL_STATE::INFO;
    }
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

// okey useless
void update_mid_lvl_btn(Encoder_values& state)
{

}

void update_bot_lvl_btn(Encoder_values& state)
{
  if (top_lvl == TOP_LVL_STATE::SETTING)
  {
    switch (mid_lvl)
    {
      case MIDDLE_LVL_STATE::TIME:
        button_counter_time++;
        //Serial.println(button_counter_time);
        if (button_counter_time == 1)
        {
          time_state = SET_TIME::HOUR;
        }
        else if (button_counter_time == 2)
        {
          time_state = SET_TIME::MINUTE;
        }
        else
        {
          button_counter_time = 0;
          set_time(requested_time_hour, requested_time_minute);
          top_lvl = TOP_LVL_STATE::INFO;
        }
        break;
      default:
        break;
    }
  }
}

void update_bot_lvl_enc(Encoder_values& state)
{
  if (top_lvl == TOP_LVL_STATE::SETTING)
  {
    switch (mid_lvl)
    {
      case MIDDLE_LVL_STATE::TEMPERATURE:
        requested_temp = crop_encoder(state, temp_range);
        break;
      case MIDDLE_LVL_STATE::COLOR:
        requested_color = crop_encoder(state, color_range);
        break;
      case MIDDLE_LVL_STATE::MODE:
        requested_mode = crop_encoder(state, mode_range);
        break;
      case MIDDLE_LVL_STATE::ALARM:
        requested_alarm = crop_encoder(state, alarm_range);
      case MIDDLE_LVL_STATE::TIME:
        if (time_state == SET_TIME::HOUR)
        {
          requested_time_hour = crop_encoder(state, hour_range);
        }
        else if (time_state == SET_TIME::MINUTE)
        {
          requested_time_minute = crop_encoder(state, minute_range);
        }
        break;
      default:
        break;
    }
  }
}
