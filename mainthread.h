#ifndef MAINTHREAD_H
#define MAINTHREAD_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QDateTime>

#include "udpsocket.h"

#define TICK_INTERVAL 1000

class Mainthread : public QObject
{
    Q_OBJECT


public:
    Mainthread();
    ~Mainthread();

    bool start();
    void stop();

private slots:
    void tick();


private:
    QTimer* threadTimer;
    qint64 lastTime;
    UDPSocket* udp;

};

#endif // MAINTHREAD_H
