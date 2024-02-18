#pragma once

#include <must_be_included.h>
#include <requested.h>
#include <utils.h>

enum TOP_LVL_STATE
{
    INFO, MENU, SETTING
};

enum MIDDLE_LVL_STATE
{
    TEMPERATURE, COLOR, MODE, ALARM, TIME, EXIT
};

extern TOP_LVL_STATE top_lvl;
extern MIDDLE_LVL_STATE mid_lvl;

void update_top_lvl(Encoder_values& state);

void update_mid_lvl_enc(Encoder_values& state);

void update_bot_lvl_enc(Encoder_values& state);

void update_bot_lvl_btn(Encoder_values& state);