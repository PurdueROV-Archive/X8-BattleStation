#ifndef CONTROLPACKET_H
#define CONTROLPACKET_H

#include <QByteArray>

#define PACKET_SIZE 30

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

    void reset();

    void print();

private:
    quint8 size;
    QByteArray data;

    void assemblePacket();

    quint8 crc(QByteArray data);

    quint8 x[2];

    quint8 y[2];

    quint8 z[2];

    quint8 roll[2];

    quint8 pitch[2];

    quint8 yaw[2];
};

#endif // CONTROLPACKET_H
