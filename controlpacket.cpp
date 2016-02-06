#include "controlpacket.h"

ControlPacket::ControlPacket() {
    this->data = QByteArray(PACKET_SIZE, 0x00);
    reset();
}

ControlPacket::~ControlPacket() {
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
    data[0] = HEADER;
    data[1] = CONTROL;

    for (int i = 2; i < PACKET_SIZE-2; i++) {
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
        qDebug("[%d]: %c", i, (quint8) data.at(i));
    }
}

