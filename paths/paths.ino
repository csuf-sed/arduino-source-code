


class Coord {
  float lat;
  float lng;
};
class Vector {
  float distance;
  float angle;
};

const size_t coord_size = 7;
Coord coord[coord_size] = { {33.882310,-117.883447}, {33.882457,-117.883528}, {33.882588,-117.883684},
{33.882668,-117.883851}, {33.882668,-117.883979}, {33.882668,-117.884108}, {33.882668,-117.884108}}

void update(Coord curr_loc){
  Coord best;
  float best_dist = 200;
  float temp;
  for (size_t i = 0; i < coord_size; ++i) {
    // do the math
    //temp = sqrt(pow(coord[i].lng - curr_loc.lng,2) + pow(coord[i].lat - curr_loc.lat,2));
    if(temp < best_dist) {
      best_dist = temp;
      best = coord[i];
    }
  }
  //calculates the angle
  float courseTo = TinyGPSPlus.courseTo(gps.location.lat(), gps.location.lng,
  best.lng, best.lat);

 //Calculate distance
 float distanceKm = TinyGPSPlus::distanceBetween( curr_loc.lat, curr_loc.lng,  best.lng, best.lat) / 10000000;
}
///---------------------------------WayPoint----------//
void goWaypoint(){
  
  Serial.println("Go to waypoint");
  
  while (true){
    bluetooth();   //connect to blueetoth and see if there is any data received
    if (blueToothVal == 5) { break;}  //if a 'stop' bluetooth command is received then break from the loop
    getCompass(); //update compass heading
    getGPS(); //update GPS location
  }
  
  if (millis() > 5000 && gps.charsProcessed() < 10){ //if no data from GPS within 5 seconds
    Serial1.println("No GPS data: check wiring"));
    }

  //determine distance to destination
  Distance_To_Dest = TinyGPSPlus::distanceBetween(gps.location.lat(),gps.location.lng(), Dest_LAT[ac], Dest_LNG[ac]);
  //determine cardinal point and degrees to distination
  CourseTo = TinyGPSPlus::courseTo(gps.location.lat(),gps.location.lng(),Dest_LAT[ac], Dest_LNG[ac]);
  
  
  if (Distance_To_Dest == 0){ //if vehicle reached its destination
    StopCar();    //stop the robot
    Serial1.println("You have arrived!");
    ac++;   //increment counter for nextWaypoint
    break;
  }

  if (abs(CourseTo - compass_heading) <= 15){
    {Continue_Forward(); } //Go forward
  }else{
    int x = (CourseTo - 360);  //x = GPS desired heading - 360
    int y = (compass_heading - (x)); //y = Compass heading - x
    int z = (y - 360);   // z = y - 360

    if((z <= 180) && ( z >= 0)){  //if z is less than l80 and not a negative value trun left otherwise right
      Turn_Left();
    }
    else{
      Turn_Right();
    }
  }
 }
}

float setHeading(){

  float desired_heading;
  //take several readings from the compass to ensure accuracy
  for (int = 0; i <= 5; i++){
    getCompass();
  }
  desired_heading = compass_heading;
  return desired_heading;
}
  
