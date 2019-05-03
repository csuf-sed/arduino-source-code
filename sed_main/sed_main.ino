#include "Motor_Driver.h"
#include "Magnetometer.h"
#include "GPS.h"
#include "Sensor.h"
#include "Bluetooth.h"


//=== variables ===
char blue_char = ' ';       // bluetooth received data
const int led_red = 22;     // LEDs
const int led_green = 23;
const int led_blue = 24;
const int buzzer = 25;

//=== setup ===
void setup() {
  // LEDs setup
  pinMode(led_red,OUTPUT);
  pinMode(led_green,OUTPUT);
  pinMode(led_blue,OUTPUT);
  pinMode(buzzer,OUTPUT);
  digitalWrite(led_blue,HIGH);

  // Modules setup
  motor_driver.begin();
  magnetometer.begin();
  gps.begin();
  //sensor.begin();
  bluetooth.begin(9600);
  while(!bluetooth) {}
  
  digitalWrite(led_blue,LOW);
}

//=== loop ===
void loop() {
  if (bluetooth.available() > 0) {
    blue_char = bluetooth.read();
    if (blue_char == 42) {       // received : *   run : control
      digitalWrite(led_red,LOW);
      digitalWrite(buzzer,HIGH);
      delay(50);
      digitalWrite(buzzer,LOW);
      while(ctrl_loop()) {} 
    }
    else if (blue_char == 103) { // received : g   run : gps
      digitalWrite(led_red,LOW);
      digitalWrite(buzzer,HIGH);
      delay(50);
      digitalWrite(buzzer,LOW);
      delay(50);
      digitalWrite(buzzer,HIGH);
      delay(50);
      digitalWrite(buzzer,LOW);
      while(gps_loop()) {}
    }
  }
  digitalWrite(led_red,LOW);
  delay(500);
  digitalWrite(led_red,HIGH);
  digitalWrite(led_green,LOW);
  digitalWrite(led_blue,LOW);
  delay(500);
}

//=== ctrl_loop ===
bool ctrl_loop() {
  int StopGo = 0;             // moving flag stop == 0, fast == 1, slow == 2
  
  gps.read();
  if (gps.isUpdated()) {
    digitalWrite(buzzer,HIGH);
    bluetooth.print(gps.lat(),6);
    bluetooth.print(',');
    bluetooth.print(gps.lng(),6);
    bluetooth.print('|');
    delay(20);
    digitalWrite(buzzer,LOW);
  }
  
  if (bluetooth.available() > 0) {
    blue_char = bluetooth.read();
    if (blue_char == 69){ // E
      digitalWrite(led_green,LOW);
      digitalWrite(led_blue,HIGH);
      motor_driver.goEast();
      StopGo = 1;
    }
    else if (blue_char == 78){ // N
      digitalWrite(led_green,LOW);
      digitalWrite(led_blue,HIGH);
      motor_driver.goNorth();
      StopGo = 1;
      
//      if (sensor.Danger()){
//        StopGo = 0;
//        motor_driver.stop();
//      }
    }
    else if (blue_char == 83){ // S
      digitalWrite(led_green,LOW);
      digitalWrite(led_blue,HIGH);
      motor_driver.goSouth();
      StopGo = 1;
    }
    else if (blue_char == 87){ // W
      digitalWrite(led_green,LOW);
      digitalWrite(led_blue,HIGH);
      motor_driver.goWest();
      StopGo = 1;
    }
    else if (blue_char == 101) { // e
      motor_driver.goEast();
      StopGo = 2;
    }
    else if (blue_char == 110) { // n
      motor_driver.goNorth();
      StopGo = 2;
    }
    else if (blue_char == 115) { // s
      motor_driver.goSouth();
      StopGo = 2;
    }
    else if (blue_char == 119) { // w
      motor_driver.goWest();
      StopGo = 2;
    }
    else if(blue_char == 49) {   // 1 : Turn Left
      motor_driver.goWest();
      motor_driver.fast(LEFT);
      StopGo = 0;
    }
    else if(blue_char == 50) {   // 2 : Turn Right
      motor_driver.goEast();
      motor_driver.fast(RIGHT);
      StopGo = 0;
    }
    else if (blue_char == 42){ // *
      digitalWrite(led_blue,LOW);
      digitalWrite(led_green,HIGH);
      motor_driver.stop();
      StopGo = 0;
    }
    else if (blue_char == 122) { // z used to get out
      digitalWrite(led_red,LOW);
      digitalWrite(led_blue,LOW);
      digitalWrite(led_green,LOW);
      return false;
    }
  }

  switch (StopGo){
  case 0:
    //motor_driver.stop();
    break;
  case 1:
    motor_driver.fast();
    break;
  case 2:
    motor_driver.slow();
    break;
  }
  
  return true;
}

const float latitude[3] = {33.882621, 33.882655, 33.882677};
const float longtitude[3] = {-117.883726, -117.884034, -117.884254};
void move_to(float dest_lat, float dest_lng);

