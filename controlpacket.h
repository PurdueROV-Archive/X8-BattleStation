#ifndef CONTROLPACKET_H
#define CONTROLPACKET_H

#include <QByteArray>
#include "utilities.h"

#define PACKET_SIZE 28

#define HEADER 0x12
#define TAIL   0x13

#define CONTROL 0x01

#define CRC_BYTE 0xC5

class ControlPacket
{
public:
    ControlPacket();
    ~ControlPacket();

    QByteArray getPacket();

    void setX(qint16 x);
    void setY(qint16 y);
    void setZ(qint16 z);

    void setRoll (qint16 roll);
    void setPitch(qint16 pitch);
    void setYaw  (qint16 yaw);

    void setCameraServo(qint8 angle);

    void setSolenoid1(bool on);
    void setSolenoid2(bool on);
    void setSolenoid3(bool on);
    void setSolenoid4(bool on);

    void setThrusterStatus(bool t1, bool t2, bool t3, bool t4, bool t5, bool t6, bool t7, bool t8);

    void setStabilizationLock(bool x, bool y, bool z, bool roll, bool pitch, bool yaw);

    void setRotationPConst(qint16 pValue);
    void setRotationIConst(qint16 iValue);

    void setLocationPConst(qint16 pValue);
    void setLocationIConst(qint16 iValue);

    void defaults();

    void print();

private:
    quint8 size;
    QByteArray data;

    void assemblePacket();

    qint16 x;
    qint16 y;
    qint16 z;
    qint16 roll;
    qint16 pitch;
    qint16 yaw;

    qint8 cameraAngle;

    bool solenoid1;
    bool solenoid2;
    bool solenoid3;
    bool solenoid4;

    bool thrusterStatus[8];

    bool rollLock;
    bool pitchLock;
    bool yawLock;

    bool xLock;
    bool yLock;
    bool zLock;

    qint16 rotationPConst;
    qint16 rotationIConst;

    qint16 locationPConst;
    qint16 locationIConst;
};

#endif // CONTROLPACKET_H
