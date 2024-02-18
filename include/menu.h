#pragma once

#include <must_be_included.h>

inline const char* options[menu_size] = 
{
    "Change temperature",
    "Change LED color",
    "Change LED mode",
    "Change alarm mode",
    "Change time",
    "Exit",
};

static const long info_update_time = 500;

void menu(MIDDLE_LVL_STATE mid_lvl);

void print_options(const char* option);

void update_lcd_once(TOP_LVL_STATE top_state, MIDDLE_LVL_STATE mid_state);

void update_lcd(TOP_LVL_STATE top_state, MIDDLE_LVL_STATE mid_state);

void setting(MIDDLE_LVL_STATE mid_lvl);