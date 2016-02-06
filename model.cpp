#include "model.h"


Model::Model() : QObject() {
    running = false;
}

void Model::init() {
    this->controller = Controller::getInstance();

    QObject::connect(this->controller, &Controller::modelRefreshList,
                     this, &Model::refreshList);

    QObject::connect(this->controller, &Controller::modelJoystick1Select,
                     this, &Model::selectJoystick1);

    QObject::connect(this->controller, &Controller::modelStart,
                     this, &Model::start);

    QObject::connect(this->controller, &Controller::modelStop,
                         this, &Model::stop);

    if (SdlWrap::init() == false) {
        qDebug() << SdlWrap::getError();
    }

    controller->modelSetJoystickDevices(SdlWrap::getJoystickList());

    joystick1 = new Joystick();

    qThread = new QThread(this);
    mainthread = new Mainthread(joystick1);
}

Model::~Model() {
    if (mainthread) delete mainthread;
    if (qThread) delete qThread;

}

void Model::refreshList() {
    controller->modelSetJoystickDevices(SdlWrap::getJoystickList());
}

void Model::selectJoystick1(int index) {
    joystick1->select(index);
}

void Model::start() {
    running = true;
    if (mainthread->start()) {
        running = true;
    } else {
        running = false;
        emit controller->modelStopRunning();
    }
}

void Model::stop() {
    running = false;
    mainthread->stop();
}
