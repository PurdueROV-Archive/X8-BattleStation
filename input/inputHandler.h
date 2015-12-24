#pragma once
#include <QObject>
#include <QDebug>
#include <QStringList>
#include "SDL.h"
#include <vector>
#include "gamepad.h"

class InputHandler : public QObject
{
	Q_OBJECT
public:
	explicit InputHandler();
	bool addGamepad(int id);//adds a gamepad (as in make it usable in the BattleStation)
	bool listAvailableGamepads();//lists available gamepads connected to the computer
    bool handle();//constantly polls for events
	~InputHandler();

private:
    bool initGamepads();
	std::vector<Gamepad> connectedGamepads;
	std::vector<int> availableGamepads;
    //std::vector<std::vector<>> availableConfigs;
};
