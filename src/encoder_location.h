#pragma once
// #include <Arduino.h>
// #include <Wire.h>
// #include <Encoder.h>
// #include <enums.h>

// long old_value = -999;
// long encoder_value = 0;
// extern bool call_control;
// bool encoder_control = false;

// void menu_position(Menu_state& location, int encoder_range) 
// {
//   encoder_value = Enc.read() / 2;

//   if (encoder_value != old_value)
//   {
//     encoder_control = true;
//     old_value = encoder_value;
//     if (encoder_value < 0) 
//     {
//       encoder_value += 1000;
//     }
//     location = (Menu_state)(encoder_value % (encoder_range));
//   }
// }

// void setting_temperature(int& location, int encoder_range) 
// {
//   encoder_value = Enc.read() / 2;

//   if (encoder_value != old_value)
//   {
//     encoder_control = true;
//     old_value = encoder_value;
//     if (encoder_value < 0) 
//     {
//       encoder_value += 1000;
//     }
//     location = (encoder_value % (encoder_range));
//   }
// }