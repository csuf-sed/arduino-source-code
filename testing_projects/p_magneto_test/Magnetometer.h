#ifndef MAGNETOMETER
#define MAGNETOMETER
#include "MPU9250.h"

const float hxb = 22.72279345f;
const float hxs = 0.7950104991f;
const float hyb = 12.57442714f;
const float hys = 0.8012245577f;
const float hzb = 5.0f;
const float hzs = 0.6f;

class Magnetometer {
public:
  Magnetometer(): IMU(Wire, 0x68) {}

  void begin() {
    IMU.begin();
    IMU.setMagCalX(hxb,hxs);  
    IMU.setMagCalY(hyb,hys);
    //IMU.setMagCalZ(hzb,hzs);
  }

  float magX() { 
    IMU.readSensor();
    return IMU.getMagX_uT(); }
  float magY() { 
    IMU.readSensor();
    return IMU.getMagY_uT(); }
  
public:
  MPU9250 IMU;
};

#endif
