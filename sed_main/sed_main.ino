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

//=== gps_loop ===
bool gps_loop() {
    digitalWrite(led_green,HIGH);
//    delay(100);
//    digitalWrite(led_green,LOW);
//    delay(100);
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

      switch(DaveChar) {
        case 101:   // e: engineering
          digitalWrite(buzzer,HIGH);
          digitalWrite(led_green,LOW);
          digitalWrite(led_blue,HIGH);
          delay(500);
          digitalWrite(buzzer,LOW);
          digitalWrite(led_blue,LOW);
          // Go to engineering
        case 104:   // h: health
          digitalWrite(buzzer,HIGH);
          digitalWrite(led_green,LOW);
          digitalWrite(led_blue,HIGH);
          delay(500);
          digitalWrite(buzzer,LOW);
          digitalWrite(led_blue,LOW);
        case 108:   // l: library
          digitalWrite(buzzer,HIGH);
          digitalWrite(led_green,LOW);
          digitalWrite(led_blue,HIGH);
          delay(500);
          digitalWrite(buzzer,LOW);
          digitalWrite(led_blue,LOW);
        case 122:   // z: exit
          return false;
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
