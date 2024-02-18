#include <modules/rtc.h>

ThreeWire wire(io_pin, sclk_pin, ce_pin);

RtcDS1302<ThreeWire> rtc(wire);

SET_TIME time_state = SET_TIME::HOUR;

void print_date_time(const RtcDateTime& dt)
{
    char datestring[13];

    snprintf_P(datestring, 
            sizeof(datestring) / sizeof(datestring[0]),
            PSTR("%02u:%02u:%02u"),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    lcd.setCursor(6,1);
    lcd.print(datestring);
}

void rtc_setup()
{
  rtc.Begin();
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  print_date_time(compiled);
  compiled += time_delay;
  rtc.SetDateTime(compiled);
}

void print_time()
{
  
  RtcDateTime now = rtc.GetDateTime();
  print_dash();
  print_date_time(now);
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
  rtc.SetDateTime(new_time);
}