#include "GPS.h"

GPS_Data data;

void setup(){
  Serial.begin(9600);
  data.begin();
}

void loop(){
 data.getGPS();
 if (gps.location.isUpdated()){
   Serial.print(data.get_lat(),6);
   Serial.print(' ');
   Serial.print(data.get_lng(), 6);
   Serial.print(' ');
   Serial.println(data.get_sat());
 }
}
