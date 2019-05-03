#include "MPU9250.h"

// ==== Variables ====
MPU9250 IMU(Wire,0x68);
float hbx = 0, hsx = 0, hby = 0, hsy = 0;
int status;
const int buzz = 2;

void mag() {
  status = IMU.begin();
  if (status < 0) {
    Serial.print("IMU.begin() failed: status = ");
    Serial.println(status);
    while (true) {}
  }

  // Calibration
  Serial.println("Calibrating...");
  status = IMU.calibrateMag();
  if (status < 0) {
    Serial.print("IMU.calibrateMag() failed: status = ");
    Serial.println(status);
    while (true) {}
  }
  
  Serial.println("Calibration succesful.");
  delay(500);
  IMU.readSensor();
  
  Serial.println("Data:");
  Serial.println(hbx,8);
  Serial.println(hsx,8);
  Serial.println(hby,8);
  Serial.println(hsy,8);
  Serial.println(" ");
}

// ==== LOOP ====
void loop() {
  digitalWrite(buzz,HIGH);  
}
