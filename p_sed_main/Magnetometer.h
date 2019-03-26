#include "MPU9250.h"

const float hxb = -8.874619289f;
const float hxs = 0.89632523f;
const float hyb = 19.04453754f;
const float hys = 0.88371754f;

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
