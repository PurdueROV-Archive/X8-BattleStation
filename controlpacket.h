#ifndef CONTROLPACKET_H
#define CONTROLPACKET_H

#include <QByteArray>

#define PACKET_SIZE 30

#define HEADER 'h' //0x12
#define TAIL 't' //0x13

#define CONTROL '1' //0x01

#define CRC_BYTE 'c' //0xC5

class ControlPacket
{
public:
    ControlPacket();
    ~ControlPacket();

    QByteArray getPacket();

    void reset();

    void print();


private:
    quint8 size;
    QByteArray data;

    void assemblePacket();

    quint8 crc(QByteArray data);

};

#endif // CONTROLPACKET_H
