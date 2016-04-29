#include "mainthread.h"
#include "controller.h"
#include "packetin.h"


void normalize(int values[], int size) {
    int valuesMax = 0;
    int max = INT_16_MAX;

    //get Max value
    for (int i = 0; i < size; i++) {
        if (abs(values[i]) > max) {
            valuesMax = abs(values[i]);
        }
    }

    if (valuesMax > max) {
        //Normalize the values based off max
        float n = ((float) max) / ((float) valuesMax);
        for (int i = 0; i < size; i++) {
            values[i] = (int) (n * values[i]);
        }
    }
}



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
     ControlPacket* cp = new ControlPacket();

    /*vect6 targetvector;
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
    }*/

    //Calculate Thruster Values

    //Y (Ascend and descend)
    int velY = joystick->getAxis(JOYSTICK_RTRIGG) - joystick->getAxis(JOYSTICK_LTRIGG);

    //X (Strafe left and right)
    int velX = 0;
    if (joystick->getButtonState(JOYSTICK_LEFTBUTTON)) velX += INT_16_MIN;
    if (joystick->getButtonState(JOYSTICK_RIGHTBUTTON)) velX += INT_16_MAX;

    //Z (forward and backword)
    int velZ = joystick->getAxis(JOYSTICK_LJ_Y);

    //Yaw (rotate clockwise and counter-clockwise)
    int yaw = joystick->getAxis(JOYSTICK_LJ_X) * -1;
    //Pitch (rotate forward and backward)
    int pitch = joystick->getAxis(JOYSTICK_RJ_Y);

    //Roll (rotate left to right)
    int roll = joystick->getAxis(JOYSTICK_RJ_X);


    velY = velY * 0.5;
    velX = velX * 0.5;
    velZ = velZ * 0.5;

    yaw = yaw * 0.15;
    pitch = pitch * 0.4;
    roll = roll * 0.4;


    int thrusters[8] = {0,0,0,0,0,0,0,0};
    int* horizontalThrusters = thrusters;
    int* verticalThrusters = thrusters + 4;

    horizontalThrusters[0] += velX;
    horizontalThrusters[1] -= velX;
    horizontalThrusters[2] += velX;
    horizontalThrusters[3] -= velX;

    verticalThrusters[0] += velY;
    verticalThrusters[1] += velY;
    verticalThrusters[2] += velY;
    verticalThrusters[3] += velY;

    horizontalThrusters[0] += velZ;
    horizontalThrusters[1] += velZ;
    horizontalThrusters[2] -= velZ;
    horizontalThrusters[3] -= velZ;

    verticalThrusters[0] += pitch;
    verticalThrusters[1] += pitch;
    verticalThrusters[2] -= pitch;
    verticalThrusters[3] -= pitch;

    horizontalThrusters[0] -= yaw;
    horizontalThrusters[1] += yaw;
    horizontalThrusters[2] += yaw;
    horizontalThrusters[3] -= yaw;

    verticalThrusters[0] += roll;
    verticalThrusters[1] -= roll;
    verticalThrusters[2] += roll;
    verticalThrusters[3] -= roll;

    int diff = 2000;
    for (int i = 0; i < 8; i++) {
       if (abs(thrusters[i] - lastThrusters[i]) > diff) {
           if (lastThrusters[i] < thrusters[i]) {
               thrusters[i] = lastThrusters[i] + diff;
           } else if (lastThrusters[i] > thrusters[i]) {
               thrusters[i] = lastThrusters[i] - diff;
           }
       }
       lastThrusters[i] = thrusters[i];
    }

    normalize(horizontalThrusters, 4);
    normalize(verticalThrusters, 4);

    Controller::getInstance()->SetThrusterValues(thrusters);

    cp->setX(horizontalThrusters[0]);
    cp->setY(horizontalThrusters[1]);
    cp->setZ(horizontalThrusters[2]);

    cp->setRoll(horizontalThrusters[3]);
    cp->setPitch(verticalThrusters[1]);
    cp->setYaw(verticalThrusters[2] * 0.95);

    if (now - last_comms > (500 + TICK_INTERVAL)) {
       cp->safety();
    }

    cp->print();

    udp->send(cp->getPacket());

    QByteArray returnData = udp->read();

    if (returnData.size() > 0) {
        last_comms = now;

    //        PacketIn *packet = new PacketIn();

    //        if (!packet->setData(returnData)){
    //            qDebug("Bad Checksum or no data");
    //        }

    //        delete packet;
    }

    if (now - last_comms > 500) {
        cp->safety();
    }

    Controller::getInstance()->SetCommunication(now - last_comms < 500);

    delete cp;

    last_time = now;
}
