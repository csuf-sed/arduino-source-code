#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

class US_Sensor{ 
public:
  US_Sensor(): echo(13), trig(12) {}
  US_Sensor(int arg_echo, int arg_trig) : echo(arg_echo), trig(arg_trig) {}
  void begin();
  void read();
  long distance() const { return distance_; }
    
public:
  int echo;
  int trig;
  long duration_;
  long distance_;
};

#endif // SENSOR_H
