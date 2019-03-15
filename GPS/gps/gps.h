#ifndef GPS
#define GPS
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

struct Coord {
  float lat;
  float lng;
  float mps;
};

const int RXPin = 3, TXPin = 4;
class gps_location {
public:
public:
  gps_location(): ss(RXPin,TXPin) {}
  void begin(){ ss.begin(9600); }


  void read(){
    while (ss.available() > 0){
    gps.encode(ss.read());
      if (gps.location.isUpdated()){
        coord.lat = gps.location.lat();
        coord.lng = gps.location.lng();
        coord.mps = gps.speed.mps();
      }
    }
  }

  float get_lng(){
    return coord.lat;
  }

  float get_lat(){
    return coord.lng;
  }

  float get_mps() {
    return coord.mps;
  }

public:
 SoftwareSerial ss;
 TinyGPSPlus gps;
 Coord coord;
};

#endif
