#include "Sensor.h"

void US_Sensor::begin(){
    pinMode(echo, INPUT);
    pinMode(trig, OUTPUT); 
}

void US_Sensor::read() {
  //clears the trigPin
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  //sets the trigPin on HIGH state for 10ms
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  //reads the echoPin, returns the sound wave travel in microseconds
  duration_ = pulseIn(echo, HIGH);
  distance_ = duration_/58.2; // distance in cm
}
