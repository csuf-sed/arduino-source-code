//======================
// Bluetooth Module
//======================
// Instructions:
// call bluetooth.begin(9600) in setup()
// call on of the functions below to transmit data to through the bluetooth module unto the phone

#ifndef BLUETOOTH_H
#define BLUETOOTH_H
#include "Arduino.h"
#include "GPS.h"
#include "Magnetometer.h"

#define bluetooth Serial1

inline void sendLatLng() {
  bluetooth.print(gps.lat(), 6);
  bluetooth.print(',');
  bluetooth.print(gps.lng(), 6);
  bluetooth.print('|');
}

inline void sendLatLng(float lat_, float lng_) {
  bluetooth.print(lat_, 6);
  bluetooth.print(',');
  bluetooth.print(lng_, 6);
  bluetooth.print('|');
}

inline void sendDegrees() {
  bluetooth.print(magnetometer.getDegrees(), 2);
  bluetooth.print('w');
}

inline void sendDegrees(float degrees_) {
  bluetooth.print(degrees_, 2);
  bluetooth.print('w');
}

inline void sendDistance(float _dist) {
  bluetooth.print(_dist);
  bluetooth.print('n');
}

inline void sendCourse(float _course) {
  bluetooth.print(_course);
  bluetooth.print('t');
}

void sendDirection(short _dir = 0) {
  switch(_dir) {
  case STOP:
    bluetooth.print("STOP");
    break;
  case LEFT:
    bluetooth.print("LEFT");
    break;
  case RIGHT:
    bluetooth.print("RIGHT");
    break;
  case FORWARD:
    bluetooth.print("FORWARD");
    break;
  default:
    bluetooth.print("-");
    break;
  }
  bluetooth.print('y');
}

#endif // BLUETOOTH_H
