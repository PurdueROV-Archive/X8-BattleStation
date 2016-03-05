#include "udpsocket.h"

UDPSocket::UDPSocket() {

}


void UDPSocket::initSocket(QString addr, quint16 port) {
    socket = new QUdpSocket();
    socket->connectToHost(QHostAddress(addr), port);

    if (socket->waitForConnected(1000)) {
        qDebug("Connected!");
    } else {
        qDebug() << "Couldn't connect";
    }
}


void UDPSocket::send(QByteArray data) {

    if (socket == NULL || !socket || socket->NotOpen) {
        return;
    }

    socket->write(data);
}

void UDPSocket::closeSocket() {
    socket->close();
}

QByteArray UDPSocket::read() {

    if (socket == NULL || !socket || socket->state() == QUdpSocket::UnconnectedState) {
        return NULL;
    }

    if (socket->hasPendingDatagrams()) {
        return socket->readAll();
    }

    return NULL;
}
