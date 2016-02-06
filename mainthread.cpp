#include "mainthread.h"

Mainthread::Mainthread(Joystick *joystick1) : QObject() {

    //TODO: Pass in other needed objects

    threadTimer = new QTimer(0);
    threadTimer->setTimerType(Qt::PreciseTimer);
    threadTimer->setInterval(TICK_INTERVAL);

    lastTime = 0;

    this->joystick1 = joystick1;

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
    udp->initSocket("192.168.1.100", 5100);

    return true;
}


//Stop the mainthread
void Mainthread::stop() {
    threadTimer->stop();
    udp->closeSocket();

    //closing stuff here
}


//Called after TICK_INTERVAL milliseconds
//main while loop where it ticks every 10ms
void Mainthread::tick() {
    qint64 now = QDateTime::currentMSecsSinceEpoch();
    //qDebug() << now-lastTime;

    ControlPacket* cp = new ControlPacket();
    //cp->print();

    udp->send(cp->getPacket());
    QByteArray returnData = udp->read();

    if (returnData.size() > 0) {
        for (int i = 0; i < 30; ++i) {
            qDebug("[%d]: %c", i, (quint8) returnData.at(i));
        }
    }


    lastTime = now;

    //TODO: Add code for each tick
}
