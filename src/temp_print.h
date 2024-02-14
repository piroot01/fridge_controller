#include <Arduino.h>
#include <Wire.h>
#include <display_init.h>
#include <bytes.h>

#define RT0 10000   // Ω
#define B 3977      //  K
#define VCC 5    //Supply  voltage
#define R 10000 //R=10KΩ

//Variables
float RT, VR, ln, TX,  T0, VRT;

void temp_setup();
void print_temp();

void temp_setup()
{
  T0 = 25 + 273.15;  
  pinMode(A1,INPUT);
  lcd.createChar(0, celsius);
}

void print_temp()
{
  VRT = analogRead(A1);              //Acquisition analog value of VRT
  VRT  = (5.00 / 1023.00) * VRT;      //Conversion to voltage
  VR = VCC - VRT;
  RT = VRT / (VR / R);               //Resistance of RT

  ln = log(RT / RT0);
  TX = (1 / ((ln / B) + (1 / T0))); //Temperature from thermistor

  TX =  TX - 273.15;                 //Conversion to Celsius
  lcd.setCursor(7,3);
  lcd.print(TX, 1);
  lcd.setCursor(12,3);
  lcd.write((byte)0);
  lcd.setCursor(13,3);
  lcd.print("C");
}