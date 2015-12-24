/*
Input Handler handles the Joysticks, mouse, and keyboard input.
To use: simply create an InputHandler object and call inputHandler.handle()
Example:
InputHandler myInput = new InputHandler();
myInput.handle();
*/
#include "inputHandler.h"
#include <stdio.h>

int main()
{
    InputHandler inputHandler;
	inputHandler.listAvailableGamepads();
	inputHandler.handle();
	return 0;
}

InputHandler::InputHandler()
{
	SDL_Init(SDL_INIT_JOYSTICK);
	this->initGamepads();
}
/***************
Checks SDL event queue for new events
	if there is a new event, emit the right signal
Also checks if a Joystick has been unplugged or plugged
****************/
bool InputHandler::handle()
{
	SDL_Event event;
	int numJoy = SDL_NumJoysticks();
	while(true)
	{
		if(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_JOYAXISMOTION:
					printf("Axis motion detected\n");
					break;
				case SDL_JOYBALLMOTION:
					printf("Joy ball motion detected\n");
					break;
				case SDL_JOYHATMOTION:
					printf("Joy hat motion detected\n");
					break;
				case SDL_JOYBUTTONUP:
					printf("Button up detected\n");
					break;
				case SDL_JOYBUTTONDOWN:
					printf("Button down detected\n");
					break;
			}
		}
		if(SDL_NumJoysticks()>numJoy)
		{
			numJoy = SDL_NumJoysticks();
            this->addGamepad(SDL_NumJoysticks()-1);
		}
		if(SDL_NumJoysticks()<numJoy)
		{
			numJoy = SDL_NumJoysticks();
			for(int i = 0; i < numJoy; i++)
			{
                if(!SDL_JoystickOpened(i))
					connectedGamepads.erase(i);
			}
		}
	}
	return true;
}

bool InputHandler::addGamepad(int id)
{
	Gamepad newJoystick = new Gamepad(SDL_JoystickOpen(id));
	connectedGamepads.push_back(newJoystick);
}

bool InputHandler::initGamepads()
{
	int numJoysticks = SDL_NumJoysticks();
	if(numJoysticks>0)
	{
		SDL_Joystick Joysticks[] = new int[numJoysticks];
		for(int i = 0; i < numJoysticks; i++)
		{
			Joysticks[i] = SDL_JoystickOpen(i);
			printf("ID: %d\n", i);
			printf("Name: %s\n", SDL_JoystickName(i));
			printf("Number of Axes: %d\n", SDL_JoystickNumAxes(i));
			printf("Number of Buttons: %d\n", SDL_JoystickNumButtons(i));
			printf("Number of Balls: %d\n", SDL_JoystickNumBalls(i));
		}
	}
	else
		printf("No Joysticks connected to this computer\n");
	for(int i = 0; i < numJoysticks; i++)
		SDL_JoystickClose(Joysticks[i]);	
}

bool InputHandler::listAvailableGamepads()
{
	int numJoysticks = SDL_NumJoysticks();
	if(numJoysticks>0)
	{
		SDL_Joystick Joysticks[] = new int[numJoysticks];
		for(int i = 0; i < numJoysticks; i++)
		{
			Joysticks[i] = SDL_JoystickOpen(i);
			printf("ID: %d\n", i);
			printf("Name: %s\n", SDL_JoystickName(i));
			printf("Number of Axes: %d\n", SDL_JoystickNumAxes(i));
			printf("Number of Buttons: %d\n", SDL_JoystickNumButtons(i));
			printf("Number of Balls: %d\n", SDL_JoystickNumBalls(i));
		}
	}
	else
		printf("No Joysticks connected to this computer\n");
	for(int i = 0; i < numJoysticks; i++)
		SDL_JoystickClose(Joysticks[i]);
}

InputHandler::~InputHandler()
{
	int numJoysticks = SDL_NumJoysticks();
	for(int i = 0; i < numJoysticks; i++)
	{
		SDL_JoystickClose(Joysticks[i]);
		delete connectedGamepads.get(i);
	}
}
