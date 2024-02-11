#include <Arduino.h>
#include <Wire.h>
#include <RtcDS1302.h>
#include <LiquidCrystal_I2C.h>

ThreeWire myWire(4,2,3);
RtcDS1302<ThreeWire> Rtc(myWire);
void printDateTime(const RtcDateTime& dt);

LiquidCrystal_I2C lcd(0x27, 20, 4);

void time_setup();
void print_time();
void print_dash();

#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt)
{
    char datestring[13];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u:%02u:%02u"),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    lcd.setCursor(6,1);
    lcd.print(datestring);
}

void time_setup()
{
  Rtc.Begin();

  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  printDateTime(compiled);
  compiled += 22;
  Rtc.SetDateTime(compiled);
}

void print_time()
{
  
  RtcDateTime now = Rtc.GetDateTime();
  print_dash();
  printDateTime(now);
}

void print_dash()
{
  bool dash_aviable = true;
  
  if (dash_aviable = true)
  {
    lcd.setCursor(6,0);
    lcd.print("--------");
    lcd.setCursor(6,2);
    lcd.print("--------");
    dash_aviable = false;
  }
}