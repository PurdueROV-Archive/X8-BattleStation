#include "mainthread.h"
#include "controller.h"

Mainthread::Mainthread(Joystick *joystick1) : QObject() {

    //TODO: Pass in other needed objects

    threadTimer = new QTimer(0);
    threadTimer->setTimerType(Qt::PreciseTimer);
    threadTimer->setInterval(TICK_INTERVAL);

    lastTime = 0;

    this->joystick1 = joystick1;

    //controller = Controller::getInstance();

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

    joystick1->connect();

    thrustMapper = new ThrustMapper();

    return true;
}


//Stop the mainthread
void Mainthread::stop() {
    threadTimer->stop();
    udp->closeSocket();

    joystick1->disconnect();
}


//Called after TICK_INTERVAL milliseconds
//main while loop where it ticks every 10ms
void Mainthread::tick() {
    qint64 now = QDateTime::currentMSecsSinceEpoch();
    //qDebug() << now-lastTime;

    joystick1->update();

    vect6 targetvector;

    targetvector.L.z = joystick1->getAxis(JOYSTICK_LJ_Y) * -1;
    targetvector.L.y = (joystick1->getAxis(JOYSTICK_RTRIGG) / 2) - (joystick1->getAxis(JOYSTICK_LTRIGG) / 2);

    int l = joystick1->getButtonState(JOYSTICK_LEFTBUTTON) * -1;
    int r = joystick1->getButtonState(JOYSTICK_RIGHTBUTTON);
    targetvector.L.x = (l + r) * INT16_MAX;

    targetvector.R.z = joystick1->getAxis(JOYSTICK_RJ_X);
    targetvector.R.x = joystick1->getAxis(JOYSTICK_RJ_Y) * -1;
    targetvector.R.y = joystick1->getAxis(JOYSTICK_LJ_X) * -1;

    //qDebug("L: x: %d, y: %d, z: %d\n", targetvector.L.x, targetvector.L.y, targetvector.L.z);
    //qDebug("R: x: %d, y: %d, z: %d\n", targetvector.R.x, targetvector.R.y, targetvector.R.z);

    ThrustMapper* tm = new ThrustMapper();
    tm->calculateThrustMap(targetvector);

    vect8 m = tm->thrust_map;
    //qDebug("%d         %d\n", m.a, m.b);
    //qDebug("   %d  %d  \n",   m.e, m.f);
    //qDebug("   %d  %d  \n",   m.g, m.h);
    //qDebug("%d         %d\n", m.c, m.d);

    int thrusters[8] = {m.a, m.b, m.c, m.d, m.e, m.f, m.g, m.h};
    Controller::getInstance()->SetThrusterValues(thrusters);

    ControlPacket* cp = new ControlPacket();

    cp->setX(joystick1->getAxis(JOYSTICK_LJ_X));

    int ll = joystick1->getButtonState(JOYSTICK_LEFTBUTTON) * -1;
    int rr = joystick1->getButtonState(JOYSTICK_RIGHTBUTTON);
    cp->setY((ll+rr) * INT16_MAX);

    cp->setZ((joystick1->getAxis(JOYSTICK_RTRIGG) / 2) - (joystick1->getAxis(JOYSTICK_LTRIGG) / 2));

    cp->setRoll(joystick1->getAxis(JOYSTICK_LJ_X));
    cp->setPitch(joystick1->getAxis(JOYSTICK_RJ_Y));
    cp->setYaw(joystick1->getAxis(JOYSTICK_RJ_X));



    cp->print();

    udp->send(cp->getPacket());
    QByteArray returnData = udp->read();

    if (returnData.size() > 0) {
        qDebug() << "Things";
        for (int i = 0; i < 30; ++i) {
            qDebug("[%d]: %c", i, (quint8) returnData.at(i));
        }
    }


    lastTime = now;
}
