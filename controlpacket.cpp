#include "controlpacket.h"

ControlPacket::ControlPacket() {
    this->data = QByteArray(PACKET_SIZE, 0x00);
    this->defaults();
}

void ControlPacket::setX(qint16 x) {
    this->x = x;
}

void ControlPacket::setY(qint16 y) {
    this->y = y;
}

void ControlPacket::setZ(qint16 z) {
    this->z = z;
}

void ControlPacket::setRoll(qint16 roll) {
    this->roll = roll;
}

void ControlPacket::setPitch(qint16 pitch) {
    this->pitch = pitch;
}

void ControlPacket::setYaw(qint16 yaw) {
    this->yaw = yaw;
}

void ControlPacket::setCameraServo(qint8 angle) {
    this->cameraAngle = angle;
}

void ControlPacket::setSolenoid1(bool on) {
    this->solenoid1 = on;
}
void ControlPacket::setSolenoid2(bool on) {
    this->solenoid2 = on;
}
void ControlPacket::setSolenoid3(bool on) {
    this->solenoid3 = on;
}
void ControlPacket::setSolenoid4(bool on) {
    this->solenoid4 = on;
}

void ControlPacket::setHydraulicPump(quint8 value) {
    this->hydraulicPumpValue = value;
}

void ControlPacket::setLEDValue(quint8 value) {
    this->ledValue = value;
}

void ControlPacket::setThrusterStatus(bool t1, bool t2, bool t3, bool t4, bool t5, bool t6, bool t7, bool t8) {
    this->thrusterStatus[0] = t1;
    this->thrusterStatus[1] = t2;
    this->thrusterStatus[2] = t3;
    this->thrusterStatus[3] = t4;

    this->thrusterStatus[4] = t5;
    this->thrusterStatus[5] = t6;
    this->thrusterStatus[6] = t7;
    this->thrusterStatus[7] = t8;
}

void ControlPacket::setStabilizationLock(bool x, bool y, bool z, bool roll, bool pitch, bool yaw) {
    this->xLock = x;
    this->yLock = y;
    this->zLock = z;

    this->rollLock  = roll;
    this->pitchLock = pitch;
    this->yawLock   = yaw;
}

void ControlPacket::setRotationPConst(qint16 pValue){
    this->rotationPConst = pValue;
}
void ControlPacket::setRotationIConst(qint16 iValue){
    this->rotationIConst = iValue;
}

void ControlPacket::setLocationPConst(qint16 pValue){
    this->locationPConst = pValue;
}
void ControlPacket::setLocationIConst(qint16 iValue){
    this->locationIConst = iValue;
}

void ControlPacket::setPivotX(qint8 value){
    this->pivotX = value;
}
void ControlPacket::setPivotY(qint8 value){
    this->pivotY = value;
}
void ControlPacket::setPivotZ(qint8 value){
    this->pivotZ = value;
}

void ControlPacket::assemblePacket() {
    data[0] = HEADER;
    data[1] = CONTROL;

    memcpy(&this->x,     &data[2],  2);
    memcpy(&this->y,     &data[4],  2);
    memcpy(&this->z,     &data[6],  2);
    memcpy(&this->roll,  &data[8],  2);
    memcpy(&this->pitch, &data[10], 2);
    memcpy(&this->yaw,   &data[12], 2);

    data[14] = this->cameraAngle;

    quint8 solenoidByte = 0;
    solenoidByte += (quint8) (this->solenoid1) ? (2 << 6) : (1 << 6);
    solenoidByte += (quint8) (this->solenoid2) ? (2 << 4) : (1 << 4);
    solenoidByte += (quint8) (this->solenoid3) ? (2 << 2) : (1 << 2);
    solenoidByte += (quint8) (this->solenoid4) ? (2 << 0) : (1 << 6);

    data[15] = solenoidByte;

    data[16] = this->hydraulicPumpValue;

    data[17] = this->ledValue;

    data[18] = (this->thrusterStatus[0] << 7) +
               (this->thrusterStatus[1] << 6) +
               (this->thrusterStatus[2] << 5) +
               (this->thrusterStatus[3] << 4) +
               (this->thrusterStatus[4] << 3) +
               (this->thrusterStatus[5] << 2) +
               (this->thrusterStatus[6] << 1) +
               (this->thrusterStatus[7] << 0);

    data[19] = (this->zLock     << 5) +
               (this->yLock     << 4) +
               (this->zLock     << 3) +
               (this->yawLock   << 2) +
               (this->pitchLock << 1) +
               (this->rollLock  << 0);

    memcpy(&this->rotationPConst, &data[20], 2);
    memcpy(&this->rotationIConst, &data[22], 2);
    memcpy(&this->locationPConst, &data[24], 2);
    memcpy(&this->locationIConst, &data[26], 2);

    data[28] = this->pivotX;
    data[29] = this->pivotY;
    data[30] = this->pivotZ;


    data[PACKET_SIZE-2] = CRC_BYTE;
    data[PACKET_SIZE-1] = TAIL;

    data[PACKET_SIZE-2] = Utilities::crc(data);
}

