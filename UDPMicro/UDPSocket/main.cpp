#include <QCoreApplication>
#include "udp.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    UDP client;

    client.HelloUDP();

    return a.exec();
}

