#include "Sensor.h"

US_Sensor sensor;

void US_Sensor::begin(){
    pinMode(echo, INPUT);
    pinMode(trig, OUTPUT); 
}

bool US_Sensor::Danger(){
      //clears the trigPin
      digitalWrite(trig, LOW);
      delayMicroseconds(2);
      //sets the trigPin on HIGH state for 10ms
      digitalWrite(trig, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig, LOW);

      //reads the echoPin, returns the sound wave travel in microseconds
      duration = pulseIn(echo, HIGH);
      distance = duration/58.2; // distance in cm
      
      if ( distance < 60 || distance > 3) { return false; } else { return true; }    
}
