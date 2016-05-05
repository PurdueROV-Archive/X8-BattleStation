#include "packetin.h"

PacketIn::PacketIn() {}

bool PacketIn::parseData(QByteArray data) {

//    if (data.at(1) != SENSOR_DATA) {
//        return false;
//    }

    if (data.size() < PACKET_SIZE) {
        return false;
    }

    if (Utilities::crc(data) != data.at(PACKET_SIZE - 2)) {
        return false;
    }

    thrusterStatus = data.at(2);

    memcpy(&pressure,    &data.constData()[3],  4);
    memcpy(&temperature, &data.constData()[7],  4);
    memcpy(&IMU_X,       &data.constData()[11], 2);
    memcpy(&IMU_Y,       &data.constData()[13], 2);
    memcpy(&IMU_Z,       &data.constData()[15], 2);
    memcpy(&IMU_Roll,    &data.constData()[17], 2);
    memcpy(&IMU_Pitch,   &data.constData()[19], 2);
    memcpy(&IMU_Yaw,     &data.constData()[21], 2);

    memcpy(&thrusterValues, &data.constData()[23], 8);

    return true;
}

char PacketIn::getThrusterStatus() {
    return thrusterStatus;
}

float PacketIn::getPressure(){
    return pressure;
}

float PacketIn::getTemperature() {
    return temperature;
}

qint16 PacketIn::getIMU_X() {
    return IMU_X;
}

qint16 PacketIn::getIMU_Y(){
    return IMU_Y;
}

qint16 PacketIn::getIMU_Z(){
    return IMU_Z;
}

qint16 PacketIn::getIMU_Roll(){
    return IMU_Roll;
}

qint16 PacketIn::getIMU_Pitch(){
    return IMU_Pitch;
}

qint16 PacketIn::getIMU_Yaw(){
    return IMU_Yaw;
}

qint8* PacketIn::getThrusterValues() {
    return thrusterValues;
}

void PacketIn::print() {

//    quint8 tStatus = this->getThrusterStatus();
//    qDebug("T. Stat:\t %d %d %d %d %d %d %d %d",
//           tStatus & 0x80 ? 1 : 0,
//           tStatus & 0x40 ? 1 : 0,
//           tStatus & 0x20 ? 1 : 0,
//           tStatus & 0x10 ? 1 : 0,
//           tStatus & 0x08 ? 1 : 0,
//           tStatus & 0x04 ? 1 : 0,
//           tStatus & 0x02 ? 1 : 0,
//           tStatus & 0x01 ? 1 : 0
//           );

//    qDebug("Pressure:\t %f", this->getPressure());
//    qDebug("Temp:\t %f", this->getTemperature());

//    qDebug("IMU X:\t %d", this->getIMU_X());
//    qDebug("IMU Y:\t %d", this->getIMU_Y());
//    qDebug("IMU Z:\t %d", this->getIMU_Z());

        qDebug("%d %d %d", this->getIMU_X(), this->getIMU_Y(), this->getIMU_Z());

//    qDebug("IMU Roll:\t %d", this->getIMU_Roll());
//    qDebug("IMU Pitch:\t %d", this->getIMU_Pitch());
//    qDebug("IMU Yaw:\t %d", this->getIMU_Yaw());

//      qDebug("%d %d %d %d %d %d %d %d",
//              this->getThrusterValues()[0], this->getThrusterValues()[1], this->getThrusterValues()[2], this->getThrusterValues()[3],
//              this->getThrusterValues()[4], this->getThrusterValues()[5], this->getThrusterValues()[6], this->getThrusterValues()[7]);

      //qDebug("%.3f, %.3f, %.3f, %.3f", this->getPressure(), (float) this->getIMU_Roll()/16, (float) this->getIMU_Pitch()/16, (float)this->getIMU_Yaw()/16);
}
