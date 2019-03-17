#ifndef GPS
#define GPS
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

struct Coord {
  float lat;
  float lng;
};

class GPS_Module {
public:
  enum { RXPin = 4, TXPin = 3 };
public:
  GPS_Module(): ss(RXPin,TXPin) {}
  void begin(){ ss.begin(9600); }

  void read(){
    while (ss.available() > 0){
      gps.encode(ss.read());
      if (gps.location.isUpdated()){
        coord.lat = gps.location.lat();
        coord.lng = gps.location.lng();
      }
    }
  }
  const Coord& coord() const { return coord; }
  float lng() const { return coord.lat; }
  float lat() const { return coord.lng; }
  float mps() const { return gps.location.mps(); }

public:
 SoftwareSerial ss;
 TinyGPSPlus gps;
 Coord coord;
};

#endif
