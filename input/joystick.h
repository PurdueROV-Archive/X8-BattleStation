#pragma once
#include "SDL.h"
#undef main//bc SDL defines main and causes an error
#include "KeyMapping.h"

class Joystick
{
public:
    explicit Joystick(SDL_Joystick* joystick);
    void axis(int index, float val);
    void button(int index);
    void toggle(int index);
private:
    SDL_Joystick* joystick;
    KeyMapping* keyMapping;
};