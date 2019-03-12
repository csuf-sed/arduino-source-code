#include "Motor_Driver.h"
#include "Magnetometer.h"

//=== variables ===
Motor_Driver motor0;      // Motor Drivers
Magnetometer magnet0;     // Magnetometer
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
  delay(200);
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
  if (Serial.available() > 0) {
    DaveChar = Serial.read();
    
   if (DaveChar == 69){ // E
      digitalWrite(led_green,LOW);
      digitalWrite(led_blue,HIGH);
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
      digitalWrite(led_green,LOW);
      digitalWrite(led_blue,HIGH);
      motor0.goSouth();
      StopGo = 1;
    }
    else if (DaveChar == 87){ // W
      digitalWrite(led_green,LOW);
      digitalWrite(led_blue,HIGH);
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
    else if (DaveChar == 42){ // *
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

//=== gps_loop ===
bool gps_loop() {
    digitalWrite(led_green,HIGH);
    delay(500);
    digitalWrite(led_green,LOW);
    delay(500);
    Serial.print(12.345678);
    Serial.print(',');
    Serial.print(-123.456789);
    Serial.print('|');
    

    if (Serial.available() > 0) {
      DaveChar = Serial.read();

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
