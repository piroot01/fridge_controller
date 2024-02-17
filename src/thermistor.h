// presunout do modules/thermistor.h
#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <display_init.h>
#include <bytes.h>
#include <pins.h>

#define RT0 10000   // Ω
#define B 3977      //  K
#define VCC 5    //Supply  voltage
const int R = 10000; //R=10KΩ

//Variables
float RT, VR, ln, TX,  T0, VRT;

void temp_setup();
void print_temp();
float get_temp();

void temp_setup()
{
  T0 = 25 + 273.15;  
  pinMode(A1,INPUT);
  lcd.createChar(0, celsius);
}

void print_temp()
{               
  lcd.setCursor(7,3);
  lcd.print(get_temp(), 1);
  lcd.setCursor(12,3);
  lcd.write((byte)0);
  lcd.setCursor(13,3);
  lcd.print("C");
}

float get_temp()
{
  VRT = analogRead(thermistor);              
  VRT  = (5.00 / 1023.00) * VRT;      
  VR = VCC - VRT;
  RT = VRT / (VR / R);               

  ln = log(RT / RT0);
  TX = (1 / ((ln / B) + (1 / T0))); 

  return TX - 273.15;     
}
