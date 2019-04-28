#ifndef MAGNETOMETER_H
#define MAGNETOMETER_H

#include "MPU9250.h"

class Magnetometer {
public:
  const float hxb = -6.67241f;
  const float hxs = 0.853901f;
  const float hyb = 13.82588f;
  const float hys = 0.848811f;
public:
  Magnetometer(): IMU(Wire, 0x68) {}
  void begin();

  void readSensor() { IMU.readSensor(); }
  float getDegrees();
  float getRadians();
  float magX() const { return IMU.getMagX_uT(); }
  float magY() const { return IMU.getMagY_uT(); }

  float turning_angle(float courseTo_) const { return static_cast<int>(courseTo_ - getDegrees() + 540)%360 - 180; }
  
public:
  MPU9250 IMU;
};

extern Magnetometer magnetometer;

#endif // MAGNETOMETER_H
