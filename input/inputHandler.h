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
    void addJoystickAxis(void (*axisFunc[])(float));
    void addButtons(void (*buttonFunc[])(void));
    void handle();
    //~InputHandler();

private:
	std::vector<SDL_Joystick*> activeJoysticks;
    void (**axisFunc)(float);
    void (**buttonFunc)(void);
};
