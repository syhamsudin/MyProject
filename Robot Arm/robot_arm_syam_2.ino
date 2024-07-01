//servo1=  (semakin tinggi semakin ke kiri)
//servo2=  (semakin tinggi semakin ke atas)
//servo3=  (semakin tinggi semakin ke bawah)
//servo4=  (semakin tinggi semakin ke atas)
//servo5=  (20=nyapit. buka=100) 
//relay aktif=low
#include <Servo.h>
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

const int relay1 = 7;
const int relay2 = 8;
const int sensor1 = 9;
const int sensor2 = 10;
int statusSensor1;
int statusSensor2; 
int pos1;
int pos2;
int pos3;
int pos4;
int pos5;
int count1;
int count2;

void setup() {
  Serial.begin(9600);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(sensor1, INPUT);
  pinMode(sensor2,INPUT);
  servo1.attach(2);
  servo2.attach(3);
  servo3.attach(4);
  servo4.attach(5);
  servo5.attach(6);
  
  digitalWrite(7, 1);
  digitalWrite(8, 1);
  delay(2000);
  
  servo2.write(60);
  delay(1000);
  servo1.write(75);
  servo3.write(50);
  servo4.write(40);
  servo5.write(100);
  delay(1000);
 
}
void loop() {
  statusSensor1 = digitalRead(sensor1);
  statusSensor2 = digitalRead(sensor2);
  if(statusSensor1 == 1){
  kiri();
  }
  if(statusSensor2 == 1){
  kanan();
  }
}
void kiri(){
  for(pos1 = 75; pos1<=125; pos1 ++){
    servo1.write(pos1);
    delay(15);
  }
  for(int a=0; a<=75; a++){
    if(a<=70)
    servo4.write(a+40);
    servo3.write(a+50);
    delay(15);
  }
  for(pos2 = 60; pos2>=40; pos2 --){
    servo2.write(pos2);
    delay(15);
  }
  for(pos5 = 100; pos5>=20; pos5 --){
    servo5.write(pos5);
    delay(15);
  }
  
  //setelah menyapit

  for(pos2 = 40; pos2<=60; pos2 ++){
    servo2.write(pos2);
    delay(15);
  }
  for(int a=0; a<=75; a++){
    servo3.write(125-a);
    if(a<=70)
    servo4.write(110-a);
    delay(15);
    }
  if(count1 == 0){
  for(pos1 = 125; pos1<=155; pos1 ++){
    servo1.write(pos1);
    delay(15);
  }
  }
  if(count1 == 1){
  for(pos1 = 125; pos1<=165; pos1 ++){
    servo1.write(pos1);
    delay(15);
  }
  }
  for(int a=0; a<=60; a++){
    servo4.write(a+40);
    if(a<=50)
    servo3.write(a+50);
    if(a<=35)
    servo2.write(60-a);
    delay(15);
  }
  for(pos5 = 20; pos5<=100; pos5 ++){
    servo5.write(pos5);
    delay(15);
  }

  //otw inisial
  
  for(int a=0; a<=60; a++){
    servo4.write(100-a);
    if(a<=50)
    servo3.write(100-a);
    if(a<=35)
    servo2.write(a+25);
    delay(15);
  }
  for(pos1 = 155; pos1>=75; pos1 --){
    servo1.write(pos1);
    delay(15);
  }
  digitalWrite(relay1, 0);
  delay(100);
  digitalWrite(relay1, 1);
  delay(100);
  count1++;
  if(count1 == 2){
    count1 = 0;
  }
}

void kanan(){
  for(pos1 = 75; pos1>=30; pos1 --){
    servo1.write(pos1);
    delay(15);
  }
  for(int a=0; a<=75; a++){
    if(a<=70)
    servo4.write(a+40);
    servo3.write(a+50);
    delay(15);
  }
  for(pos2 = 60; pos2>=40; pos2 --){
    servo2.write(pos2);
    delay(15);
  }
  for(pos5 = 100; pos5>=20; pos5 --){
    servo5.write(pos5);
    delay(15);
  }
  
  //setelah menyapit
  
  for(pos2 = 40; pos2<=60; pos2 ++){
    servo2.write(pos2);
    delay(15);
  }
  for(int a=0; a<=75; a++){
    servo3.write(125-a);
    if(a<=70)
    servo4.write(110-a);
    delay(15);
    }
  if(count2 == 0){
  for(pos1 = 30; pos1>=10; pos1 --){
    servo1.write(pos1);
    delay(15);
  }
  }
  if(count2 == 1){
  for(pos1 = 30; pos1>=0; pos1 --){
    servo1.write(pos1);
    delay(15);
  }
  }
  for(int a=0; a<=60; a++){
    servo4.write(a+40);
    if(a<=50)
    servo3.write(a+50);
    if(a<=35)
    servo2.write(60-a);
    delay(15);
  }
  for(pos5 = 20; pos5<=100; pos5 ++){
    servo5.write(pos5);
    delay(15);
  }

  //otw inisial
  
  for(int a=0; a<=60; a++){
    servo4.write(100-a);
    if(a<=50)
    servo3.write(100-a);
    if(a<=35)
    servo2.write(a+25);
    delay(15);
  }
  for(pos1 = 10; pos1<=75; pos1 ++){
    servo1.write(pos1);
    delay(15);
  }
  digitalWrite(relay2, 0);
  delay(100);
  digitalWrite(relay2, 1);
  delay(100);
  count2++;
  if(count2 == 2){
    count2 = 0;
  }

}
