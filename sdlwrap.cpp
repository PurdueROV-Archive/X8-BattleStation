#include "sdlwrap.h"

bool SdlWrap::initialized = false;
QStringList SdlWrap::deviceList;

bool SdlWrap::init() {
    if (initialized == true) return true;

    if (SDL_Init(SDL_INIT_JOYSTICK) == 0) {
        SDL_JoystickUpdate();
        initialized = true;
    } else {
        initialized = false;
    }

    return initialized;
}

QString SdlWrap::getError() {
    return QString(SDL_GetError());
}


QStringList SdlWrap::getJoystickList() {
    if (!initialized) {
        deviceList.clear();
        return deviceList;
    }

    SDL_JoystickUpdate();

    deviceList.clear();


    int len = SdlWrap::getNumJoysticks();
    if (len == 0) {
        deviceList.append(" ");
    }

    for(int i = 0; i < len; i++) {
        QString info = QString(SDL_JoystickNameForIndex(i));
        if (!info.isEmpty()) {
            deviceList.append(info);
        }
    }

    return deviceList;
}

int SdlWrap::getNumJoysticks() {
    if (!initialized) return 0;

    return SDL_NumJoysticks();
}

QString SdlWrap::getJoystickName(int index) {
    if (!initialized) return 0;
    if (index < 0 || index >= SdlWrap::getNumJoysticks()) return "";

    return QString(SDL_JoystickNameForIndex(index));
}

bool SdlWrap::ready() {
    return initialized;
}
