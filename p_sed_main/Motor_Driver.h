#ifndef MOTOR_DRIVER
#define MOTOR_DRIVER

class Motor_Driver {
public:
  static const int _fast = 255;
  static const int _slow = 180;
public:
  Motor_Driver(): ena(9), enb(6), in1(10), in2(11), in3(7), in4(8) {}

  void begin() {
    pinMode(ena,OUTPUT);
    pinMode(enb,OUTPUT);
    pinMode(in1,OUTPUT);
    pinMode(in2,OUTPUT);
    pinMode(in3,OUTPUT);
    pinMode(in4,OUTPUT);
    stop();
  }

  void slow() {
    analogWrite(ena,_slow);
    analogWrite(enb,_slow);
  }

  void fast() {
    analogWrite(ena,_fast);
    analogWrite(enb,_fast);
  }

  void stop() {
    analogWrite(ena,0);
    analogWrite(enb,0);
  }

  void goNorth() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }

  void goSouth() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }

  void goEast() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }

  void goWest() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  
public:
  int ena;  // PWM
  int enb; // PWM
  int in1;
  int in2;
  int in3;
  int in4; 
};

#endif
