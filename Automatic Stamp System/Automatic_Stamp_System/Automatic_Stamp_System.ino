#include <Servo.h>

#define sensor A0
#define motor 2

Servo myservo;
byte max = 96, min= 145;
bool nilai, prevSensor;
int pos;
void setup() {
  Serial.begin(9600);
  myservo.attach(9);
  pinMode(sensor, INPUT);
  pinMode(motor, OUTPUT);

  myservo.write(min);
  delay(1000);
  digitalWrite(motor, LOW);
}

void loop() {
  nilai = digitalRead(sensor);
  Serial.println(nilai);
  if(prevSensor != nilai){
    if(nilai == 0){
      stamp();
    }
    prevSensor = nilai;
  }
}

void stamp(){
    digitalWrite(motor, HIGH); // Motor OFF
    delay(500);
    for(pos = min; pos >= max; pos--){
      myservo.write(pos);
      delay(8);
    }
    delay(2000);
    for(pos = max; pos <= min; pos++){
      myservo.write(pos);
      delay(8);
    }
    delay(500);
    digitalWrite(motor, LOW); // Motor ON
}
