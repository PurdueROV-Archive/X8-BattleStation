#pragma once
#include <QObject>
#include <QDebug>
#include <QStringList>
#include "SDL.h"
#undef main
#include <vector>

class InputHandler : public QObject
{
	Q_OBJECT
    typedef void (*axisFunc)(float);
    typedef void (*buttonFunc)(void);
public:
    //explicit InputHandler();
    void addJoystickAxis(std::vector<axisFunc> axisFunctions);
    void addButtons(std::vector<buttonFunc> buttonFunctions);
    void handle();
    //~InputHandler();

private:
	std::vector<SDL_Joystick*> activeJoysticks;
    std::vector<axisFunc> axisFunctions;
    std::vector<buttonFunc> buttonFunctions;
};