//=== gps_loop ===
bool gps_loop() {
    digitalWrite(led_green,HIGH);

    magnetometer.readSensor();
    sendDegrees();                                    // BLUETOOTH
    gps.read();
    if (gps.isUpdated()) {
      digitalWrite(buzzer,HIGH);
      delay(100);
      digitalWrite(buzzer,LOW);
      magnetometer.readSensor();
      sendLatLng();                                   // BLUETOOTH
    }
    if (bluetooth.available() > 0) {
      blue_char = bluetooth.read();

      switch(blue_char) {
        case 101:   // e: engineering
          for (int i = 0; i < 3; i++){
            move_to(latitude[i], longtitude[i]);
          }
          digitalWrite(buzzer,HIGH);
          delay(500);
          digitalWrite(buzzer,LOW);
          break;
        case 104:   // h: health
          digitalWrite(buzzer,HIGH);
          digitalWrite(led_green,LOW);
          digitalWrite(led_blue,HIGH);
          delay(500);
          digitalWrite(buzzer,LOW);
          digitalWrite(led_blue,LOW);
          break;
        case 108:   // l: library
          digitalWrite(buzzer,HIGH);
          digitalWrite(led_green,LOW);
          digitalWrite(led_blue,HIGH);
          delay(500);
          digitalWrite(buzzer,LOW);
          digitalWrite(led_blue,LOW);
          break;
        case 122:   // z: exit
          return false;
          break;
        default:    // invalid input
          digitalWrite(buzzer,HIGH);
          digitalWrite(led_green,LOW);
          digitalWrite(led_red,HIGH);
          delay(1000);
          digitalWrite(buzzer,LOW);
          digitalWrite(led_red,LOW);
      }
    }
    delay(200);
    digitalWrite(led_green,LOW);
    delay(200);
    return true;
}

void get_current_location(float &_lat, float &_lng){
  int i = 0;
  _lat = 0;
  _lng = 0;
  while (i < 3) {
    gps.read();
    if (gps.isUpdated()) {
      digitalWrite(buzzer,HIGH);
      delay(20);
      digitalWrite(buzzer,LOW);
      _lat += gps.lat();
      _lng += gps.lng();
      ++i;
    }
  }
  _lat /= 3;
  _lng /= 3;
}

int get_orientation(){
  int _orientation = 0;
  
  for(int i = 0; i < 3; ++i) {
    magnetometer.readSensor();
    _orientation += magnetometer.getDegrees();
    delay(20);
  }
  _orientation /= 3;  

  return _orientation;
}

//void Avoid_Obstacle(float dest_lat, float dest_lng){
//  int _orientation;
//  magnetometer.readSensor();
//  _orientation = magnetometer.getDegrees();
//
//  sensor.read();
//  if ( sensor.distance < 60 ){
//    motor_driver.stop();
//    motor_driver.goSouth();
//    motor_driver.fast();
//    delay(1000);
//    motor_driver.goEast();
//    motor_driver.fast();
//    while (_orientation % 30){
//      motor_driver.goEast();
//      motor_driver.fast();
//      delay(50);
//      magnetometer.readSensor();
//      _orientation = magnetometer.getDegrees();
//    }
//    motor_driver.goNorth();
//    motor_driver.fast();
//  }
//}

const int deg_error = 10;

//--------- To Move ---------------
void move_to(float dest_lat, float dest_lng) {

  digitalWrite(led_green,LOW);
  digitalWrite(led_blue,HIGH);
  int _orientation;
  float _lat=0.0, _lng=0.0;
  
  get_current_location(_lat, _lng);
  sendLatLng(_lat,_lng);                            // BLUETOOTH
  _orientation = get_orientation();
  sendDegrees(_orientation);                        // BLUETOOTH
  
  float _dist = gps.distanceBetween(_lat,_lng,dest_lat,dest_lng);
  float _courseTo = gps.courseTo(_lat,_lng,dest_lat,dest_lng);
  int   _dir = STOP;
  sendDistance(_dist);                              // BLUETOOTH
  sendCourse(_courseTo);                            // BLUETOOTH
  sendDirection(_dir);                              // BLUETOOTH

  while (abs(_courseTo - _orientation) > deg_error) {
    if (magnetometer.turning_angle(_courseTo) < 0.0){
      _dir = LEFT;
      motor_driver.goWest();
    }
    else {
      _dir = RIGHT;
      motor_driver.goEast();
    }
    motor_driver.fast();
    magnetometer.readSensor();
    _orientation = magnetometer.getDegrees();
    sendDegrees();                                // BLUETOOTH
    delay(100);
  }
  
  // GO ----------
  while (_dist > 3.0f) {
    _dir = FORWARD;
    sendDirection(_dir);                          // BLUETOOTH
    motor_driver.goNorth();
    motor_driver.fast();
    
    //Avoid_Obstacle(dest_lat, dest_lng);
    magnetometer.readSensor();
    _orientation = magnetometer.getDegrees(); //update orientation
    sendDegrees(_orientation);                    // BLUETOOTH
    get_current_location(_lat, _lng);  //update current location
    sendLatLng(_lat,_lng);                        // BLUETOOTH
    _dist = gps.distanceBetween(_lat,_lng,dest_lat,dest_lng);
    sendDistance(_dist);                          // BLUETOOTH
    _courseTo = gps.courseTo(_lat,_lng,dest_lat,dest_lng);
    sendCourse(_courseTo);                        // BLUETOOTH
   
    while (abs(_courseTo - _orientation) > deg_error) {
      if (magnetometer.turning_angle(_courseTo) < 0.0){
        _dir = LEFT;
        motor_driver.goWest();
      }
      else {
        _dir = RIGHT;
        motor_driver.goEast();
      }
      motor_driver.fast();
      magnetometer.readSensor();
      _orientation = magnetometer.getDegrees();
      sendDegrees();                                // BLUETOOTH
      sendDirection(_dir);                          // BLUETOOTH
      delay(100);
    }
  } 
  motor_driver.stop();
  digitalWrite(buzzer,HIGH);
  delay(400);
  digitalWrite(buzzer,LOW);
  digitalWrite(led_blue,LOW);
}
