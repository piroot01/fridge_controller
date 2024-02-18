#include <modules/encoder.h>

Encoder_values encoder_values = {false, 0};

Encoder encoder(channel_A, channel_B);

void encoder_setup()
{
    pinMode(button_pin, INPUT_PULLUP);
}

void read_encoder(Encoder_values& state)
{
    encoder_values.button_state = digitalRead(button_pin);
    encoder_values.encoder_value = encoder.read() / 2;
}

bool button_change(Encoder_values& state)
{
    static bool button_rising = false;

    if (state.button_state == true)
    {
        button_rising = true;
    }
    if (state.button_state == false and button_rising == true)
    {
        button_rising = false;
        return true;
    }
    else
    {
        return false;
    }
}

bool encoder_change(Encoder_values& state)
{
    static int old_encoder_value = 0;
    
    if (old_encoder_value != state.encoder_value)
    {
        old_encoder_value = state.encoder_value;
        return true;
    }
    else
    {
        return false;
    }
}