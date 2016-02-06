#ifndef SDL_H
#define SDL_H

#include <QtGlobal>
#include <QStringList>
#include "SDL.h"
#undef main

class SdlWrap
{

public:
    static bool init();
    static QString getError();
    static QStringList getJoystickList();
    static int getNumJoysticks();
    static QString getJoystickName(int index);
    static bool ready();

private:
    static bool initialized;
    static QStringList deviceList;

};

#endif // SDL_H
