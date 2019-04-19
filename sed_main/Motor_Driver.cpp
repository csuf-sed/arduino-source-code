#include "Motor_Driver.h"

Motor_Driver motor_driver;

void Motor_Driver::begin() {
  pinMode(ena,OUTPUT);
  pinMode(enb,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  stop();
}

void Motor_Driver::slow() {
  analogWrite(ena,_slow);
  analogWrite(enb,_slow);
}

void Motor_Driver::fast(int dir) {
  if (dir == FORWARD) {
    analogWrite(ena,_fast);
    analogWrite(enb,_fast);
  }
  else if (dir == LEFT) {  // ena
    analogWrite(ena,0);
    analogWrite(enb,_fast);
  }
  else if (dir == RIGHT) { // enb
    analogWrite(ena,_fast);
    analogWrite(enb,0);
  }
}

void Motor_Driver::stop() {
  analogWrite(ena,0);
  analogWrite(enb,0);
}

void Motor_Driver::goNorth() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void Motor_Driver::goSouth() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void Motor_Driver::goEast() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
}

void Motor_Driver::goWest() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
