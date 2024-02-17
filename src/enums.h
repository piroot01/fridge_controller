// distribuce do jednotlivych moduku
#pragma once

// do main.h
enum TOP_LVL_STATE
{
    INFO, MENU, SETTING
};

// do main.h
enum MIDDLE_LVL_STATE
{
    TEMPERATURE, COLOR, MODE, ALARM, TIME, EXIT
};

// do modules/strip.h
enum STRIP_MODES
{
    ON, OFF, AUTO
};

// do modules/rtc.h
enum SET_TIME
{
    HOUR, MINUTE
};
