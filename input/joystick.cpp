#include "joystick.h"

void Joystick::addJoystickAxis(std::vector<axisFunc> axisFunctions)
{
    int length = axisFunctions.size();
    this->axisFunctions = axisFunctions;
}

void Joystick::addButtons(std::vector<buttonFunc> buttonFunctions)
{
    this->buttonFunctions = buttonFunctions;
}

void Joystick::addToggleButtons(std::vector<toggleFunc> toggleFunctions, std::vector<int> numStates)
{
    int toggleFunctionsSize = toggleFunctions.size();//I'll be using this in the for loop. Having a variable is faster than calling .size() multiple times
    if(toggleFunctionsSize!=numStates.size())//if the toggleFunc and numStates have mismatching numbers, we throw an exception
        throw "Error in addToggleButtons: togglingFunctions and numStates do not have the same number of elements in them\n";
    this->toggleFunctions = toggleFunctions;//assigning this class's toggleFunctions to input
    this->toggleNumStates = numStates;//assigning this class's numStates to input
    for(int i = 0; i < toggleFunctionsSize; i++)//initializing all current states to 0
        this->toggleCurrentStates.push_back(0);    
}

void Joystick::axis(int index, float val)
{
    this->axisFunctions[index](val);
}

void Joystick::button(int index)
{
    this->buttonFunctions[index]();
}

void Joystick::toggle(int index)
{
    //update state (which is just state = (state+1)%maxStates)
    this->toggleCurrentStates[index] = (this->toggleCurrentStates[index]+1)%(this->toggleNumStates[index]);
    //call function
    this->toggleFunctions[index](this->toggleNumStates[index]);
}
Joystick::Joystick(SDL_Joystick* joystick)
{
    this->joystick = joystick;
    int numButtons = SDL_JoystickNumButtons(joystick);
    int numAxes = SDL_JoystickNumAxes(joystick);
    qDebug() << "numButtons = " << numButtons;
    qDebug() << "numAxes = " << numAxes;
    this->axisFunctions = std::vector<axisFunc>(numAxes);
    this->buttonFunctions = std::vector<buttonFunc>(numButtons);
    this->toggleFunctions = std::vector<toggleFunc>(numButtons);
    this->toggleNumStates = std::vector<int>(numButtons);
    this->toggleCurrentStates = std::vector<int>(numButtons);
}
