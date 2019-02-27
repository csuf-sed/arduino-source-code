#include "MPU9250.h"

const float hxb = 22.72279345f;
const float hxs = 0.7950104991f;
const float hyb = 12.57442714f;
const float hys = 0.8012245577f;

class Magnetometer {
public:
  Magnetometer(): IMU(Wire, 0x68) {}

  void begin() {
    IMU.setMagCalX(hxb,hxs);  
    IMU.setMagCalY(hyb,hys);
  }

  float magX() { return IMU.getMagX_uT(); }
  float magY() { return IMU.getMagY_uT(); }
  
public:
  MPU9250 IMU;
};