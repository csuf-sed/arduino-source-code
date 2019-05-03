#include "Sensor.h"

US_Sensor sensor_left(27,26);
US_Sensor sensor_front(13,12);

void setup() {
  Serial.begin(9600);
  while(!Serial) {}
  sensor_front.begin();
  sensor_left.begin();
}

void loop() {
  sensor_left.read();
  if (sensor_left.distance() < 60)
    Serial.println("Danger!");
  Serial.println(sensor_left.distance());
  delay(500);
}
