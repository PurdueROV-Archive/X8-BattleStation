#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <QObject>
#include <QUdpSocket>

class UDPSocket : public QObject
{
    Q_OBJECT


public:
    UDPSocket();

    void initSocket(QHostAddress addr, quint16 port);
    void send(QByteArray data);
    void read();


private:
    QUdpSocket*  socket;

private slots:
    void onData();
};

#endif // UDPSOCKET_H
