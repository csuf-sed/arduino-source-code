#include "gps.h"

int buzz = 25;

void setup() {
  Serial.begin(9600);
  gps.begin();
  pinMode(buzz,OUTPUT);
  digitalWrite(buzz,LOW);
}

void loop() {
  if (gps.read()) {
    digitalWrite(buzz,HIGH);
    Serial.print(gps.lat(),6);
    Serial.print(' ');
    Serial.println(gps.sat());
    delay(250);
    digitalWrite(buzz,LOW);
  }
  
  delay(500);
}
