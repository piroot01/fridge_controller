#pragma once

#include <must_be_included.h>

#include <LiquidCrystal_I2C.h>
#include <menu.h>

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

LiquidCrystal_I2C lcd(0x27, 20, 4);

void lcd_setup()
{
    lcd.init();
    lcd.backlight();
}
