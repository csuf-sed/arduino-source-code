#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <Arduino.h>

enum DIRECTION { STOP = 0, LEFT = 1, RIGHT = 2, FORWARD = 3 };

class Motor_Driver {
public:
  static const int _fast = 255;
  static const int _slow = 100;
  const int accel = 5;
public:
  Motor_Driver(): ena(9), enb(6), in1(10), in2(11), in3(7), in4(8) {}

  void begin();
  void slow();
  void fast(int dir = FORWARD);
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

extern Motor_Driver motor_driver;

#endif //MOTOR_DRIVER_H
