#include <modules/alarm.h>

void alarm_setup()
{
    pinMode(alarm_pin, INPUT);
}

bool get_alarm()
{
    if (digitalRead(alarm_pin))
    {
        return true;
    }
    return false;
}

void print_alarm()
{
    lcd.setCursor(14,3);
    lcd.print("Alarm!");
}

