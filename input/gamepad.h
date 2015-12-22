#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <QObject>
#include <QDebug>
#include <QStringList>
#include "SDL.h"
#undef main//SDL defines a main, so we have to undefine to prevent conflicts

class Gamepad : public QObject
{
    Q_OBJECT
public:
    //constructors and destructors
    explicit Gamepad();
    ~Gamepad();
    //functions for (de)selecting/connecting gamepads
    bool connect(int id);//connects this gamepad object to whatever gamepad was selected
    bool disconnect();//disconnects this gamepad object from any gamepad
    //functions for getting information (including states) about gamepads

    //function for specifying functionality.
    //NOTE TO SELF: (maybe update to take in functors instead?)
    bool setFunctionality(void* (func()));//Takes an array of function pointers and assigns buttons to it.
    //Index 0 = A, 1 = B, 2 = X, 3 = Y, 4 = LB, 5 = RB, 6 = LT, 7 = RT, 8 = Center

    bool setFunctionality(char** buttons, void*(func()));//Takes an array of function pointers and assigns it to the button specified in the string array
    //if the size of the arrsys are different, or if something goes wrong, will return false


private:


};

#endif
