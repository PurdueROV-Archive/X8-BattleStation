/**************************************************************************
InputHandler manages gamepad, mouse, and keyboard input.
It takes in vectors of function pointers and vectors of characters so we can map the functions to buttons (by mapping we mean, if you press a button 'a' it calls the function you assigned the button 'a' to)

To do:
0. Initialize vectors to maxSize of controllers for each controller (different controllers have different values and stuff)
1. How do you specify which function goes to which button?
2. Does typedef transfer in header files? (so we don't need to call typedef for function pointers)
3. Clean up code (easier to read), make it easier to use, document (e.g. supports Xbox One controllers, Rockcandy..)
4. Mapping? (how do we see which kind of controller we have?) (https://github.com/kripken/emscripten/issues/2193 for XBox One mapping)
5. Read .txt file?
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

InputHandler::InputHandler()
{
	//initialize the SDL library's joystick functions
	if(SDL_Init(SDL_INIT_JOYSTICK)<0)//if something goes wrong..
        throw SDL_GetError();
	SDL_JoystickEventState(SDL_ENABLE);//initialize SDL's event queue
	numJoysticks = 0;
	currentNumJoysticks = 0;
}

void InputHandler::put(KeyMapping map)
{
    if(keyMappings.find(map.getJoystickType()) == keyMappings.end())
    {
        keyMappings.insert(make_pair(map.getJoystickType(),map));
    }
    else
    {
        keyMappings.erase(map.getJoystickType());
        keyMappings.insert(make_pair(map.getJoystickType(),map));
    }
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
        {
            SDL_Joystick* joystick = SDL_JoystickOpen(i);
            //check what type it is
            const char* name = SDL_JoystickName(joystick);
            QString Qname(name);
            //create Joystick object based on the name
            Joystick joy = Joystick(joystick, &(keyMappings.at(Qname)));
            activeJoysticks.push_back(joy);
        }
		numJoysticks = currentNumJoysticks;
	}
	if(event.type == SDL_JOYDEVICEREMOVED)
	{
		//we have to iterate through the vector to see which one is closed and remove it
		for(int i = 0; i < numJoysticks; ++i)
            printf("don't know how to do remove\n");
	}
//check for events
	while(SDL_PollEvent(&event))//while there are events in the event queue that still need to be processed
	{
		switch(event.type)
		{
            case SDL_JOYBUTTONDOWN:
                qDebug() << "Index requested" << (int)(event.jaxis.axis);
                this->activeJoysticks[event.jbutton.which].button(event.jbutton.button);
                break;
            case SDL_JOYAXISMOTION:
                qDebug() << "Index requested" << (int)(event.jaxis.axis);
                this->activeJoysticks[event.jaxis.which].axis(event.jaxis.axis, event.jaxis.value);
                break;
            case SDL_JOYBUTTONUP:
                this->activeJoysticks[event.jbutton.which].toggle(event.jbutton.button);
                break;
		}
	}
}
