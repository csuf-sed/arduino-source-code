#include "Magnetometer.h"

Magnetometer magnet0;

void setup() {
  // put your setup code here, to run once:
  magnet0.begin();

  Serial.begin(9600);
  while(!Serial) {}

  Serial.println("Start!");
}

void loop(){

  float heading = atan2(magnet0.magX(), magnet0.magY());

  if (heading < 0){
    heading += 2 * PI;
  }

  if ( heading > 2 * PI){
    heading -= 2 * PI;
  }

  //convert heading Degrees
  float headingDeg =  heading * 180/M_PI;

  Serial.print(" Heading = ");
  Serial.print(heading);
  Serial.print(" Degress = ");
  Serial.print(headingDeg);
  Serial.println();

  delay(1000);
}
