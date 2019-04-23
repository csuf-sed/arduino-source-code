#include "Motor_Driver.h"
#include "Magnetometer.h"
#include "GPS.h"
#include "Sensor.h"


//=== variables ===
#define bluetooth Serial1   // defines the serial for the bluetooth
char DaveChar = ' ';        // bluetooth received data
int StopGo = 0;             // moving flag stop == 0, fast == 1, slow == 2
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

  motor_driver.begin();
  magnetometer.begin();
  gps.begin();
  sensor.begin();

  bluetooth.begin(9600);
  while(!bluetooth) {}
  digitalWrite(led_blue,LOW);
}

//=== loop ===
void loop() {
  if (bluetooth.available() > 0) {
    DaveChar = bluetooth.read();
    if (DaveChar == 42) {       // received : *   run : control
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
    else if(DaveChar == 49) {   // 1 : Turn Left
      motor_driver.goWest();
      motor_driver.fast(LEFT);
      StopGo = 0;
    }
    else if(DaveChar == 50) {   // 2 : Turn Right
      motor_driver.goEast();
      motor_driver.fast(RIGHT);
      StopGo = 0;
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

void Avoid_Obstacle(){
  while ( sensor.Danger() ){
    motor_driver.stop();
    motor_driver.goSouth();
    delay(50);
    motor_driver.goEast();
  }
  motor_driver.goNorth();
}

const float latitude [3] = {33.882621, 33.882674, 33.882677};
const float longtitude [3] = {-117.883726, -117.884042, -117.884254};
void move_to(float dest_lat, float dest_lng);

void sendBluetooth(float _sat,float _dist = 0.0f, float _course = 0.0f, int _dir = 0) {
  bluetooth.print(gps.lat(),6);
  bluetooth.print(',');
  bluetooth.print(gps.lng(),6);
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
    
    gps.read();
    if (gps.isUpdated()) {
      digitalWrite(buzzer,HIGH);
      delay(200);
      digitalWrite(buzzer,LOW);

      bluetooth.print(gps.lat(),6);
      bluetooth.print(',');
      bluetooth.print(gps.lng(),6);
      bluetooth.print('|');
      bluetooth.print(gps.sat());
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
          for (int i = 0; i < 3; i++){
            move_to(latitude[i], longtitude[i]);
          }
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
void move_to(float dest_lat, float dest_lng) {

  digitalWrite(led_green,LOW);
  digitalWrite(led_blue,HIGH);
  // Determine current location
  float _lat = 0;
  float _lng = 0;
  int i = 0;
  while (i < 5) {
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
  _lat /= 5;
  _lng /= 5;
  //Determine orientation
  float _orientation = 0;
  for(int i = 0; i < 5; ++i) {
    magnetometer.readSensor();
    _orientation += magnetometer.getDegrees();
    delay(20);
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
    magnetometer.readSensor();
    _orientation = magnetometer.getDegrees();
    
    int i = 0;
    _lat = 0;
    _lng = 0;
    while (i < 2) {
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
    _lat /= 2;
    _lng /= 2;
    _dist = gps.distanceBetween(_lat,_lng,dest_lat,dest_lng);
    courseTo = gps.courseTo(_lat,_lng,dest_lat,dest_lng);
    magnetometer.readSensor();
    _orientation += magnetometer.getDegrees();
    _orientation /= 2;
    while (_orientation - courseTo > 10) {
      _dir = LEFT;
      motor_driver.goWest();
      delay(50);
      magnetometer.readSensor();
      _orientation = magnetometer.getDegrees();
      sendBluetooth(gps.sat(),_dist,courseTo,_dir);          // BLUETOOTH
    }
    while (courseTo - _orientation > 10) {
      _dir = RIGHT;
      motor_driver.goEast();
      delay(50);
      magnetometer.readSensor();
      _orientation = magnetometer.getDegrees();
      sendBluetooth(gps.sat(),_dist,courseTo,_dir);          // BLUETOOTH
    }
    sendBluetooth(gps.sat(),_dist,courseTo,_dir);              // BLUETOOTH
  }
  motor_driver.stop();
  digitalWrite(buzzer,HIGH);
  delay(700);
  digitalWrite(buzzer,LOW);
  digitalWrite(led_blue,LOW);
}
