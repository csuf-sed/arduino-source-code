#include <SD.h>


const int sd_cs = 4;
const String file_name = "data.txt";
File file;

void setup() {
  // Setup Serial
  Serial.begin(9600);
  while (!Serial) {}
  Serial.print("Initializing SD card...");
  
  // Setup the SD card reader
  pinMode(sd_cs, OUTPUT);
  digitalWrite(sd_cs,HIGH);
  int status = SD.begin(sd_cs);
  if (status < 0) {
    Serial.print("SD.begin() failed, status: ");
    Serial.println(status);
    while(1) {}
  }
  Serial.println("SD card initialized.");
  
  // Write into file
  Serial.print("Writing into ");
  Serial.print(file_name);
  Serial.println("...");
  file = SD.open(file_name,FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file");
    while(1) {}
  }
  file.println("Data and stuff...");
  file.println("Style and stuff");
  file.println("Does this work as well?");
  file.close();
  Serial.println("Done");
}

void loop() {}
