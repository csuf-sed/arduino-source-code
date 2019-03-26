#include <SD.h>
#include "MPU9250.h"

// ==== Variables ====
File file;
const int sd_cs = 4;
const String file_name = "data.txt";
MPU9250 IMU(Wire,0x68);
float hbx = 0, hsx = 0, hby = 0, hsy = 0;
int status;
const int buzz = 2;

void mag() {
  //MPU9250 IMU(Wire,0x68);
    // Setup Magnetometer
  //Serial.println("Initializing Magnetometer...");
  status = IMU.begin();
  if (status < 0) {
    Serial.print("IMU.begin() failed: status = ");
    Serial.println(status);
    while (true) {}
  }
  //Serial.println("Magnetometer initialized.");

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
  
  hbx = IMU.getMagBiasX_uT();
  hsx = IMU.getMagScaleFactorX();
  hby = IMU.getMagBiasY_uT();
  hsy = IMU.getMagScaleFactorY();
//  Serial.println("Data:");
//  Serial.println(hbx,8);
//  Serial.println(hsx,8);
//  Serial.println(hby,8);
//  Serial.println(hsy,8);
//  Serial.println(" ");
}

void card() {
    // Setup the SD card reader
  //Serial.println("Initializing SD card...");
  status = SD.begin(sd_cs);
  if (status < 0) {
    Serial.print("SD.begin() failed, status: ");
    Serial.println(status);
    while(1) {}
  }
  //Serial.println("SD card initialized.");
  
  // Write into file
  //Serial.print("Writing into file..");
  file = SD.open("data.txt",FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file");
    while(1) {}
  }
  file.println("=====================");
  file.println(hbx,8);
  file.println(hsx,8);
  file.println(hby,8);  
  file.println(hsy,8);
  file.close();
}

// ==== SETUP ====
void setup() {
  // Setup Serial
  Serial.begin(9600);
  while (!Serial) {}
  pinMode(sd_cs, OUTPUT);
  digitalWrite(sd_cs,HIGH);
  pinMode(buzz,OUTPUT);
  digitalWrite(buzz,LOW);

  mag();
  card();
  Serial.println("Done");
}

// ==== LOOP ====
void loop() {
  digitalWrite(buzz,HIGH);  
}
