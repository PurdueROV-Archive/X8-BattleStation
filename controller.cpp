#include "controller.h"

//Controller::Controller() : QObject() {
//    //Make sure it isn't running to begin with
//    running = false;
//}

Controller* Controller::instance = NULL;
QMutex Controller::mutex;

Controller* Controller::getInstance() {
    QMutexLocker locker(&mutex);

    if (instance == NULL) {
        instance = new Controller();
    }

    return instance;
}

Controller::~Controller() {

}


/////////////////////////////////////////
//  Control Thread Running Properties  //
/////////////////////////////////////////

//Read property
bool Controller::Running() const {
    return running;
}

//Write Property
void Controller::SetRunning(bool running) {
    this->running = running;

    if (this->running) {
        emit modelStart();
    } else {
        emit modelStop();
    }

    emit RunningChanged();
}

//set running to false, from model
void Controller::modelStopRunning() {
    running = false;
    emit RunningChanged();
}



/////////////////////////////////////////
//     Joystick Control Properties     //
/////////////////////////////////////////

//Read Property
QStringList Controller::JoystickDevices() const {
    return joystickDevices;
}

//Additional Control Methods

//Select a device
void Controller::Joystick1Select(int index) {
    joystick1Index = index;
    emit modelJoystick1Select(joystick1Index);
}

//Model C++ Control Methods

//set serial device qlist for combobox
void Controller::modelSetJoystickDevices(QStringList joystickDevices) {
    //qDebug() << "Setting new joystick";
    this->joystickDevices = joystickDevices;
    emit JoystickDevicesChanged();
}

/////////////////////////////////////////
//         Misc Public Slots           //
/////////////////////////////////////////

//Refresh Serial Devices
void Controller::RefreshLists() {
    emit modelRefreshList();
}



