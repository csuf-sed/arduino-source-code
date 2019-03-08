#include <SD.h>


const int chipSelect = 4;
File file;

void setup() {
 Serial.begin(9600);
 while (!Serial) {}
 Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(chipSelect, OUTPUT);
  digitalWrite(chipSelect,HIGH);
 
 // see if the card is present and can be initialized:
 if (!SD.begin(chipSelect)) {
   Serial.println("Card failed, or not present");
   return;
 }
 Serial.println("card initialized.");
 
  file = SD.open("data.txt",FILE_WRITE);
  if (file) {
    file.write("Data and stuff...");
    file.write("Style and crap...");
    file.close();
    Serial.println("Done");
  }
  else {
    Serial.println("magnetometer.txt file broke or something");
    file.println("You broken?");
    file.close();
  }
 
}

void loop() {
}
