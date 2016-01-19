/**************************************************************************
Input Handler manages gamepad, mouse, and keyboard input.

As of 1/16/2016, I'm working on adding gamepad input. It is currently not working yet.

#TO USE
Simply create an InputHandler object, add the mapping of buttons or axis to functions, and then call handle

Example:
char[] axis = {'l','r'};
void (*axisFuncs[])(float) = {rotateFunc, walkFunc};
char[] buttons = {'a','b','x','y','u','d','l','r'};
void (*buttonFuncs[])(void) = {punch, kick, dodge, slide, climbUp, climbDown, climbLeft, climbRight};
InputHandler myInput = new InputHandler();
myInput.addJoystickAxis(axis, axisFuncs);
myInput.addButtons(buttons, buttonsFuncs);
myInput.handle();
**************************************************************************/
#include "inputHandler.h"

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