QByteArray ControlPacket::getPacket() {
    assemblePacket();
    return data;
}

void ControlPacket::defaults() {
    setX(0);
    setY(0);
    setZ(0);

    setRoll(0);
    setPitch(0);
    setYaw(0);

    setCameraServo(0);

    setSolenoid1(0);
    setSolenoid2(0);
    setSolenoid3(0);
    setSolenoid4(0);

    setHydraulicPump(0);

    setLEDValue(0);

    setThrusterStatus(1,1,1,1,1,1,1,1);

    setStabilizationLock(0,0,0,0,0,0);

    setRotationPConst(0);
    setRotationIConst(0);

    setLocationPConst(0);
    setLocationIConst(0);

    setPivotX(0);
    setPivotY(0);
    setPivotZ(0);
}

void ControlPacket::print() {
    assemblePacket();

    qDebug("Header:\t\t 0x%x", data.at(0));
    qDebug("Control:\t 0x0%x", data.at(1));

    qint16 printX = 0;
    memcpy(&printX, &data.constData()[2], 2);

    qint16 printY = 0;
    memcpy(&printY, &data.constData()[4], 2);

    qint16 printZ = 0;
    memcpy(&printZ, &data.constData()[6], 2);

    qDebug("X:\t\t %d", printX);
    qDebug("Y:\t\t %d", printY);
    qDebug("Z:\t\t %d", printZ);

    qint16 printRoll = 0;
    memcpy(&printRoll, &data.constData()[8], 2);

    qint16 printPitch = 0;
    memcpy(&printPitch, &data.constData()[10], 2);

    qint16 printYaw = 0;
    memcpy(&printYaw, &data.constData()[12], 2);

    qDebug("Roll:\t\t %d",  printRoll);
    qDebug("Pitch:\t\t %d", printPitch);
    qDebug("Yaw:\t\t %d",   printYaw);

    qDebug("Cam:\t\t %u", (quint8) data.at(14));

    qDebug("Snoids:\t\t %d%d %d%d %d%d %d%d",
           data.at(15) & 0x80 ? 1 : 0,
           data.at(15) & 0x40 ? 1 : 0,
           data.at(15) & 0x20 ? 1 : 0,
           data.at(15) & 0x10 ? 1 : 0,
           data.at(15) & 0x08 ? 1 : 0,
           data.at(15) & 0x04 ? 1 : 0,
           data.at(15) & 0x02 ? 1 : 0,
           data.at(15) & 0x01 ? 1 : 0
           );

    qDebug("H.Pump:\t\t %d", data.at(16));
    qDebug("LEDs:\t\t %d", data.at(17));

    qDebug("T. Stat:\t %d %d %d %d %d %d %d %d",
           data.at(18) & 0x80 ? 1 : 0,
           data.at(18) & 0x40 ? 1 : 0,
           data.at(18) & 0x20 ? 1 : 0,
           data.at(18) & 0x10 ? 1 : 0,
           data.at(18) & 0x08 ? 1 : 0,
           data.at(18) & 0x04 ? 1 : 0,
           data.at(18) & 0x02 ? 1 : 0,
           data.at(18) & 0x01 ? 1 : 0
           );

    qDebug("PID:\t\t %s", data.at(19) ? "Yes" : "No");

    // Print Extra Info if PID Tuning is On
    if (data.at(19)) {
        qDebug("X Lock:\t %d\n",     data.at(19) & 0x20 ? "Yes" : "No");
        qDebug("Y Lock:\t %d\n",     data.at(19) & 0x10 ? "Yes" : "No");
        qDebug("Z Lock:\t %d\n",     data.at(19) & 0x08 ? "Yes" : "No");

        qDebug("Roll Lock:\t %d\n",  data.at(19) & 0x04 ? "Yes" : "No");
        qDebug("Pitch Lock:\t %d\n", data.at(19) & 0x02 ? "Yes" : "No");
        qDebug("Yaw Lock:\t %d\n",   data.at(19) & 0x01 ? "Yes" : "No");
    }

    qint16 printRotationP = 0;
    memcpy(&printRotationP, &data.constData()[20], 2);

    qint16 printRotationI = 0;
    memcpy(&printRotationI, &data.constData()[22], 2);

    qint16 printLocationP = 0;
    memcpy(&printLocationP, &data.constData()[24], 2);

    qint16 printLocationI = 0;
    memcpy(&printLocationI, &data.constData()[26], 2);

    qDebug("Rot P:\t\t %d", printRotationP);
    qDebug("Loc I:\t\t %d", printRotationI);
    qDebug("Rot P:\t\t %d", printLocationP);
    qDebug("Loc I:\t\t %d", printLocationI);

    qDebug("Pivot X:\t %d", (qint8) data.at(28));
    qDebug("Pivot Y:\t %d", (qint8) data.at(29));
    qDebug("Pivot Z:\t %d", (qint8) data.at(30));

    qDebug("Check:\t\t 0x%x", (quint8) data.at(PACKET_SIZE-2));
    qDebug("Tail:\t\t 0x%x", data.at(PACKET_SIZE-1));
}
