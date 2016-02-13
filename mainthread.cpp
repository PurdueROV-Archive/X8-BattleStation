#include "mainthread.h"
#include "input/inputHandler.h"
#include "testInputHandler.h"

InputHandler* myInput;

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

    qDebug("start\n");
    //TODO: Check if joysticks are connected, can connet to microcontroller, etc
    threadTimer->start();
    //initialize stuff here
    qDebug("before initializing myInput\n");
    myInput = new InputHandler();
    qDebug("before typedefs\n");
    typedef void(*axisFunc)(float);
    typedef void(*buttonFunc)(void);    
    typedef void(*toggleFunc)(int);
    qDebug("before vectors\n");
    std::vector<axisFunc> axis = {rotateFunc, walkFunc, yawFunc, yawFunc, yawFunc, yawFunc, yawFunc, yawFunc};
    std::vector<buttonFunc> button = {punch, dodge, climbUp, climbDown, climbLeft, climbRight};
    std::vector<toggleFunc> toggle = {kick, slide};
    std::vector<int> numStates = {4, 2};
    qDebug("before adds\n");
    try
    {
        myInput->addJoystickAxis(0, axis);
        myInput->addButtons(0, button);
        myInput->addToggleButtons(0, toggle, numStates);
    }
    catch(const char* e)
    {
        qDebug() << e;
    }
    return true;
}

//Stop the mainthread
void Mainthread::stop() {
    threadTimer->stop();
    //closing stuff here
    delete myInput;
}

//Called after TICK_INTERVAL milliseconds
//main while loop where it ticks every 10ms
void Mainthread::tick() {
    qint64 now = QDateTime::currentMSecsSinceEpoch();
    //qDebug() << now-lastTime;
    myInput->handle();
    lastTime = now;
    //TODO: Add code for each tick
}
