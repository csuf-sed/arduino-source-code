#include "GPS.h"

GPS_Module g;

void setup() {
  Serial.begin(9600);
  g.begin();
}

void loop() {
  g.read();
  Serial.println(g.lat(),6);
  delay(500);
}
