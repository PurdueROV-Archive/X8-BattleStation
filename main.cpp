#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "mainthread.h"
#include "input/inputHandler.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);


    //TODO: Start and stop main thread via QML
    Mainthread* t = new Mainthread();
    t->start();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
