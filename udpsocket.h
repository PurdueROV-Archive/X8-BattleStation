#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <QObject>
#include <QUdpSocket>

class UDPSocket : public QObject
{
    Q_OBJECT


public:
    UDPSocket();

    void initSocket(QString addr, quint16 port);
    void send(QByteArray data);
    void closeSocket();
    QByteArray read();


private:
    QUdpSocket* socket;

};

#endif // UDPSOCKET_H
