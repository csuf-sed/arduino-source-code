#include "gps.h"


gps_location data;

void setup(){

  data.begin();
  Serial.begin(9600);
  
  while(!Serial){}
  Serial.println("Start!");
}

void loop(){
 data.read();
 Serial.print("Latitude:");
 Serial.print(data.get_lat(),6);
 Serial.print("\t");
 Serial.print("Longtitude:");
 Serial.print(data.get_lng(),6);
 Serial.println();

 delay(1000);
  
}
