#include <Servo.h>
Servo myservo;
int pos;

int relay = 13;

const int sound = A0;
byte led1 = 8;
byte led2 = 12;
boolean claps;
int nilaiSound;
byte nilaiClaps = 0;
unsigned long startTime;
boolean statusProgram1 = false;
boolean statusProgram2 = false;

void setup() {
  Serial.begin(9600);
  
  myservo.attach(2);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(relay, OUTPUT);
//inisiasi
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(relay, LOW);
  myservo.write(0);

}

void loop() {
  nilaiSound = analogRead(sound);
  if(nilaiSound < 500){
    claps = true;
  }else{
    claps = false;
  }

  if(claps == true){
    startTime = millis();
    nilaiClaps++;
    delay(500);
  }

  if(nilaiClaps == 1 && millis() - startTime >= 2000){ // 1 kali tepuk
    statusProgram1 = !statusProgram1;
    if(statusProgram1){
      digitalWrite(led1, HIGH);
      digitalWrite(relay, LOW);
      nilaiClaps = 0;
    }else{
      digitalWrite(relay, HIGH);
      digitalWrite(led1, LOW);
      nilaiClaps = 0;
    }
    
  }
  if(nilaiClaps == 2 && millis() - startTime <= 2000){ // 2 kali tepuk
    statusProgram2 =!statusProgram2;
    if(statusProgram2){
      digitalWrite(led2, HIGH);
      myservo.write(180);
      nilaiClaps = 0;
    }else{
      digitalWrite(led2, LOW);
      myservo.write(0);
      nilaiClaps = 0;
    }
  }
  Serial.println(nilaiSound);
  Serial.println(claps);
}
