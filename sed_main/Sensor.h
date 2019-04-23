#ifndef UltraSonic_Sensor
#define UltraSonic_Sensor

#include <Arduino.h>

class US_Sensor{ 
public:
  US_Sensor(): echo(13), trig(12) {}
  void begin();
  bool Danger();
    
public:
  int echo;
  int trig;
  long duration;
  long distance;
};
extern US_Sensor sensor;
#endif
