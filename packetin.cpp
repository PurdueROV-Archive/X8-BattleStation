#include "packetin.h"




PacketIn::PacketIn()
{

}

bool PacketIn::setData(char *bytes) {
    if (bytes == NULL) return NULL;
    if (crc8(bytes, sizeOfPacket) == bytes[sizeOfPacket - 2]) {
    header = bytes[0];
    thrusterStatus = bytes[1];
    memcpy(&pressure, &pressure, 4);
    memcpy(&temp, &temp, 4);
    memcpy(&IMU_Lx, &IMU_Lx, 4);
    memcpy(&IMU_Ly, &IMU_Ly, 4);
    memcpy(&IMU_Lz, &IMU_Lz, 4);
    memcpy(&IMU_Rx, &IMU_Rx, 4);
    memcpy(&IMU_Ry, &IMU_Ry, 4);
    memcpy(&IMU_Rz, &IMU_Rz, 4);
    CRC8_Check = bytes[34];
    tailByte = bytes[35];
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




char PacketIn::crc8(char bytes[], int size) {
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



