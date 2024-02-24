#include <pid.h>

double set_point = 0;
double input = 0;
bool output = 0;

AutoPIDRelay pid(&input, &set_point, &output, pulse_width, KP, KI, KD);

void pid_setup()
{
    set_point = 30.0;
    pid.setBangBang(4);
    pid.setTimeStep(4000);
}

void update_set_temp(const double temp)
{
    set_point = temp;
}

void pid_loop()
{
    if (get_alarm())
    {
        update_set_temp(requested_temp);
        input = get_temp();
        pid.run();
        digitalWrite(relay_pin, !output);
    }
    else
    {
        pid.stop();
        digitalWrite(relay_pin, output);
    }
}