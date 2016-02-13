#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "mainthread.h"
#include "controller.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    Controller* control = Controller::getInstance();
    engine.rootContext()->setContextProperty("controller", control);

    qRegisterMetaType<Sint16>("Sint16");

    return app.exec();
}
