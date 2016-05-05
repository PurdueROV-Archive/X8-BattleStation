#ifndef PACKETIN_H
#define PACKETIN_H

#include <QByteArray>
#include "utilities.h"

#define PACKET_SIZE 33
#define SENSOR_DATA 0x01

class PacketIn
{
public:
    PacketIn();
    char getThrusterStatus() ;

    float getPressure();

    float getTemperature();

    qint16 getIMU_X();

    qint16 getIMU_Y();

    qint16 getIMU_Z();

    qint16 getIMU_Roll();

    qint16 getIMU_Pitch();

    qint16 getIMU_Yaw();

    qint8* getThrusterValues();

    bool parseData(QByteArray data);

    void print();

private:
    quint8 thrusterStatus;
    float  pressure;
    float  temperature;
    qint16 IMU_X;
    qint16 IMU_Y;
    qint16 IMU_Z;
    qint16 IMU_Roll;
    qint16 IMU_Pitch;
    qint16 IMU_Yaw;
    qint8  thrusterValues[8];
};


#endif // PACKETIN_H
