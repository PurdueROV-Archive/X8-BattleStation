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
    int size = data.size();
    qDebug("Size: %d", size);
    for (int i = 0; i < size; ++i) {
        qDebug("[%d]: %c, %d\n", i, (quint8) data.at(i), (quint8) data.at(i));
    }
}

