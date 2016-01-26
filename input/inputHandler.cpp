/**************************************************************************
InputHandler manages gamepad, mouse, and keyboard input.
It takes in vectors of function pointers and vectors of characters so we can map the functions to buttons (by mapping we mean, if you press a button 'a' it calls the function you assigned the button 'a' to)

As of 1/23/2016, for gamepad input, we have support for toggling, buttons, and axis. Still needs testing
As of 1/18/2016, I'm working on adding gamepad input. The code compiles and runs. It might work, but has yet been tested.
As of 1/16/2016, I'm working on adding gamepad input. It is currently not working yet.

#TO USE
Simply create an InputHandler object and vectors of the functions you plan on using.

There will be an order, for example, let's say you have 4 buttons, A, B, X, and Y.
A will map to the first function in the vector.
B will map to the second function in the vector, and so on.

Example:
typedef void(*buttonFunc)(void);//creating a typedef for easier use
std::vector<buttonFunc> myButtonFuncs = {punch, kick, dodge, slide};//your functions
//punch maps to button A, kick maps to button B, and so on...
InputHandler myInput;//creating the object
myInput.addButtons(myButtonFuncs);//adding the functions to object
myInput.handle();//start the loop
**************************************************************************/
#include "inputHandler.h"

/***********************************************************************
Axis functions have a function prototype of

void func(float input)

the input fed into your function will be the axis values.
************************************************************************/
void InputHandler::addJoystickAxis(std::vector<axisFunc> axisFunctions)
{
    this->axisFunctions = axisFunctions;
}
/***********************************************************************
Button functions have a function prototype of

void func(void)

We don't provide any input nor expect any outputs. We simply call the function when button is pressed.
************************************************************************/
void InputHandler::addButtons(std::vector<buttonFunc> buttonFunctions)
{
    this->buttonFunctions = buttonFunctions;
}

/***********************************************************************
Toggle (as in "turn on/off" buttons) functions have a function prototype of

void func(int)

The input fed into your function is the current state (we keep track of it for you). It is up to your function to check the current state and do what you need to do.
Do not put infinite while loops in your function please.
************************************************************************/
void InputHandler::addToggleButtons(std::vector<toggleFunc> toggleFunctions, std::vector<int> numStates)
{
    int toggleFunctionsSize = toggleFunctions.size();//I'll be using this in the for loop. Having a variable is faster than calling .size() multiple times
    if(toggleFunctionsSize!=numStates.size())//if the toggleFunc and numStates have mismatching numbers, we throw an exception
        throw "Error in addToggleButtons: togglingFunctions and numStates do not have the same number of elements in them\n";
    this->toggleFunctions = toggleFunctions;//assigning this class's toggleFunctions to input
    this->toggleNumStates = numStates;//assigning this class's numStates to input
    for(int i = 0; i < toggleFunctionsSize; i++)//initializing all current states to 0
        this->toggleCurrentStates.push_back(0);
}

InputHandler::InputHandler()
{
	//initialize the SDL library's joystick functions
	if(SDL_Init(SDL_INIT_JOYSTICK)<0)//if something goes wrong..
        throw SDL_GetError();
	SDL_JoystickEventState(SDL_ENABLE);//initialize SDL's event queue
	numJoysticks = 0;
	currentNumJoysticks = 0;
}

/***********************************************************************
handle() is in charge of everything. It reads everything in the SDL event queue, including gamepad input, keyboard input, and detecting plugging/unplugging of gamepads
************************************************************************/
void InputHandler::handle()
{
	SDL_PollEvent(&event);//grabs the most recent event from the event queue
	currentNumJoysticks = SDL_NumJoysticks();//checks if number of joysticks has changed
	if(event.type == SDL_JOYDEVICEADDED)
	{
		//add all the new joysticks to our vector
		for(int i = numJoysticks; i < currentNumJoysticks; ++i)//we have numJoysticks, there are currently currentNumJoysticks, so we go from num to currentNum to add all the joysticks that weren't there originally
			activeJoysticks.push_back(SDL_JoystickOpen(i));
		numJoysticks = currentNumJoysticks;
	}
	if(event.type == SDL_JOYDEVICEREMOVED)
	{
		//we have to iterate through the vector to see which one is closed and remove it
		for(int i = 0; i < numJoysticks; ++i)
		{
            //if(activeJoysticks[i]->closed > 0)
                //	activeJoysticks.erase(i);
            printf("don't know how to do remove\n");
		}
	}
//check for events
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
            case SDL_JOYBUTTONDOWN:
                this->buttonFunctions[event.jbutton.button]();
                break;
            case SDL_JOYAXISMOTION:
                this->axisFunctions[event.jaxis.axis](event.jaxis.value);
                break;
            case SDL_JOYBUTTONUP:
                //update state
                int button = event.jbutton.button;//makes the code cleaner to read (I'll be using it a lot)
                //updates state: currentState = currentState+1 % numStates
                this->toggleCurrentStates[button] = (this->toggleCurrentStates[button]+1)%(this->toggleNumStates[button]);
                this->toggleFunctions[button](this->toggleNumStates[button]);
                break;
		}
	}
}