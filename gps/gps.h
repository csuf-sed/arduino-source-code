#ifndef GPS_h
#define GPS_h
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
        c.lat = gps.location.lat();
        c.lng = gps.location.lng();
      }
    }
  }
  const Coord& coord() const { return c; }
  float lng() const { return c.lat; }
  float lat() const { return c.lng; }
  //float mps() const { return gps.mps(); }

public:
 SoftwareSerial ss;
 TinyGPSPlus gps;
 Coord c;
};

#endif
