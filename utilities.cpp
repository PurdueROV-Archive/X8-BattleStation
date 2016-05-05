#include "utilities.h"

qint32 Utilities::rangeMap(qint32 x, qint32 in_min, qint32 in_max, qint32 out_min, qint32 out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

quint8 Utilities::crc(QByteArray data) {
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
