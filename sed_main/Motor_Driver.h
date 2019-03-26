#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <Arduino.h>

class Motor_Driver {
public:
  static const int _fast = 255;
  static const int _slow = 180;
public:
  Motor_Driver(): ena(9), enb(6), in1(10), in2(11), in3(7), in4(8) {}

  void begin();

  void slow();
  void fast();
  void stop();

  void goNorth();
  void goSouth();
  void goEast();
  void goWest();
  
public:
  int ena;  // PWM
  int enb; // PWM
  int in1;
  int in2;
  int in3;
  int in4; 
};

#endif //MOTOR_DRIVER_H
