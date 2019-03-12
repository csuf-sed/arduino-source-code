#include "MPU9250.h"

const float hxb = 22.72279345f;
const float hxs = 0.7950104991f;
const float hyb = 12.57442714f;
const float hys = 0.8012245577f;

class Magnetometer {
public:
  Magnetometer(): IMU(Wire, 0x68) {}

  void begin() {
    IMU.begin();
    IMU.setMagCalX(hxb,hxs);  
    IMU.setMagCalY(hyb,hys);
  }

  void readSensor() { IMU.readSensor(); }

  float getDegrees() {
    float heading = atan2(IMU.getMagX_uT(),IMU.getMagY_uT());
    if (heading < 0)      heading += 2 * PI;
    if (heading > 2 * PI) heading -= 2 * PI;
    return heading * 180 / PI;
  }

  float getRadians() {
    float heading = atan2(IMU.getMagX_uT(),IMU.getMagY_uT());
    if (heading < 0)      heading += 2 * PI;
    if (heading > 2 * PI) heading -= 2 * PI;
    return heading;
  }

  float magX() { return IMU.getMagX_uT(); }
  float magY() { return IMU.getMagY_uT(); }
  
public:
  MPU9250 IMU;
};
