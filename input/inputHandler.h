#pragma once
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

class InputHandler : public QObject
{
    using namespace std;
    Q_OBJECT//needed for Qt framework
public:
    explicit InputHandler();
    void put(KeyMapping map);
    void handle();//initializes and runs main event loop
private:
    vector<Joystick> activeJoysticks;//vector of active joysticks
    map<QString, KeyMapping> keyMappings;
    int numJoysticks;
    int currentNumJoysticks;
    SDL_Event event;
};
