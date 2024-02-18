#pragma once

#include <modules/module.h>
#include <modules/rgbw.h>
#include <modules/lcd.h>
#include <modules/colors.h>

static const int num_leds = 30;
static const unsigned int brightness = 128;
static const int strip_pin = A2;

enum STRIP_MODES
{
    ON, OFF, AUTO
};

inline const char* strip_modes[3] = 
{
    "Always ON",
    "Always OFF",
    "Auto",
};

extern STRIP_MODES mode;

static CRGBW leds[num_leds];
extern CRGB* ledsRGB;

void strip_setup();

void change_color(CRGB color);

void print_setting_color();

void rainbow();

void print_setting_mode();

void color_control();