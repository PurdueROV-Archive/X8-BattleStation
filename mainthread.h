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

#define TICK_INTERVAL 10

class Mainthread : public QObject
{
    Q_OBJECT


public:
    Mainthread(Joystick* joystick);
    ~Mainthread();

    bool start();
    void stop();

private slots:
    void tick();


private:
    QTimer* threadTimer;
    qint64 last_time;
    qint64 last_comms;
    UDPSocket* udp;
    Joystick* joystick;
    ThrustMapper* tmapper;
    bool velocitySlowDown;

};

#endif // MAINTHREAD_H
