#include <Arduino.h>
#include <Wire.h>
#include <Encoder.h>

const int menu_size =  4;
int menu_position;

 Encoder Enc(11, 10);

void position(int location) 
{
  long encoder_value = Enc.read() / 2;
  if (encoder_value < 0) 
  {
    encoder_value += 1000;
  }
  location = encoder_value % (menu_size);

  switch(location)
  {
    case 0:
      menu_position = 0;
      break;
    case 1:
      menu_position = 1;
      break;
    case 2:
      menu_position = 2;
      break;
    case 3:
      menu_position = 3;
      break;
  }
}