#include <Arduino.h>
#include <Wire.h>
#include <FastLED.h>

#define LED_AMMOUNT 30
#define DATA_PIN A2
#define LED_TYPE WS2812B
#define BRIGHTNESS 255
#define SATURATION 255

CRGB leds[LED_AMMOUNT];

void led_setup()
{
    FastLED.addLeds<LED_TYPE, DATA_PIN>(leds, LED_AMMOUNT);
}

void change_color()
{
    for (int i; i < LED_AMMOUNT; i++)
    {
    }

    FastLED.show();
}