#ifndef GPS_h
#define GPS_h

#include <TinyGPS++.h>

#define GPS_SERIAL Serial3
extern TinyGPSPlus tiny_gps;

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
  float lat() const {return c_.lat;}
  float lng() const {return c_.lng;}
  int   sat() const {return tiny_gps.satellites.value();}
  
  float distanceBetween(float lat0, float lng0, float lat1, float lng1);
  float distanceBetween(float lat1, float lng1);
  float distanceBetween(Coord coord0, Coord coord1);
  float distanceBetween(Coord coord1);
  
  float courseTo(float lat0, float lng0, float lat1, float lng1);
  float courseTo(float lat1, float lng1);
  float courseTo(Coord coord0, Coord coord1);
  float courseTo(Coord coord1);
  
public:
 Coord       c_;
 bool        updated;
};

extern GPS_Module gps;

#endif // GPS_h
