#ifndef GlobalPositioningSystem
#define GlobalPositioningSystem
//#include <SoftwareSerial.h>
#include <TinyGPS++.h>

#define ss Serial3

const int RXPin = 4, TXPin = 3;
const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;

class GPS_Data{
public:
  //SoftwareSerial ss;
  //GPS_Data(): ss(RXPin, TXPin) {}
  void begin(){ ss.begin(GPSBaud);}
  void getGPS(){
    while (ss.available() > 0){
      gps.encode(ss.read());
    }
  }
  float get_lat(){ return gps.location.lat(); }
  float get_lng(){ return gps.location.lng(); }
  int   get_sat() { return gps.satellites.value(); }
};

#endif
