#pragma once
#include <QObject>
#include <QDebug>
#include <QStringList>
#include "SDL.h"
#undef main//bc SDL defines main and causes an error
#include <vector>

class InputHandler : public QObject
{
    Q_OBJECT//needed for Qt framework
    typedef void (*axisFunc)(float);//to make function pointers work with vectors
    typedef void (*buttonFunc)(void);
    typedef void (*toggleFunc)(int);
public:
    explicit InputHandler();
    void addJoystickAxis(std::vector<axisFunc> axisFunctions);//maps the functions to axis
    void addButtons(std::vector<buttonFunc> buttonFunctions);//maps the functions to buttons
    void addToggleButtons(std::vector<toggleFunc> toggleFunctions, std::vector<int> numStates);
    void handle();//initializes and runs main event loop
    //~InputHandler();

private:
    std::vector<SDL_Joystick*> activeJoysticks;//vector of active joysticks
    std::vector<axisFunc> axisFunctions;//vector of functions mapped to axes
    std::vector<buttonFunc> buttonFunctions;//vector of functions mapped to buttons
    std::vector<toggleFunc> toggleFunctions;//vector of functions mapped to buttons that toggle
    std::vector<int> toggleNumStates;//vector of number of possible states that match toggleFunctions
    std::vector<int> toggleCurrentStates;//vector that keeps track of the current state that each toggleFunction is at. Initializes with int = 0
    int numJoysticks;
    int currentNumJoysticks;
    SDL_Event event;
};
