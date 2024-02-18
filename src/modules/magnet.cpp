#include <modules/magnet.h>

void magnet_setup()
{
    pinMode(magnet, INPUT);
}

bool get_magnet()
{
    return (analogRead(magnet) > threshold)? true:false;
}

void change_alarm()
{
    if (requested_alarm == 1)
    {
        alarm(buzz_flag);
    }
}