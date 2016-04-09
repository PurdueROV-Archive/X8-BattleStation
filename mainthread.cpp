#include "mainthread.h"
#include "controller.h"
#include "packetin.h"
Mainthread::Mainthread(Joystick* joystick) : QObject() {

    //TODO: Pass in other needed objects

    threadTimer = new QTimer(0);
    threadTimer->setTimerType(Qt::PreciseTimer);
    threadTimer->setInterval(TICK_INTERVAL);

    last_time  = 0;
    last_comms = 0;

    this->joystick = joystick;
    tmapper = new ThrustMapper();

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
    //udp->initSocket(Controller::getInstance()->ConnectionIP(),
    //                Controller::getInstance()->ConnectionPort());

    joystick->connect();

    last_time  = QDateTime::currentMSecsSinceEpoch();
    velocitySlowDown = false;
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

    Controller::getInstance()->addTempData(qrand() % ((18 + 1) + 10) -10);

    vect6 targetvector;
    tmapper->changeMapperMatrix(246);

    targetvector.L.x = joystick->getAxis(JOYSTICK_LJ_Y);
    int l = joystick->getButtonState(JOYSTICK_LEFTBUTTON);
    int r = joystick->getButtonState(JOYSTICK_RIGHTBUTTON);
    targetvector.L.y = (r - l) * INT_16_MAX;

    targetvector.L.z = (joystick->getAxis(JOYSTICK_RTRIGG) / 2) - (joystick->getAxis(JOYSTICK_LTRIGG) / 2);

    targetvector.R.x = joystick->getAxis(JOYSTICK_RJ_X);
    targetvector.R.y = joystick->getAxis(JOYSTICK_RJ_Y);
    targetvector.R.z = joystick->getAxis(JOYSTICK_LJ_X);

    tmapper->calculateThrustMap(targetvector);

    vect8 m = tmapper->thrust_map;

    int thrusters[8] = {m.a, m.b, m.c, m.d, m.e, m.f, m.g, m.h};
    Controller::getInstance()->SetThrusterValues(thrusters);


    ControlPacket* cp = new ControlPacket();
    int leftButton = joystick->getButtonState(JOYSTICK_LEFTBUTTON);
    int rightButton = joystick->getButtonState(JOYSTICK_RIGHTBUTTON);
    if (joystick->getButtonPressed(JOYSTICK_START)){
        velocitySlowDown = !velocitySlowDown;
    }
    if (velocitySlowDown) {
        cp->setX((joystick->getAxis(JOYSTICK_LJ_Y)) / 2);
        cp->setY((rightButton - leftButton) * INT_16_MAX/2);
        cp->setZ((joystick->getAxis(JOYSTICK_RTRIGG) / 4) - (joystick->getAxis(JOYSTICK_LTRIGG) / 4));

        cp->setRoll(joystick->getAxis(JOYSTICK_RJ_X)/2);
        cp->setPitch(joystick->getAxis(JOYSTICK_RJ_Y)/2);
        cp->setYaw(joystick->getAxis(JOYSTICK_LJ_X)/2);
    }
    else
    {
        cp->setX(joystick->getAxis(JOYSTICK_LJ_Y));
        cp->setY((rightButton - leftButton) * INT_16_MAX);
        cp->setZ((joystick->getAxis(JOYSTICK_RTRIGG) / 2) - (joystick->getAxis(JOYSTICK_LTRIGG) / 2));
        cp->setRoll(joystick->getAxis(JOYSTICK_RJ_X));
        cp->setPitch(joystick->getAxis(JOYSTICK_RJ_Y));
        cp->setYaw(joystick->getAxis(JOYSTICK_LJ_X));
    }

    float rotation = (float) joystick->getAxis(0) / (float) (INT_16_MAX);
    Controller::getInstance()->setRotation(90 * rotation);

    float pitch = (float) joystick->getAxis(1) / (float) (INT_16_MAX);
    Controller::getInstance()->setPitch(90 * pitch);

    //cp->print();

    udp->send(cp->getPacket());
    QByteArray returnData = udp->read();
    PacketIn *packet = new PacketIn();
    if(!packet->setData(returnData)) qDebug("Bad Checksum or no data");
    int size = returnData.size();
    if (size > 0) {
        last_comms = now;

        for (int i = 0; i < size; i++) {
           qDebug("[%d]: %u", i, (quint8) returnData.at(i));
        }

        qint16 printA = 0;
        memcpy(&printA, &returnData.constData()[1], 2);

        qint16 printB = 0;
        memcpy(&printB, &returnData.constData()[3], 2);

        qint16 printC = 0;
        memcpy(&printC, &returnData.constData()[5], 2);
        qDebug("A: %d", printA);

        qDebug("B: %d", printB);

        qDebug("C: %d", printC);

    }

    Controller::getInstance()->SetCommunication(now - last_comms < 500);

    last_time = now;
}
