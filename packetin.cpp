#include "packetin.h"

#include "qbytearray.h"


PacketIn::PacketIn()
{
    sizeOfPacket = 36;
}

bool PacketIn::setData(QByteArray byte) {
    if (crc8(byte, sizeOfPacket) == byte[sizeOfPacket - 2]) {
    char * bytes = byte.data();
    thrusterStatus = bytes[1];
    memcpy(&pressure, &bytes[2], 4);
    memcpy(&temp, &bytes[6], 4);
    memcpy(&IMU_Lx, &bytes[10], 4);
    memcpy(&IMU_Ly, &bytes[14], 4);
    memcpy(&IMU_Lz, &bytes[18], 4);
    memcpy(&IMU_Rx, &bytes[22], 4);
    memcpy(&IMU_Ry, &bytes[26], 4);
    memcpy(&IMU_Rz, &bytes[30], 4);

    return true;
    }
    return false;

}

char PacketIn::getThrusterStatus() {
    return thrusterStatus;
}

float PacketIn::getPressure(){
    return pressure;
}

float PacketIn::getTemp() {
    return temp;
}

float PacketIn::getIMU_Lx() {
    return IMU_Lx;
}

float PacketIn::getIMU_Ly(){
    return IMU_Ly;
}

float PacketIn::getIMU_Lz(){
    return IMU_Lz;
}

float PacketIn::getIMU_Rx(){
    return IMU_Rx;
}

float PacketIn::getIMU_Ry(){
    return IMU_Ry;
}

float PacketIn::getIMU_Rz(){
    return IMU_Rz;
}




char PacketIn::crc8(QByteArray bytes, int size) {
    char crc = 0;
    char val;
    char mix;
    for (int i = 1; i < size - 2; ++i) {
      val = bytes[i];
      for (int j = 8; j; --j) {
        mix = (crc ^ val) & 0x01;
        crc >>= 1;
        if (mix) {
          crc ^= 0xD5;
        }
        val >>= 1;
      }
    }
    return crc;
}


