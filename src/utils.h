#pragma once

#include <structs.h>
#include <Arduino.h>

int crop_encoder(Encoder_values& state, int encoder_range)
{
  int tmp_encoder_value = state.encoder_value;

  if (tmp_encoder_value < 0) 
  {
    tmp_encoder_value += 1000;
  }
  //Serial.println(tmp_encoder_value % encoder_range);
  return tmp_encoder_value % (encoder_range);
}