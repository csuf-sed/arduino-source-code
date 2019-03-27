#ifndef US_SENSOR
#define US_SENSOR

class US_Sensor {
  public:
    US_Sensor(): echo(12), trig(13) {}

    void begin() {
      pinMode(echo, INPUT);
      pinMode(trig, OUTPUT);
    }

    bool danger() {
      digitalWrite(trig, LOW);
      delayMicroseconds(2);
      digitalWrite(trig, HIGH);  //send soundwave
      delayMicroseconds(10);
      digitalWrite(trig, LOW);

      duration = pulseIn(echo, HIGH);  //record soundwave
      distance = duration/58.2;  //distance in cm

      if (distance>60 or distance<3){
        return 0;
      }
      else{
        return 1;
      }
    }

  public:
    int echo;
    int trig;
    long duration;
    long distance;
};
    
#endif
