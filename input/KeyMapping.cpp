#include "KeyMapping.h"

void KeyMapping::map(int button, axisFunc func)
{
	if(button > axisFunctions.size())
	{
        qDebug() << "Invalid axis assigned. There are only " << axisFunctions.size() << "axes, but you tried assigning " << button<< endl;
		return;
	}
    axisFunctions[button] = func;
}

void KeyMapping::map(int button, buttonFunc func)
{
	if(button > buttonFunctions.size())
	{
        qDebug() << "Invalid button assigned. There are only " << buttonFunctions.size() << "buttons, but you tried assigning " << button<< endl;
		return;
	}
    buttonFunctions[button] = func;
}

void KeyMapping::map(int button, toggleFunc func, int numStates)
{
	if(button > buttonFunctions.size())
	{
        qDebug() << "Invalid button assigned. There are only " << buttonFunctions.size() << "buttons, but you tried assigning " << button<< endl;
		return;
	}	
    toggleFunctions[button] = func;
    toggleNumStates[button] = numStates;
}

void KeyMapping::axis(int index, float val)
{
    this->axisFunctions[index](val);
}

void KeyMapping::button(int index)
{
    this->buttonFunctions[index]();
}

void KeyMapping::toggle(int index)
{
    //update state (which is just state = (state+1)%maxStates)
    this->toggleCurrentStates[index] = (this->toggleCurrentStates[index]+1)%(this->toggleNumStates[index]);
    //call function
    this->toggleFunctions[index](this->toggleNumStates[index]);
}

QString KeyMapping::getJoystickType()
{
	return this->joystickType;
}

KeyMapping::KeyMapping(QString joystickType)
{
	//check	which joystick it is and based on that, define the size of vectors
	this->joystickType = joystickType;
    if(joystickType == XBoxOneID)
	{
        axisFunctions.resize(XBoxOne::NUMAXES);
        buttonFunctions.resize(XBoxOne::NUMBUTTONS);
        toggleFunctions.resize(XBoxOne::NUMBUTTONS);
        toggleNumStates.resize(XBoxOne::NUMBUTTONS);
        toggleCurrentStates.resize(XBoxOne::NUMBUTTONS, 0);
	}
}
