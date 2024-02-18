#include <modules/strip.h>

CRGB* ledsRGB = (CRGB*) &leds[0];

void strip_setup()
{
    FastLED.addLeds<WS2812B, strip_pin, RGB>(ledsRGB, getRGBWsize(num_leds));
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
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Choose color:");
    lcd.setCursor(0,2);
    lcd.print(color_names[requested_color]);
}

void rainbow()
{
	static unsigned short hue;

	for(int i = 0; i < num_leds; i++){
		leds[i] = CHSV((i * 256 / num_leds) + hue, 255, 255);
	}
	FastLED.show();
	hue++;
}

void print_setting_mode()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Choose strip mode:");
    lcd.setCursor(0,2);
    lcd.print(strip_modes[requested_mode]);
}

void color_control()
{
    if (requested_color == 11)
    {
        rainbow();
    }
    else
    {
        change_color(colors[requested_color]);
    }
}