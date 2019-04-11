#include "Motor_Driver.h"
#include "Magnetometer.h"
#include "GPS.h"

//=== variables ===
#define bluetooth Serial1      // defines the serial for the bluetooth
char DaveChar = ' ';      // bluetooth received data
int StopGo = 0;           // moving flag stop == 0, fast == 1, slow == 2
const int led_red = 22;   // LEDs
const int led_green = 23;
const int led_blue = 24;
const int buzzer = 25;
GPS_Data data;

//comment

//=== setup ===
void setup() {
  Serial.begin(9600);
  // LEDs setup
  pinMode(led_red,OUTPUT);
  pinMode(led_green,OUTPUT);
  pinMode(led_blue,OUTPUT);
  pinMode(buzzer,OUTPUT);
  digitalWrite(led_blue,HIGH);
  
  motor_driver.begin();
  magnetometer.begin();
  data.begin();

  bluetooth.begin(9600);
  while(!bluetooth) {}
  digitalWrite(led_blue,LOW);
}


//=== loop ===
void loop() {
  if (bluetooth.available() > 0) {
    DaveChar = bluetooth.read();
    if (DaveChar == 42) { // received : *   run : control
      digitalWrite(led_red,LOW);
      digitalWrite(buzzer,HIGH);
      delay(50);
      digitalWrite(buzzer,LOW);
      while(ctrl_loop()) {} 
    }
    else if (DaveChar == 103) { // received : g   run : gps
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
  data.getGPS();
  if (gps.location.isUpdated()) {
    digitalWrite(buzzer,HIGH);
    bluetooth.print(data.get_lat(),6);
    bluetooth.print(',');
    bluetooth.print(data.get_lng(),6);
    bluetooth.print('|');
    delay(200);
    digitalWrite(buzzer,LOW);
  }
  
  if (bluetooth.available() > 0) {
    DaveChar = bluetooth.read();
    if (DaveChar == 69){ // E
      digitalWrite(led_green,LOW);
      digitalWrite(led_blue,HIGH);
      motor_driver.goEast();
      StopGo = 1;
    }
    else if (DaveChar == 78){ // N
      digitalWrite(led_green,LOW);
      digitalWrite(led_blue,HIGH);
      motor_driver.goNorth();
      StopGo = 1;
    }
    else if (DaveChar == 83){ // S
      digitalWrite(led_green,LOW);
      digitalWrite(led_blue,HIGH);
      motor_driver.goSouth();
      StopGo = 1;
    }
    else if (DaveChar == 87){ // W
      digitalWrite(led_green,LOW);
      digitalWrite(led_blue,HIGH);
      motor_driver.goWest();
      StopGo = 1;
    }
    else if (DaveChar == 101) { // e
      motor_driver.goEast();
      StopGo = 2;
    }
    else if (DaveChar == 110) { // n
      motor_driver.goNorth();
      StopGo = 2;
    }
    else if (DaveChar == 115) { // s
      motor_driver.goSouth();
      StopGo = 2;
    }
    else if (DaveChar == 119) { // w
      motor_driver.goWest();
      StopGo = 2;
    }
    else if (DaveChar == 42){ // *
      digitalWrite(led_blue,LOW);
      digitalWrite(led_green,HIGH);
      motor_driver.stop();
      StopGo = 0;
    }
    else if (DaveChar == 122) { // z used to get out
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

const float dest_lat = 33.882110;
const float dest_lng = -117.883544;

enum DIRECTION { STOP = 0, LEFT = 1, RIGHT = 2, FORWARD = 3 };

void sendBluetooth(float _sat,float _dist = 0.0f, float _course = 0.0f, int _dir = 0) {
  bluetooth.print(data.get_lat(),6);
  bluetooth.print(',');
  bluetooth.print(data.get_lng(),6);
  bluetooth.print('|');
  bluetooth.print(_sat);
  bluetooth.print('q');
  magnetometer.readSensor();
  bluetooth.print(magnetometer.getDegrees(),2);
  bluetooth.print('w');
  bluetooth.print(_dist,6);
  bluetooth.print('n');
  bluetooth.print(_course,6);
  bluetooth.print('t');
  switch(_dir) {
    case STOP:
      bluetooth.print("STOP");
      break;
    case LEFT:
      bluetooth.print("LEFT");
      break;
    case RIGHT:
      bluetooth.print("RIGHT");
      break;
    case FORWARD:
      bluetooth.print("FORWARD");
      break;
    default:
      bluetooth.print("-");
      break;
  }
  bluetooth.print('y');
}

//=== gps_loop ===
bool gps_loop() {
    digitalWrite(led_green,HIGH);
    
    data.getGPS();
    if (gps.location.isUpdated()) {
      digitalWrite(buzzer,HIGH);
      delay(200);
      digitalWrite(buzzer,LOW);

      bluetooth.print(data.get_lat(),6);
      bluetooth.print(',');
      bluetooth.print(data.get_lng(),6);
      bluetooth.print('|');
      bluetooth.print(data.get_sat());
      bluetooth.print('q');
      magnetometer.readSensor();
      bluetooth.print(magnetometer.getDegrees(),2);
      bluetooth.print('w');
      bluetooth.print(0.0,6);
      bluetooth.print('n');
      bluetooth.print(0.0,6);
      bluetooth.print('t');
      bluetooth.print("STOP");
      bluetooth.print('y');
    }
    if (bluetooth.available() > 0) {
      DaveChar = bluetooth.read();

      switch(DaveChar) {
        case 101:   // e: engineering
          move_to();
          break;
          // Go to engineering
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
    return true;
}

//--------- To Move ---------------
void move_to() {
  digitalWrite(led_green,LOW);
  digitalWrite(led_blue,HIGH);
  // Determine current location
  float _lat = 0;
  float _lng = 0;
  int i = 0;
  while (i < 5) {
    data.getGPS();
    if (gps.location.isUpdated()) {
      digitalWrite(buzzer,HIGH);
      delay(50);
      digitalWrite(buzzer,LOW);
      _lat += data.get_lat();
      _lng += data.get_lng();
      ++i;
    }
  }
  _lat /= 5;
  _lng /= 5;
  //Determine orientation
  float _orientation = 0;
  for(int i = 0; i < 5; ++i) {
    magnetometer.readSensor();
    _orientation += magnetometer.getDegrees();
    delay(50);
  }
  _orientation /= 5;

  float _dist = gps.distanceBetween(_lat,_lng,dest_lat,dest_lng);
  float courseTo = gps.courseTo(_lat,_lng,dest_lat,dest_lng);
  int   _dir = STOP;

  while (abs(_orientation - courseTo) > 15) {
    motor_driver.goEast();
    motor_driver.fast();
    magnetometer.readSensor();
    _orientation = magnetometer.getDegrees();
  }
  motor_driver.stop();
  // GO ----------
  while (_dist > 3.0f) {
    _dir = FORWARD;
    motor_driver.goNorth();
    motor_driver.fast();
    int i = 0;
    _lat = 0;
    _lng = 0;
    while (i < 2) {
      data.getGPS();
      if (gps.location.isUpdated()) {
        digitalWrite(buzzer,HIGH);
        delay(40);
        digitalWrite(buzzer,LOW);
        _lat += data.get_lat();
        _lng += data.get_lng();
        ++i;
      }
    }
    _lat /= 2;
    _lng /= 2;
    courseTo = gps.courseTo(_lat,_lng,dest_lat,dest_lng);
    magnetometer.readSensor();
    _orientation = magnetometer.getDegrees();
    sendBluetooth(data.get_sat(),_dist,courseTo,_dir);            // BLUETOOTH
    while (_orientation - courseTo > 10) {
      _dir = LEFT;
      motor_driver.goWest();
      delay(50);
      magnetometer.readSensor();
      _orientation = magnetometer.getDegrees();
      //sendBluetooth(data.get_sat(),_dist,courseTo,_dir);          // BLUETOOTH
    }
    while (courseTo - _orientation > 10) {
      _dir = RIGHT;
      motor_driver.goEast();
      delay(50);
      magnetometer.readSensor();
      _orientation = magnetometer.getDegrees();
      //sendBluetooth(data.get_sat(),_dist,courseTo,_dir);          // BLUETOOTH
    }
    _dist = gps.distanceBetween(_lat,_lng,dest_lat,dest_lng);
  }
  motor_driver.stop();
  digitalWrite(buzzer,HIGH);
  delay(500);
  digitalWrite(buzzer,LOW);
  digitalWrite(led_blue,LOW);
}
