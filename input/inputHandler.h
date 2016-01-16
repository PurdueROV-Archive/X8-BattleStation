#pragma once
#include <QObject>
#include <QDebug>
#include <QStringList>
#include "SDL.h"
#include <vector>

class InputHandler : public QObject
{
	Q_OBJECT
public:
    //explicit InputHandler();
    void addJoystickAxis(char whichAxis[], void (*axisFunc[])(float));
    void addButtons(char buttons[], void (*buttonFunc[])(void));
    void handle();
    //~InputHandler();

private:
	std::vector<SDL_Joystick*> activeJoysticks;
};
