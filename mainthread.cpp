#include "mainthread.h"
#include "controller.h"

Mainthread::Mainthread(Joystick* joystick) : QObject() {

    //TODO: Pass in other needed objects

    threadTimer = new QTimer(0);
    threadTimer->setTimerType(Qt::PreciseTimer);
    threadTimer->setInterval(TICK_INTERVAL);

    lastTime = 0;

    this->joystick = joystick;

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

    joystick->connect();

    thrustMapper = new ThrustMapper();

    return true;
}


//Stop the mainthread
void Mainthread::stop() {
    threadTimer->stop();
    udp->closeSocket();

    joystick->disconnect();
}


//Called after TICK_INTERVAL milliseconds
//main while loop where it ticks every 10ms
void Mainthread::tick() {
    qint64 now = QDateTime::currentMSecsSinceEpoch();

    joystick->update();

    /*
    vect6 targetvector;

    targetvector.L.z = joystick->getAxis(JOYSTICK_LJ_Y) * -1;
    targetvector.L.y = (joystick->getAxis(JOYSTICK_RTRIGG) / 2) - (joystick->getAxis(JOYSTICK_LTRIGG) / 2);

    int l = joystick->getButtonState(JOYSTICK_LEFTBUTTON) * -1;
    int r = joystick->getButtonState(JOYSTICK_RIGHTBUTTON);
    targetvector.L.x = (l + r) * INT_16_MAX;

    targetvector.R.z = joystick->getAxis(JOYSTICK_RJ_X);
    targetvector.R.x = joystick->getAxis(JOYSTICK_RJ_Y) * -1;
    targetvector.R.y = joystick->getAxis(JOYSTICK_LJ_X) * -1;

    ThrustMapper* tm = new ThrustMapper();
    tm->calculateThrustMap(targetvector);

    vect8 m = tm->thrust_map;
    //qDebug("%d         %d\n", m.a, m.b);
    //qDebug("   %d  %d  \n",   m.e, m.f);
    //qDebug("   %d  %d  \n",   m.g, m.h);
    //qDebug("%d         %d\n", m.c, m.d);

    int thrusters[8] = {m.a, m.b, m.c, m.d, m.e, m.f, m.g, m.h};
    Controller::getInstance()->SetThrusterValues(thrusters);
    */

    ControlPacket* cp = new ControlPacket();

    cp->setX(joystick->getAxis(JOYSTICK_LJ_Y));

    int leftButton = joystick->getButtonState(JOYSTICK_LEFTBUTTON);
    int rightButton = joystick->getButtonState(JOYSTICK_RIGHTBUTTON);
    cp->setY((rightButton - leftButton) * INT_16_MAX);

    cp->setZ((joystick->getAxis(JOYSTICK_RTRIGG) / 2) - (joystick->getAxis(JOYSTICK_LTRIGG) / 2));

    cp->setRoll(joystick->getAxis(JOYSTICK_RJ_X));
    cp->setPitch(joystick->getAxis(JOYSTICK_RJ_Y));
    cp->setYaw(joystick->getAxis(JOYSTICK_LJ_X));

    cp->print();

    udp->send(cp->getPacket());
    QByteArray returnData = udp->read();


    lastTime = now;
}
