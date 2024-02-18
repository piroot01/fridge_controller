#include <main.h>

bool change_flag = false;

void do_if_change()
{
  update_lcd_once(top_lvl, mid_lvl);
  change_color(colors[requested_color]);
}

void do_looply()
{
  pid_loop();
  mode_control((STRIP_MODES)requested_mode);
  change_alarm();
  update_lcd(top_lvl, mid_lvl);
}

void setup () 
{
  buzzer_setup();
  encoder_setup();
  lcd_setup();
  magnet_setup();
  relay_setup();
  rtc_setup();
  strip_setup();
  thermistor_setup();

  pid_setup();
}

void loop () 
{
  read_encoder(encoder_values);

  if (button_change(encoder_values))
  {
    update_top_lvl(encoder_values);
    update_bot_lvl_btn(encoder_values);
    buzz(50);
    change_flag = true;
  }
  if (encoder_change(encoder_values))
  {
    update_mid_lvl_enc(encoder_values);
    update_bot_lvl_enc(encoder_values);
    change_flag = true;
    buzz(50);
  }
  if (change_flag == true)
  {
    do_if_change();
    change_flag = false;
  }
  do_looply();
}