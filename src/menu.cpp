#include <menu.h>

void menu(MIDDLE_LVL_STATE mid_lvl)
{
    print_options(options[(MIDDLE_LVL_STATE)mid_lvl]);
}

void print_options(const char* option)
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
        menu(mid_state);
    }
    else if (top_state == TOP_LVL_STATE::SETTING)
    {
        setting(mid_state);
    }
}

void update_lcd(TOP_LVL_STATE top_state, MIDDLE_LVL_STATE mid_state)
{
    static unsigned long old_millis = 0;

    if (top_state == TOP_LVL_STATE::INFO)
    {        
        if (millis() > old_millis + info_update_time)
        {
            print_temp();
            print_time();
            if (get_alarm())
            {
                print_alarm();
            }
            old_millis = millis();
        }
    }
}

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