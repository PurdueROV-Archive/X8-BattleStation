#pragma once//header guard for modern C/C++ compilers
#undef main//bc SDL defines main and causes an error
#include "SDL.h"
#undef main//bc SDL defines main and causes an error
#include <vector>
#include <QString>
#include <qDebug>

using namespace std;
//These are function pointers. KeyMapping takes functions as one of its inputs so we can call it when the right button is pressed
//These are the only formats we support
typedef void (*axisFunc)(float);//for axes, they return void and take in a float (the float will be the rotation values)
typedef void (*buttonFunc)(void);//for buttons, they return void and take in nothing
typedef void (*toggleFunc)(int);//for switches (turning something on/off), they return void and take in an int (the int being the current state (e.g. 0 = off; 1 = on)). Your function has to define the states and handle them yourself

/*defining the mappings for XBoxOne*/
enum XBoxOne
{
	//number of buttons
    NUMBUTTONS = 15,
    NUMAXES = 6,
	//buttons
    DPadUp = 0,
    DPadDown = 1,
    DPadLeft = 2,
    DPadRight = 3,
    Start = 4,
    Select = 5,
    L3 = 6,
    R3 = 7,
    LB = 8,
    RB = 9,
    A = 10,
    B = 11,
    X = 12,
    Y = 13,
    Home = 14,
	//axes
    LT = 0,
    RT = 1,
    LJoy = 2,
    RJoy = 3,
} typedef XBoxOne;

class KeyMapping
{
public:
    //Constructor. Takes in a QString which is the name of the joystick
    explicit KeyMapping(QString joystickType);
    //maps a button (refer to the enums above) to a function
	void map(int button, buttonFunc func);
	void map(int button, axisFunc func);
    void map(int button, toggleFunc func, int numStates);
    //executes a function based on the button
	void axis(int index, float val);
	void button(int index);
	void toggle(int index);
	QString getJoystickType();
private:
	std::vector<axisFunc> axisFunctions;//vector of functions mapped to axes
	std::vector<buttonFunc> buttonFunctions;//vector of functions mapped to buttons
	std::vector<toggleFunc> toggleFunctions;//vector of functions mapped to buttons that toggle
	std::vector<int> toggleNumStates;//vector of number of possible states that match toggleFunctions
	std::vector<int> toggleCurrentStates;//vector that keeps track of the current state that each toggleFunction is at. Initializes with = 0	
	QString joystickType;	
    QString XBoxOneID = "XInput Controller #1";
};
