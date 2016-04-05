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
    Q_PROPERTY(bool Communication READ Communication WRITE SetCommunication NOTIFY CommunicationChanged)

    Q_PROPERTY(QStringList JoystickDevices READ JoystickDevices NOTIFY JoystickDevicesChanged)
    Q_PROPERTY(int JoystickCount READ JoystickCount NOTIFY JoystickCountChanged)
    Q_PROPERTY(QString JoystickName READ JoystickName NOTIFY JoystickNameChanged)

    Q_PROPERTY(QStringList ThrusterValues READ ThrusterValues NOTIFY ThrusterValuesChanged)

    Q_PROPERTY(QString ConnectionIP READ ConnectionIP WRITE setConnectionIP NOTIFY ConnectionIPChanged)
    Q_PROPERTY(int ConnectionPort READ ConnectionPort WRITE setConnectionPort NOTIFY ConnectionPortChanged)

    Q_PROPERTY(QList<int> TempData READ TempData NOTIFY TempDataChanged)

    Q_PROPERTY(int Rotation READ Rotation WRITE setRotation NOTIFY RotationChanged)
    Q_PROPERTY(int Pitch READ Pitch WRITE setPitch NOTIFY PitchChanged)


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
    void updateTempData();

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
//      Communication Properties       //
/////////////////////////////////////////

//Running Property
public:
    bool Communication() const; //Read property

    void SetCommunication(bool communication); //Write Property

private: //Dependencies
    bool communication;

signals: //Signal to emit on change
    void CommunicationChanged();

/////////////////////////////////////////
//     Joystick Control Properties     //
/////////////////////////////////////////

//QML Property Definitions
public:
    QStringList JoystickDevices() const; //Read property
    int JoystickCount() const;
    QString JoystickName() const;

    //Write Property

private: //Dependencies
    QStringList joystickDevices;

signals: //Signal to emit on change
    void JoystickDevicesChanged();
    void JoystickCountChanged();
    void JoystickNameChanged();

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
//          TempData Properties        //
/////////////////////////////////////////

//QML Property Definitions
public:
    //Read property
    QList<int> TempData() const;

    void addTempData(int data);


private: //Dependencies
    QList<int> tempData;


signals: //Signal to emit on change
    void TempDataChanged();

/////////////////////////////////////////
//         Connection Properties       //
/////////////////////////////////////////

//QML Property Definitions
public:
    //Read property
    QString ConnectionIP() const;
    int ConnectionPort() const;

    //Write Property
    void setConnectionIP(QString ip);
    void setConnectionPort(int port);

private: //Dependencies
    QString connectionIP;
    int     connectionPort;


signals: //Signal to emit on change
    void ConnectionIPChanged();
    void ConnectionPortChanged();

/////////////////////////////////////////
//          Rotation Properties        //
/////////////////////////////////////////

//QML Property Definitions
public:
    //Read property
    int Rotation() const;
    int Pitch() const;

    //Write Property
    void setRotation(int rotation);
    void setPitch(int pitch);

private: //Dependencies
    int rotation;
    int pitch;

signals: //Signal to emit on change
    void RotationChanged();
    void PitchChanged();

/////////////////////////////////////////
//         Misc Public Slots           //
/////////////////////////////////////////
public slots:
    void RefreshLists();
};

#endif // CONTROLLER_H
