#ifndef GPS_h
#define GPS_h
#include "Arduino.h"
#include <TinyGPS++.h>

#define GPS_SERIAL Serial3

struct Coord {
  float lat;
  float lng;
};

class GPS_Module {
public:
  GPS_Module() = default;
  void begin(unsigned int bitrate = 9600){ GPS_SERIAL.begin(bitrate); }

  bool read();
  const Coord& coord() const { return c; }
  float lng() const { return c.lat; }
  float lat() const { return c.lng; }
  //float mps() const { return gps.location.mps(); }

public:
 TinyGPSPlus gps;
 Coord c;
};

extern GPS_Module gps;

#endif // GPS_h
