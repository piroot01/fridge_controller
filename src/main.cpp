#include <Arduino.h>
#include <Wire.h>
#include <time_print.h>
#include <temp_print.h>
#include <LiquidCrystal_I2C.h>
#include <menu.h>
#include <pins.h>


// lepsi pridat, pokud beres promennou button_state z menu.h, pokud to je teda dobre
// extern bool button_state;

bool clear = true;
long old_encoder_value = 0;

void clear_lcd();

void setup () 
{
  pinMode(button, INPUT_PULLUP);

  // do lcd_setup();
  lcd.init();
  lcd.backlight();
  temp_setup();
  time_setup();
}

void loop () 
{
  // nadekalrovany v menu.h?
  button_state = !digitalRead(button);

  if (button_state == true)
  {
    menu_active = true;
    // clear_lcd by melo clearovat display nezavisle na promenne clear
    clear_lcd();
    // dal bych do separatni funkce, ktera se bude rozhodovat na zaklade menu_active
    menu();
  }

  if (menu_active == false)
  {
    print_temp();
    print_time();
  }

  // vycitani z encoderu do funkce, ktera nastavi hodnotu menu_active
  long curr = Enc.read();

  if(old_encoder_value != curr and menu_active)
  {
    old_encoder_value = curr;
    // opet resi jina funkce
    menu();
  }

}


// BS code
void clear_lcd()
{
  if (clear == true)
  {
    lcd.clear();
    clear = false;
  }
  else
  {
    clear = false;
  }
}
