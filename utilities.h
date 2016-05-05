#ifndef UTILITIES_H
#define UTILITIES_H

#include <QtGlobal>
#include <QByteArray>


class Utilities
{
public:
    Utilities() {}

    static qint32 rangeMap(qint32 x, qint32 in_min, qint32 in_max, qint32 out_min, qint32 out_max);
    static quint8 crc(QByteArray data);
};

#endif // UTILITIES_H
