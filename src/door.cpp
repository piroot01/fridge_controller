#include <door.h>

bool magnet_logic()
{
    static bool open_flag = false;
    
    if (get_magnet())
    {
        open_flag = true;
        if (millis() - prev_mag_state_buzzer > interval_buzzer)
        {
            buzz_flag = true;
            prev_mag_state_buzzer = millis();
        }
        return true;
    }
    else if (!get_magnet() and open_flag == true)
    {
        buzz_flag = false;
        if (millis() - prev_mag_state_strip > interval_strip)
        {
            prev_mag_state_strip = millis();
            open_flag = false;
            return false;
        }
        else
        {
            return true;
        }
    }
    return false;
}

void mode_control(STRIP_MODES mode)
{
    switch (mode)
    {
        case STRIP_MODES::ON:
            color_control();
            break;
        case STRIP_MODES::AUTO:
            if (magnet_logic())
            {
                color_control();
            }
            else
            {
                change_color(CRGB::Black);
            }
            break;
        case STRIP_MODES::OFF:
            change_color(CRGB::Black);
            break;
        default:
            break;
    }
}