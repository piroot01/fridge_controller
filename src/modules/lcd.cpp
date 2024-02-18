#include <modules/lcd.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

void lcd_setup()
{
    lcd.init();
    lcd.backlight();
    lcd.createChar(0, celsius);
}