#include <modules/thermistor.h>

void thermistor_setup()
{
    pinMode(thermistor_pin, INPUT);
}

void print_temp()
{               
    lcd.setCursor(7,3);
    lcd.print(get_temp(), 1);
    lcd.setCursor(12,3);
    lcd.write((byte)0);
    lcd.setCursor(13,3);
    lcd.print("C");
}

float get_temp()
{
    float VRT = analogRead(thermistor_pin);              
    VRT  = (5.00 / 1023.00) * VRT;      
    float VR = VCC - VRT;
    float RT = VRT / (VR / R);               

    float ln = log(RT / RT0);
    float TX = (1 / ((ln / B) + (1 / T0))); 

    return TX - 273.15;     
}

void print_setting_temp()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Choose temperature:");
    lcd.setCursor(0,2);
    lcd.print(5 + requested_temp);
    lcd.setCursor(2,2);
    lcd.write((byte)0);
    lcd.setCursor(3,2);
    lcd.print("C");
}