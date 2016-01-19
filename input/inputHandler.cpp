/**************************************************************************
Input Handler manages gamepad, mouse, and keyboard input.

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

/*Place holder functions.
 *
 * Axis functions have a prototype of void func(float input) bc they will need the axis values
 * Button functions have a prototype of void func(void) bc they just get called when pressed
 */

void rotateFunc(float rotate)
{
    printf("rotate by %f\n", rotate);
}

void walkFunc(float rotate)
{
    printf("walk by %f\n", rotate);
}

void punch()
{
    printf("Punch!");
}

void kick()
{
    printf("Kick!");
}

void dodge()
{
    printf("dodge!?");
}
void slide()
{
    printf("sliiiiide!");
}
void climbUp()
{
    printf("climbed up");
}

void climbDown()
{
    printf("climed down..");
}

void climbLeft()
{
    printf("climbing left");
}

void climbRight()
{
    printf("climbing right");
}
/*
int main(void)
{
    typedef void(*axisFunc)(float);
    typedef void(*buttonFunc)(void);
    std::vector<axisFunc> myAxisFuncs = {rotateFunc, walkFunc};
    std::vector<buttonFunc> myButtonFuncs = {punch, kick, dodge, slide, climbUp, climbDown, climbLeft, climbRight};
    InputHandler myInput;
    myInput.addJoystickAxis(myAxisFuncs);
    myInput.addButtons(myButtonFuncs);
    myInput.handle();
    return 1;
}*/

void InputHandler::addJoystickAxis(std::vector<axisFunc> axisFunctions)
{
    this->axisFunctions = axisFunctions;
}

void InputHandler::addButtons(std::vector<buttonFunc> buttonFunctions)
{
    this->buttonFunctions = buttonFunctions;
}

void InputHandler::handle()
{
	//initialize the SDL library's joystick functions
	if(SDL_Init(SDL_INIT_JOYSTICK)<0)//if something goes wrong..
		printf("Couldn't initialize SDL Joystick: %s\n", SDL_GetError());
	SDL_JoystickEventState(SDL_ENABLE);//initialize SDL's event queue
	SDL_Event event;
	int numJoysticks = 0;
	int currentNumJoysticks = 0;
	while(true)
	{
		SDL_PollEvent(&event);
		currentNumJoysticks = SDL_NumJoysticks();
		if(event.type == SDL_JOYDEVICEADDED)
		{
			//add all the new joysticks to our vector
			for(int i = numJoysticks; i < currentNumJoysticks; ++i)
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
			}
		}
	}
}
