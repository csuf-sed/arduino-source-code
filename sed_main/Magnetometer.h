#ifndef MAGNETOMETER_H
#define MAGNETOMETER_H

#include "MPU9250.h"

class Magnetometer {
public:
  const float hxb = -8.874619289f;
  const float hxs = 0.89632523f;
  const float hyb = 19.04453754f;
  const float hys = 0.88371754f;
public:
  Magnetometer(): IMU(Wire, 0x68) {}
  void begin();

  void readSensor() { IMU.readSensor(); }
  float getDegrees();
  float getRadians();
  float magX() { return IMU.getMagX_uT(); }
  float magY() { return IMU.getMagY_uT(); }
  
public:
  MPU9250 IMU;
};

extern Magnetometer magnetometer;

#endif // MAGNETOMETER_H
