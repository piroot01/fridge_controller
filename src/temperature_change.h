#include <Arduino.h>
#include <Wire.h>
#include <display_init.h>
#include <encoder_location.h>

int requested_temp;
const int temp_range = 11;
bool print_control = true;

byte celsius[] = {
  0x0C,
  0x12,
  0x12,
  0x0C,
  0x00,
  0x00,
  0x00,
  0x00
};

void change_temperature();

void change_temperature()
{
    //setting_temperature(requested_temp, temp_range);

    if (print_control == true)
    {
        lcd.clear();
        lcd.createChar(0, celsius);
        lcd.setCursor(0,0);
        lcd.print("Choose new");
        lcd.setCursor(0,1);
        lcd.print("temperature: ");
        lcd.setCursor(15,1);
        lcd.write((byte)0);
        lcd.setCursor(16,1);
        lcd.print("C");
        print_control = false;
    }

    lcd.setCursor(13,1);
    lcd.print(requested_temp);
    Serial.println(requested_temp);
}