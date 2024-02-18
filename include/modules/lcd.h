#pragma once

#include <modules/module.h>

extern LiquidCrystal_I2C lcd;

inline byte celsius[] = 
{
  0x0C,
  0x12,
  0x12,
  0x0C,
  0x00,
  0x00,
  0x00,
  0x00
};

void lcd_setup();