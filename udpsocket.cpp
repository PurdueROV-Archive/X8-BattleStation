#include "udpsocket.h"

UDPSocket::UDPSocket() {

}


void UDPSocket::initSocket(QHostAddress addr, quint16 port) {
    socket = new QUdpSocket();
    socket->connectToHost(addr, port);

    if (socket->waitForConnected(1000)) {
        qDebug("Connected!");
    } else {
        qDebug() << "Couldn't connect";
    }
}


void UDPSocket::send(QByteArray data) {
    socket->write(data);
}

void UDPSocket::read() {
    if (socket->hasPendingDatagrams()) {
        qDebug() << socket->read(6400);
    }
}


void UDPSocket::onData() {
    while (socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        socket->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);

        qDebug() << datagram.data();
    }
}