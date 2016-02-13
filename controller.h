#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QMutex>
#include <QThread>
#include <QStringList>
#include "joystick.h"
#include "mainthread.h"


class Controller : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool Running READ Running WRITE SetRunning NOTIFY RunningChanged)

    Q_PROPERTY(QStringList JoystickDevices READ JoystickDevices NOTIFY JoystickDevicesChanged)

    Q_PROPERTY(QStringList ThrusterValues READ ThrusterValues NOTIFY ThrusterValuesChanged)


/////////////////////////////////////////
// Class & (de)Contsructor Definitions //
/////////////////////////////////////////
public:
    static Controller* getInstance();

private:
    Controller() {};
    Controller(Controller const&);
    void operator=(Controller const&);
    ~Controller();

    static Controller* instance;
    static QMutex mutex;

    void init();


/////////////////////////////////////////
//   Thread Control Properties & Fns   //
/////////////////////////////////////////

//Running Property
public:
    bool Running() const; //Read property

    void SetRunning(bool running); //Write Property

private: //Dependencies
    bool running;

signals: //Signal to emit on change
    void RunningChanged();

//Thread Control Functions
private:
    void startThread();
    void stopThread();

private: //Dependecies
    QThread* qThread;
    Mainthread* mainthread;

/////////////////////////////////////////
//     Joystick Control Properties     //
/////////////////////////////////////////

//QML Property Definitions
public:
    QStringList JoystickDevices() const; //Read property

    //Write Property

private: //Dependencies
    QStringList joystickDevices;

signals: //Signal to emit on change
    void JoystickDevicesChanged();

//Additional Control Methods
public slots:

    //Select a device based combo index
    void JoystickSelect(int index);

private: //dependencies
    int joystickIndex;

    Joystick* joystick;


/////////////////////////////////////////
//     Thruster Control Properties     //
/////////////////////////////////////////

//QML Property Definitions
public:
    //Read property
    QStringList ThrusterValues() const;

    //Write Property
    void SetThrusterValues(int values[]);

private: //Dependencies
    QStringList thrusterValues;


signals: //Signal to emit on change
    void ThrusterValuesChanged();

/////////////////////////////////////////
//         Misc Public Slots           //
/////////////////////////////////////////
public slots:
    void RefreshLists();
};

#endif // CONTROLLER_H
