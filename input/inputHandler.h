#pragma once
#include <QObject>
#include <QDebug>
#include <QStringList>
#undef main//bc SDL defines main and causes an error
#include "SDL.h"
#undef main//bc SDL defines main and causes an error
#include "joystick.h"
#include <vector>

class InputHandler : public QObject
{
    Q_OBJECT//needed for Qt framework
public:
    explicit InputHandler();
    void addJoystickAxis(int whichJoystick, std::vector<axisFunc> axisFunctions);//maps the functions to axis
    void addButtons(int whichJoystick, std::vector<buttonFunc> buttonFunctions);//maps the functions to buttons
    void addToggleButtons(int whichJoystick, std::vector<toggleFunc> toggleFunctions, std::vector<int> numStates);
    void handle();//initializes and runs main event loop
private:
    std::vector<Joystick> activeJoysticks;//vector of active joysticks
    int numJoysticks;
    int currentNumJoysticks;
    SDL_Event event;
};
