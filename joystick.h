#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QObject>
#include <QDebug>
#include <QStringList>
#include "sdlwrap.h"
#include "SDL.h"
#undef main

#define INT_16_MAX 32767
#define INT_16_MIN -32768


#define JOYSTICK_A 10
#define JOYSTICK_B 11
#define JOYSTICK_X 12
#define JOYSTICK_Y 13

#define JOYSTICK_DP_UP 0
#define JOYSTICK_DP_DOWN 1
#define JOYSTICK_DP_LEFT 2
#define JOYSTICK_DP_RIGHT 3

#define JOYSTICK_LJ_X 0
#define JOYSTICK_LJ_Y 1
#define JOYSTICK_RJ_X 2
#define JOYSTICK_RJ_Y 3

#define JOYSTICK_L3 6
#define JOYSTICK_R3 7



#define JOYSTICK_LEFTBUTTON 8
#define JOYSTICK_RIGHTBUTTON 9
#define JOYSTICK_LTRIGG 4
#define JOYSTICK_RTRIGG 5

#define JOYSTICK_BACK 5
#define JOYSTICK_START 4
#define JOYSTICK_HOME 14


struct ButtonState {
    bool lastState;
    bool currentState;
};


class Joystick : public QObject
{
    Q_OBJECT

public:
    explicit Joystick();
    ~Joystick();

    bool select(int index);
    bool connect();

    void disconnect();

    bool isConnected();

    int getNumAxes();
    int getNumButtons();

    bool getButtonState(int buttonId);

    bool getButtonPressed(int buttonId);
    bool getButtonReleased(int buttonId);

    qint16 getAxis(int axisId);

    void update();


private:
    bool connected;

    int numAxes;
    int numButtons;

    QList<ButtonState> buttons;

    QList<qint16> axes;
    QList<qint16> axesZero;

    QString joystickName;

    int joystickId;
    SDL_Joystick* sdlJoystick;

signals:

public slots:

};

#endif // JOYSTICK_H
