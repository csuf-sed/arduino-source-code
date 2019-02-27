#include "Magnetometer.h"

Magnetometer magnet0;

void setup() {
  // put your setup code here, to run once:
  magnet0.begin();

  Serial.begin(9600);
  while(!Serial) {}

  Serial.println("Start!");
}

void loop() {
  Serial.print("x: ");
  Serial.println(String(magnet0.magX(),6));
  Serial.print("y: ");
  Serial.println(String(magnet0.magY(),6));
  delay(1000);
}
