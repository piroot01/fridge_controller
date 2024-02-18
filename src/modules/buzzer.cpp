#include <modules/buzzer.h>

void buzzer_setup()
{
    pinMode(buzzer_pin, OUTPUT);
}

void buzz(unsigned long buzz_time)
{
    tone(buzzer_pin, buzzer_freq, buzz_time);
}

void alarm(bool flag)
{
    if (flag == true)
    {
        tone(buzzer_pin, alarm_freq);
    }
    else
    {
        noTone(buzzer_pin);
    }
}

void print_setting_alarm()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Choose alarm mode:");
    lcd.setCursor(0,2);
    lcd.print(alarm_modes[requested_alarm]);
}