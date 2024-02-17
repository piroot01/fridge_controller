// presunout do modules/rtc.h
#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <RtcDS1302.h>
#include <display_init.h>
#include <enums.h>
#include <setting_data.h>

ThreeWire myWire(4,3,2); //io, sclk, ce
RtcDS1302<ThreeWire> Rtc(myWire);
void printDateTime(const RtcDateTime& dt);

void time_setup();
void print_time();
void print_dash();

SET_TIME time_state;

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
  
  if (dash_aviable == true)
  {
    lcd.setCursor(6,0);
    lcd.print("--------");
    lcd.setCursor(6,2);
    lcd.print("--------");
    dash_aviable = false;
  }
}

void print_setting_time()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Choose new time:");
  lcd.setCursor(0,2);
  lcd.print("hh:mm: ");
  lcd.setCursor(6,2);
  lcd.print(requested_time_hour);
  lcd.setCursor(8,2);
  lcd.print(":");
  lcd.setCursor(9,2);
  lcd.print(requested_time_minute);
  if (time_state == SET_TIME::HOUR)
  {
    lcd.setCursor(0,3);
    lcd.print("^^   ");
  }
  else
  {
    lcd.setCursor(0,3);
    lcd.print("   ^^");
  }
}


void set_time(int hours, int minutes)
{
  RtcDateTime new_time = RtcDateTime(2024, 2, 16, hours, minutes, 0);
  Rtc.SetDateTime(new_time);
}
