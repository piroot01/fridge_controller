#pragma once

#include <modules/module.h>

static const int channel_A = 11;
static const int channel_B = 10;
static const int button_pin = 9;

struct Encoder_values
{
  bool button_state;
  int encoder_value;
};

extern Encoder_values encoder_values;

extern Encoder encoder;

void encoder_setup();

void read_encoder(Encoder_values& state);

bool button_change(Encoder_values& state);

bool encoder_change(Encoder_values& state);