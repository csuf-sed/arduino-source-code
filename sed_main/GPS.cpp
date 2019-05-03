#include "gps.h"

TinyGPSPlus tiny_gps;
GPS_Module gps;

void GPS_Module::read(){
  while (GPS_SERIAL.available() > 0){
    tiny_gps.encode(GPS_SERIAL.read());
    if (tiny_gps.location.isUpdated()){
      c_.lat = tiny_gps.location.lat();
      c_.lng = tiny_gps.location.lng();
      updated = true;
      return;
    }
  }
  updated = false;
}

bool  GPS_Module::isUpdated() {
  if (updated == true) {
    updated = false;
    return true;
  }
  else return false;
}

float GPS_Module::distanceBetween(float lat0, float lng0, float lat1, float lng1) {return tiny_gps.distanceBetween(lat0, lng0, lat1, lng1);}
float GPS_Module::distanceBetween(float lat1, float lng1)                         {return tiny_gps.distanceBetween(c_.lat, c_.lng, lat1, lng1);}
float GPS_Module::distanceBetween(Coord coord0, Coord coord1)                     {return tiny_gps.distanceBetween(coord0.lat, coord0.lng, coord1.lat, coord1.lng);}
float GPS_Module::distanceBetween(Coord coord1)                                   {return tiny_gps.distanceBetween(c_.lat, c_.lat, coord1.lat, coord1.lng);}

float GPS_Module::courseTo(float lat0, float lng0, float lat1, float lng1)        {return tiny_gps.courseTo(lat0,lng0,lat1,lng1);}
float GPS_Module::courseTo(float lat1, float lng1)                                {return tiny_gps.courseTo(c_.lat,c_.lng,lat1,lng1);}
float GPS_Module::courseTo(Coord coord0, Coord coord1)                            {return tiny_gps.courseTo(coord0.lat,coord0.lng,coord1.lat,coord1.lng);}
float GPS_Module::courseTo(Coord coord1)                                          {return tiny_gps.courseTo(c_.lat,c_.lng,coord1.lat,coord1.lng);}
