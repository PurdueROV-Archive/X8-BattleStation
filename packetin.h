#ifndef PACKETIN_H
#define PACKETIN_H
#include "qbytearray.h"

class PacketIn
{
public:
    PacketIn();
    char getThrusterStatus() ;
    float getPressure();

    float getTemp();

    float getIMU_Lx();

    float getIMU_Ly();

    float getIMU_Lz();

    float getIMU_Rx();

    float getIMU_Ry();

    float getIMU_Rz();

    bool setData(QByteArray bytes);


private:
    char crc8(QByteArray bytes, int size);

    char thrusterStatus;
    float pressure;
    float temp;
    float IMU_Lx;
    float IMU_Ly;
    float IMU_Lz;
    float IMU_Rx;
    float IMU_Ry;
    float IMU_Rz;


    int sizeOfPacket;

};




#endif // PACKETIN_H
