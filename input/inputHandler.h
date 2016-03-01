#pragma once//header guards for most modern C/C++ compilers
#include <QObject>
#include <QDebug>
#include <QStringList>
#undef main//bc SDL defines main and causes an error
#include "SDL.h"
#undef main//bc SDL defines main and causes an error
#include "joystick.h"
#include "KeyMapping.h"
#include <vector>
#include <map>

using namespace std;

/*
InputHandler is the main input handler. It looks at what buttons were pressed and calls the functions that the buttons are supposed to execute

HOW TO USE:
1) Create a new InputHandler object

InputHandler input = InputHandler();

2)Create some key mapping (look at KeyMapping.h) and add it to the InputHandler. It now knows what buttons execute what functions

input.put(myKeyMapping);

3)Call the function handle() in your main while loop and it'll handle everything for you

while(true)
{
    input.handle();
}
*/

class InputHandler : public QObject
{
    Q_OBJECT//needed for Qt framework
public:
    //constructor, initializes the SDL library and sets controller input up
    explicit InputHandler();
    //puts a Button->Function map into InputHandler. When a new controller is added, we'll check if it has a mapping and assign the controls to that mapping
    void put(KeyMapping map);
    //this is the main loop for reading input
    void handle();
private:
    //vector of active joysticks. Used to check which joystick was called and execute the function mapping asosciated with that joystick
    vector<Joystick> activeJoysticks;
    //a map of all possible key maps (e.g. "Manipulator" maps the button X to a function that closes the claw)
    map<QString, KeyMapping> keyMappings;
    //these two integers are for checking for new joysticks plugged in/joysticks removed
    int numJoysticks;
    int currentNumJoysticks;
    //for checking the event queue from SDL so we can see which buttons were pressed
    SDL_Event event;
};
