#include "Magnetometer.h"

void Magnetometer::begin() {
  IMU.begin();
  IMU.setMagCalX(hxb,hxs);  
  IMU.setMagCalY(hyb,hys);
}

float Magnetometer::getDegrees() {
  float heading = atan2(IMU.getMagX_uT(),IMU.getMagY_uT());
  if (heading < 0)      heading += 2 * PI;
  if (heading > 2 * PI) heading -= 2 * PI;
  return heading * 180 / PI;
}

float Magnetometer::getRadians() {
  float heading = atan2(IMU.getMagX_uT(),IMU.getMagY_uT());
  if (heading < 0)      heading += 2 * PI;
  if (heading > 2 * PI) heading -= 2 * PI;
  return heading;
}

Magnetometer magnetometer;
