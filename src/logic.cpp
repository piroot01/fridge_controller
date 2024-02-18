#include <logic.h>

TOP_LVL_STATE top_lvl = TOP_LVL_STATE::INFO;
MIDDLE_LVL_STATE mid_lvl = MIDDLE_LVL_STATE::TEMPERATURE;

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

void update_mid_lvl_enc(Encoder_values& state)
{
  if (top_lvl == TOP_LVL_STATE::MENU)
  {
    mid_lvl = (MIDDLE_LVL_STATE)crop_encoder(state, menu_size);
  }
}

void update_bot_lvl_btn(Encoder_values& state)
{
    static int button_counter_time = 0;
    
    if (top_lvl == TOP_LVL_STATE::SETTING)
    {
        switch (mid_lvl)
        {
        case MIDDLE_LVL_STATE::TIME:
            button_counter_time++;
            Serial.println(button_counter_time);
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