#include "joystick.h"

Joystick::Joystick() : QObject() {
    connected = false;
    joystickId = -1;
    if (SdlWrap::ready() == false) {
        SdlWrap::init();
    }
}

bool Joystick::select(int index) {
    if (index < 0 || index >= SdlWrap::getNumJoysticks()) return false;

    joystickId = index;
    joystickName = SdlWrap::getJoystickName(index);
    return true;
}

bool Joystick::connect() {
    if (joystickId < 0 || joystickId >= SdlWrap::getNumJoysticks()) return false;

    sdlJoystick = SDL_JoystickOpen(joystickId);
    if (sdlJoystick == NULL) {
        connected = false;
        return connected;
    }

    SDL_JoystickUpdate();

    axes.clear();
    axesZero.clear();
    buttons.clear();

    numAxes = getNumAxes();
    numButtons = getNumButtons();

    for (int i = 0; i < numAxes; i++) {
        axes.append(0);
    }

    for (int i = 0; i < numAxes; i++) {
        int threshold = 5000;
        qint16 axisOffset = SDL_JoystickGetAxis(sdlJoystick, i);
        if (axisOffset < threshold && axisOffset > -threshold) {
            axesZero.append(-axisOffset);
        } else {
            axesZero.append(0);
        }
    }


    for (int i = 0; i < numButtons; i++) {
        ButtonState state;
        state.lastState = false;
        state.currentState = false;
        buttons.append(state);
    }

    connected = true;
    return connected;
}

void Joystick::disconnect() {
    connected = false;
    if (sdlJoystick) SDL_JoystickClose(sdlJoystick);
}

bool Joystick::isConnected() {
    return connected;
}

Joystick::~Joystick() {
    if (sdlJoystick) SDL_JoystickClose(sdlJoystick);
    connected = false;
}

int Joystick::getNumAxes() {
    return SDL_JoystickNumAxes(sdlJoystick);
}

int Joystick::getNumButtons() {
    return SDL_JoystickNumButtons(sdlJoystick);
}

bool Joystick::getButtonState(int buttonId) {
   if (buttonId < 0 || buttonId >= numButtons) return false;

    return buttons.at(buttonId).currentState;
}

bool Joystick::getButtonPressed(int buttonId) {
    if (buttonId < 0 || buttonId >= numButtons) return false;

    ButtonState button = buttons.at(buttonId);
    return (!button.lastState && button.currentState);
}

bool Joystick::getButtonReleased(int buttonId) {
    if (buttonId < 0 || buttonId >= numButtons) return false;

    ButtonState button = buttons.at(buttonId);
    return (button.lastState && !button.currentState);
}

qint16 Joystick::getAxis(int axisId) {
    if (axisId < 0 || axisId >= numAxes) return 0;
    qint32 value =  axes.at(axisId) + axesZero.at(axisId);

    if (abs(value) < 400) value = 0;

    if (axisId == JOYSTICK_LJ_Y || axisId == JOYSTICK_RJ_Y) {
        value *= -1;
    }

    if (value > INT_16_MAX) value = INT_16_MAX;
    if (value < INT_16_MIN) value = INT_16_MIN;

    return (qint16) value;
}

void Joystick::update() {
    SDL_JoystickUpdate();

    for (int i = 0; i < numButtons; i++) {
        ButtonState state;
        state.lastState = buttons.at(i).currentState;
        state.currentState = SDL_JoystickGetButton(sdlJoystick, i);

        buttons[i] = state;
    }

    for (int i = 0; i < numAxes; i++) {
        qint16 axisValue = SDL_JoystickGetAxis(sdlJoystick, i);
        axes[i] = axisValue;
    }
}
