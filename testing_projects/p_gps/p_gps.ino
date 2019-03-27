#include "gps.h"

int buzz = 2;

void setup() {
  Serial.begin(9600);
  gps.begin();
  pinMode(buzz,OUTPUT);
  digitalWrite(buzz,LOW);
}

void loop() {
  if (gps.read()) {
    digitalWrite(buzz,HIGH);
  }
  Serial.println(gps.lat());
  delay(500);
}
