#include "joystick.h"

void Joystick::axis(int index, float val)
{
    this->keyMapping->axis(index, val);
}

void Joystick::button(int index)
{
    this->keyMapping->button(index);
}

void Joystick::toggle(int index)
{
    this->keyMapping->toggle(index);
}
Joystick::Joystick(SDL_Joystick* joystick, keyMapping keyMapping)
{
    this->joystick = joystick;
    this->keyMapping = keyMapping;
}
