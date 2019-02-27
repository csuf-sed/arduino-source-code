#include "Motor_Driver.h"

//=== variables ===
Motor_Driver motor0;      // motor
Magnetometer magnet0;
char DaveChar = ' ';      // bluetooth received data
int StopGo = 0;           // moving flag stop == 0, fast == 1, slow == 2
const int led_red = 22;   // LEDs
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
  
  motor0.begin();

  magnet0.begin();

  Serial.begin(9600);
  while(!Serial) {}
  delay(500);
  digitalWrite(led_blue,LOW);
}


//=== loop ===
void loop() {
  if (Serial.available() > 0) {
    DaveChar = Serial.read();
    if (DaveChar == 42) { // received : *   run : control
      digitalWrite(led_red,LOW);
      digitalWrite(buzzer,HIGH);
      delay(50);
      digitalWrite(buzzer,LOW);
      while(gps_loop()) {} 
    }
  }
  delay(200);
  digitalWrite(led_red,HIGH);
  digitalWrite(led_green,LOW);
  digitalWrite(led_blue,LOW);
}

//=== gps_loop ===
bool gps_loop() {
  if (Serial.available() > 0) {
    DaveChar = Serial.read();
    
   if (DaveChar == 69){ // E
      motor0.goEast();
      StopGo = 1;
    }
    else if (DaveChar == 78){ // N
      digitalWrite(led_green,LOW);
      digitalWrite(led_blue,HIGH);
      motor0.goNorth();
      StopGo = 1;
    }
    else if (DaveChar == 83){ // S
      motor0.goSouth();
      StopGo = 1;
    }
    else if (DaveChar == 87){ // W
      motor0.goWest();
      StopGo = 1;
    }
    else if (DaveChar == 101) { // e
      motor0.goEast();
      StopGo = 2;
    }
    else if (DaveChar == 110) { // n
      motor0.goNorth();
      StopGo = 2;
    }
    else if (DaveChar == 115) { // s
      motor0.goSouth();
      StopGo = 2;
    }
    else if (DaveChar == 119) { // w
      motor0.goWest();
      StopGo = 2;
    }
    else if (DaveChar == 42){
      digitalWrite(led_blue,LOW);
      digitalWrite(led_green,HIGH);
      motor0.stop();
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
    //motor0.stop();
    break;
  case 1:
    motor0.fast();
    break;
  case 2:
    motor0.slow();
    break;
  }
  
  return true;
}
