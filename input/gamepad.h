#pragma once
#include <QObject>
#include <QDebug>
#include <QStringList>
#include "SDL.h"
#undef main//SDL defines a main, so we have to undefine it to prevent conflicts

class Gamepad : public QObject
{
    Q_OBJECT
public:
    explicit Gamepad(int id);//creates Gamepad object + connects it to a gamepad
    bool connect(int id);//connects this gamepad object to a gamepad
    bool disconnect();//disconnects this gamepad object from any gamepad
    //bool setFunctionality(Config config);//
    ~Gamepad();
private:
};
