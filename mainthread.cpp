#include "mainthread.h"

Mainthread::Mainthread() : QObject() {

    //TODO: Pass in other needed objects

    threadTimer = new QTimer(0);
    threadTimer->setTimerType(Qt::PreciseTimer);
    threadTimer->setInterval(TICK_INTERVAL);

    lastTime = 0;

    //Connect thredTimer timeout to tick slot
    connect(threadTimer, SIGNAL(timeout()), SLOT(tick()), Qt::DirectConnection);
}

Mainthread::~Mainthread() {
    if (threadTimer) {
        threadTimer->stop();
        delete threadTimer;
    }
}

//Start the main thread
bool Mainthread::start() {

    //TODO: Check if joysticks are connected, can connet to microcontroller, etc
    threadTimer->start();
    //initialize stuff here

    udp = new UDPSocket();
    udp->initSocket(QHostAddress::LocalHost, 53456);

    return true;
}


//Stop the mainthread
void Mainthread::stop() {
    threadTimer->stop();
    //closing stuff here
}


//Called after TICK_INTERVAL milliseconds
//main while loop where it ticks every 10ms
void Mainthread::tick() {
    qint64 now = QDateTime::currentMSecsSinceEpoch();
    qDebug() << now-lastTime;

    udp->send(QByteArray("Data"));
    udp->read();

    lastTime = now;

    //TODO: Add code for each tick
}
