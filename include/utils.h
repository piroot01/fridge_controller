#pragma once

#include <must_be_included.h>


inline int crop_encoder(Encoder_values& state, int encoder_range)
{
  int tmp_encoder_value = state.encoder_value;

  if (tmp_encoder_value < 0) 
  {
    tmp_encoder_value += 1000;
  }
  return tmp_encoder_value % (encoder_range);
}