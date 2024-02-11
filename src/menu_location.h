#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <Encoder.h>

const int menu_size =  4;
int menu_position;
long old_value = -999;
long encoder_value = 0;
extern bool call_control;
bool encoder_control = false;

 Encoder Enc(11, 10);

void position(int& location) 
{
  encoder_value = Enc.read() / 2;

  if (encoder_value != old_value)
  {
    encoder_control = true;
    old_value = encoder_value;
    if (encoder_value < 0) 
    {
      encoder_value += 1000;
    }
    location = encoder_value % (menu_size);
  }
}