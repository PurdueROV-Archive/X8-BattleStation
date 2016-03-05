#include "controlpacket.h"

ControlPacket::ControlPacket() {
    this->data = QByteArray(PACKET_SIZE, 0x00);
    reset();
}

ControlPacket::~ControlPacket() {
}

void ControlPacket::setX(qint16 x) {
    memcpy(this->x, &x, 2);
}

void ControlPacket::setY(qint16 y) {
    memcpy(this->y, &y, 2);
}

void ControlPacket::setZ(qint16 z) {
    memcpy(this->z, &z, 2);
}

void ControlPacket::setRoll(qint16 roll) {
    memcpy(this->roll, &roll, 2);
}

void ControlPacket::setPitch(qint16 pitch) {
    memcpy(this->pitch, &pitch, 2);
}

void ControlPacket::setYaw(qint16 yaw) {
    memcpy(this->yaw, &yaw, 2);
}


quint8 ControlPacket::crc(QByteArray data) {
    quint8 crc = 0;
    int size = data.size();

    for (int i = 1; i < size-2; ++i) {

        quint8 inbyte = data.at(i);

        for (int i = 8; i; i--) {
            quint8 mix = (crc ^ inbyte) & 0x01;
            crc >>= 1;
            if (mix) crc ^= 0xD5;
            inbyte >>= 1;
        }
    }

    return crc;
}

void ControlPacket::assemblePacket() {
     data[0] =   HEADER;
     data[1] =  CONTROL;

     data[2] =     x[0];
     data[3] =     x[1];

     data[4] =     y[0];
     data[5] =     y[1];

     data[6] =     z[0];
     data[7] =     z[1];

     data[8] =  roll[0];
     data[9] =  roll[1];

    data[10] = pitch[0];
    data[11] = pitch[1];

    data[12] =   yaw[0];
    data[13] =   yaw[1];

    for (int i = 14; i < PACKET_SIZE-2; i++) {
        data[i] = 'A' + i - 2;
    }

    data[PACKET_SIZE-2] = CRC_BYTE;
    data[PACKET_SIZE-1] = TAIL;

    data[PACKET_SIZE-2] = crc(data);
}

QByteArray ControlPacket::getPacket() {
    assemblePacket();
    return data;
}

void ControlPacket::reset() {
    data[0] = HEADER;
    data[1] = CONTROL;

    data[PACKET_SIZE-2] = CRC_BYTE;
    data[PACKET_SIZE-1] = TAIL;    
}

void ControlPacket::print() {
    assemblePacket();

    qDebug("Header:\t\t 0x%x", data.at(0));
    qDebug("Control:\t 0x0%x", data.at(1));

    qint16 printX = 0;
    memcpy(&printX, &data.constData()[2], 2);

    qint16 printY = 0;
    memcpy(&printY, &data.constData()[4], 2);

    qint16 printZ = 0;
    memcpy(&printZ, &data.constData()[6], 2);

    qDebug("X:\t\t %d", printX);
    qDebug("Y:\t\t %d", printY);
    qDebug("Z:\t\t %d", printZ);

    qint16 printRoll = 0;
    memcpy(&printRoll, &data.constData()[8], 2);

    qint16 printPitch = 0;
    memcpy(&printPitch, &data.constData()[10], 2);

    qint16 printYaw = 0;
    memcpy(&printYaw, &data.constData()[12], 2);

    qDebug("Roll:\t\t %d",  printRoll);
    qDebug("Pitch:\t\t %d", printPitch);
    qDebug("Yaw:\t\t %d",   printYaw);

    qDebug("Snoids:\t\t %d%d %d%d %d%d %d%d",
           data.at(14) & 0x80 ? 1 : 0,
           data.at(14) & 0x40 ? 1 : 0,
           data.at(14) & 0x20 ? 1 : 0,
           data.at(14) & 0x10 ? 1 : 0,
           data.at(14) & 0x08 ? 1 : 0,
           data.at(14) & 0x04 ? 1 : 0,
           data.at(14) & 0x02 ? 1 : 0,
           data.at(14) & 0x01 ? 1 : 0
           );

    qDebug("H.Pump:\t\t %d", data.at(15));
    qDebug("LEDs:\t\t %d", data.at(16));

    qDebug("T. Stat:\t %d %d %d %d %d %d %d %d",
           data.at(17) & 0x80 ? 1 : 0,
           data.at(17) & 0x40 ? 1 : 0,
           data.at(17) & 0x20 ? 1 : 0,
           data.at(17) & 0x10 ? 1 : 0,
           data.at(17) & 0x08 ? 1 : 0,
           data.at(17) & 0x04 ? 1 : 0,
           data.at(17) & 0x02 ? 1 : 0,
           data.at(17) & 0x01 ? 1 : 0
           );

    qDebug("PID:\t\t %s", data.at(18) ? "Yes" : "No");

    qint16 printTuningA = 0;
    memcpy(&printTuningA, &data.constData()[19], 2);

    qint16 printTuningB = 0;
    memcpy(&printTuningB, &data.constData()[21], 2);

    qint16 printTuningC = 0;
    memcpy(&printTuningC, &data.constData()[23], 2);

    qDebug("PID A:\t\t %d", printTuningA);
    qDebug("PID B:\t\t %d", printTuningB);
    qDebug("PID C:\t\t %d", printTuningC);

    qDebug("Pivot X:\t %d", (qint8) data.at(25));
    qDebug("Pivot Y:\t %d", (qint8) data.at(26));
    qDebug("Pivot Z:\t %d", (qint8) data.at(27));

    qDebug("Check:\t\t 0x%x", (quint8) data.at(PACKET_SIZE-2));
    qDebug("Tail:\t\t 0x%x", data.at(PACKET_SIZE-1));
}
