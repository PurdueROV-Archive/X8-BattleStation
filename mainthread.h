#ifndef MAINTHREAD_H
#define MAINTHREAD_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QDateTime>

#define TICK_INTERVAL 10

class Mainthread : public QObject
{
    Q_OBJECT


public:
    Mainthread();
    ~Mainthread();

    bool start();
    void stop();

private slots:
    void tick();


private:
    QTimer* threadTimer;
    qint64 lastTime = 0;

};

#endif // MAINTHREAD_H
