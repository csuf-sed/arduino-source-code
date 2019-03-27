#include "gps.h"

GPS_Module gps;

bool GPS_Module::read(){
  while (GPS_SERIAL.available() > 0){
    gps.encode(GPS_SERIAL.read());
    if (gps.location.isUpdated()){
      c.lat = gps.location.lat();
      c.lng = gps.location.lng();
      return true;
    }
  }
  return false;
}
