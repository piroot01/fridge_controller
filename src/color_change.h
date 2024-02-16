#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <FastLED.h>
#include <rgbw.h>
#include <colors.h>
#include <setting_data.h>

const int num_leds = 30;
const unsigned int brightness = 128;
const int data_pin = A2;

void print_setting_color();

CRGBW leds[num_leds];
CRGB *ledsRGB = (CRGB *) &leds[0];

void led_setup()
{
    FastLED.addLeds<WS2812B, data_pin, RGB>(ledsRGB, getRGBWsize(num_leds));
	FastLED.setBrightness(brightness);
	FastLED.show();
}

void change_color(CRGB color)
{
    for (int i = 0; i < num_leds; i++)
    {
        leds[i] = color;
    }
    FastLED.show();
}

void print_setting_color()
{
    //Serial.println(requested_temp);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Choose color:");
    lcd.setCursor(0,2);
    lcd.print(color_names[requested_color]);
}

void rainbow(){
	static unsigned short hue;

	for(int i = 0; i < num_leds; i++){
		leds[i] = CHSV((i * 256 / num_leds) + hue, 255, 255);
	}
	FastLED.show();
	hue++;
}

void color_control()
{
    if (requested_color == 11)
    {
        //Serial.println(requested_color);
        rainbow();
    }
    else
    {
        change_color(colors[requested_color]);
    }
}