#pragma once
#undef main//bc SDL defines main and causes an error
#include "SDL.h"
#undef main//bc SDL defines main and causes an error
#include <vector>
#include <QString>

using namespace std;
//function pointers
typedef void (*axisFunc)(float);//to make function pointers work with vectors
typedef void (*buttonFunc)(void);
typedef void (*toggleFunc)(int);

/*defining the mappings for XBoxOne*/
enum XBoxOne
{
	//number of buttons
	NUMBUTTONS = 15;
	NUMAXES = 6;
	//buttons
	DPadUp = 0;
	DPadDown = 1;
	DPadLeft = 2;
	DPadRight = 3;
	Start = 4;
	Select = 5;
	L3 = 6;
	R3 = 7;
	LB = 8;
	RB = 9;
	A = 10;
	B = 11;
	X = 12;
	Y = 13;
	Home = 14;
	//axes
	LT = 0;
	RT = 1;
	LJoy = 2;
	RJoy = 3;
} typedef XBoxOne;

class KeyMapping
{
public:
	explicit KeyMapping(QString joystickType);
	void map(int button, buttonFunc func);
	void map(int button, axisFunc func);
	void map(int button, toggleFunc func, numStates);
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
	static QString XBoxOne = "XInput Controller #1";
};