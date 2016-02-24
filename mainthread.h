#ifndef MAINTHREAD_H
#define MAINTHREAD_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QDateTime>

#include "udpsocket.h"
#include "joystick.h"
#include "controlpacket.h"
#include "thrust_mapping/matrices.h"
#include "thrust_mapping/thrust_mapper.h"

#define TICK_INTERVAL 500

class Mainthread : public QObject
{
    Q_OBJECT


public:
    Mainthread(Joystick* joystick1);
    ~Mainthread();

    bool start();
    void stop();

private slots:
    void tick();


private:
    QTimer* threadTimer;
    qint64 lastTime;
    UDPSocket* udp;
    Joystick* joystick1;
    ThrustMapper* thrustMapper;
};

#endif // MAINTHREAD_H
