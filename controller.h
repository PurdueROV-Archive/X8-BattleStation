#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QMutex>


class Controller : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool Running READ Running WRITE SetRunning NOTIFY RunningChanged())

    Q_PROPERTY(QStringList JoystickDevices READ JoystickDevices NOTIFY JoystickDevicesChanged)


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


/////////////////////////////////////////
//  Control Thread Running Properties  //
/////////////////////////////////////////

public:
    bool Running() const; //Read property

    void SetRunning(bool running); //Write Property

private: //Dependencies
    bool running;

signals: //Signal to emit on change
    void RunningChanged();

//Model C++ Control Methods
public:
    void modelStopRunning(); //set running to false

signals:
    void modelStart(); //signal for start connection
    void modelStop(); //signal for stop connection


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
    void Joystick1Select(int index);

private: //dependencies
    int joystick1Index;

//Model C++ Control Methods
public:
    //set serial device qlist for combobox
    void modelSetJoystickDevices(QStringList joystickDevices);

signals:
    void modelJoystick1Select(int index); //emit when serial device combobox index changed

/////////////////////////////////////////
//         Misc Public Slots           //
/////////////////////////////////////////
public slots:
    void RefreshLists();

signals:
    void modelRefreshList(); //emit to refresh serial qlist

};

#endif // CONTROLLER_H
