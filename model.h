#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QDateTime>

#include "mainthread.h"
#include "controller.h"
#include "controlpacket.h"
#include "joystick.h"

class Model : public QObject
{
    Q_OBJECT

public:
    Model();
    ~Model();

    void init();

private:
    bool running;

    Joystick* joystick1;
    Joystick* joystick2;

    Controller* controller;
    Mainthread* mainthread;

    QThread* qThread;

public slots:
    void refreshList();
    void selectJoystick1(int index);
    void start();
    void stop();

};

#endif // MODEL_H
