#ifndef GPS_h
#define GPS_h

#include "Arduino.h"
#include <TinyGPS++.h>
#define GPS_SERIAL Serial3

struct Coord { float lat; float lng; };

class GPS_Module {
public:
  const uint32_t GPSBaud = 9600;
public:
  GPS_Module() = default;
  void  begin(unsigned int bitrate = 9600){ GPS_SERIAL.begin(bitrate); }
  void  read();
  bool  isUpdated();
  const Coord& coord() const {return c_;}
  float lng() const {return c_.lat;}
  float lat() const {return c_.lng;}
  int   sat() const {return gps_.satellites.value();}
  
  float distanceBetween(float lat0, float lng0, float lat1, float lng1);
  float distanceBetween(float lat1, float lng1);
  float distanceBetween(Coord coord0, Coord coord1);
  float distanceBetween(Coord coord1);
  
  float courseTo(float lat0, float lng0, float lat1, float lng1);
  float courseTo(float lat1, float lng1);
  float courseTo(Coord coord0, Coord coord1);
  float courseTo(Coord coord1);
  
public:
 TinyGPSPlus gps_;
 Coord       c_;
 bool        updated;
};

extern GPS_Module gps;

#endif // GPS_h
