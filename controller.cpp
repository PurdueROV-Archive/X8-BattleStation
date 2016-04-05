#include "controller.h"
#include <QDebug>

Controller* Controller::instance = NULL;
QMutex Controller::mutex;

Controller* Controller::getInstance() {
    QMutexLocker locker(&mutex);

    if (instance == NULL) {
        instance = new Controller();
        instance->init();
    }

    return instance;
}

Controller::~Controller() {
    //NEVER DECONSTUCT...
}

void Controller::init() {
    this->running = false;

    if (SdlWrap::init() == false) {
        qDebug() << SdlWrap::getError();
    }

    joystickDevices = SdlWrap::getJoystickList();
    thrusterValues = QStringList();

    tempData = QList<int>();
    tempData.append(20);
    tempData.append(10);
    tempData.append(-10);
    tempData.append(-20);
    tempData.append(0);

    rotation = 0;
    pitch = 0;

    joystick = new Joystick();

    qThread = new QThread(this);
    mainthread = new Mainthread(joystick);

}


/////////////////////////////////////////
//   Thread Control Properties & Fns   //
/////////////////////////////////////////

//Read property
bool Controller::Running() const {
    return running;
}

//Write Property
void Controller::SetRunning(bool running) {
    this->running = running;

    if (this->running) {
        this->startThread();
    } else {
        this->stopThread();
    }

    emit RunningChanged();
}

//Start Thread Fn
void Controller::startThread() {
    running = true;
    if (mainthread->start()) {
        running = true;
    } else {
        running = false;
    }

    emit RunningChanged();
}

//Stop Thread Function
void Controller::stopThread() {
    running = false;
    mainthread->stop();

    emit RunningChanged();
}

/////////////////////////////////////////
//      Communication Properties       //
/////////////////////////////////////////

//Read property
bool Controller::Communication() const {
    return this->communication;
}

//Write Property
void Controller::SetCommunication(bool communication) {
    this->communication = communication;
    emit CommunicationChanged();
}


/////////////////////////////////////////
//     Joystick Control Properties     //
/////////////////////////////////////////

//Read Property
QStringList Controller::JoystickDevices() const {
    return joystickDevices;
}

int Controller::JoystickCount() const {
    return SdlWrap::getNumJoysticks();
}

QString Controller::JoystickName() const {
    return SdlWrap::getJoystickName(joystickIndex);
}

//Select a device
void Controller::JoystickSelect(int index) {
    joystickIndex = index;
    joystick->select(index);
    emit JoystickNameChanged();
}


/////////////////////////////////////////
//     Thruster Control Properties     //
/////////////////////////////////////////

QStringList Controller::ThrusterValues() const {
    return thrusterValues;
}

void Controller::SetThrusterValues(int values[]) {
    thrusterValues.clear();

    for (int i = 0; i < 8; i++) {
       QString val = QString("%1").arg(values[i]/32);
       thrusterValues.append(val + "");
    }

    emit ThrusterValuesChanged();
}


/////////////////////////////////////////
//          TempData Properties        //
/////////////////////////////////////////

QList<int> Controller::TempData() const {
    return tempData;
}

void Controller::addTempData(int data) {
    tempData.removeFirst();
    tempData.append(data);

    emit TempDataChanged();
}

/////////////////////////////////////////
//         Connection Properties       //
/////////////////////////////////////////

QString Controller::ConnectionIP() const {
    return this->connectionIP;
}
int Controller::ConnectionPort() const {
    return this->connectionPort;
}

//Write Property
void Controller::setConnectionIP(QString ip) {
    this->connectionIP = ip;
    emit ConnectionIPChanged();
}

void Controller::setConnectionPort(int port) {
    this->connectionPort = port;
    emit ConnectionPortChanged();
}

/////////////////////////////////////////
//          Rotation Properties        //
/////////////////////////////////////////

int Controller::Rotation() const {
    return this->rotation;
}

void Controller::setRotation(int rotation) {
    this->rotation = (rotation % 360);
    emit RotationChanged();
}

int Controller::Pitch() const {
    return this->pitch;
}

void Controller::setPitch(int pitch) {
    this->pitch = (pitch % 360);
    emit PitchChanged();
}

/////////////////////////////////////////
//         Misc Public Slots           //
/////////////////////////////////////////

//Refresh Serial Devices
void Controller::RefreshLists() {
    joystickDevices = SdlWrap::getJoystickList();
    emit JoystickCountChanged();
    emit JoystickDevicesChanged();
}



