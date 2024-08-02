
#include <Servo.h>
#define LDRpin A1
#define sensorPower 7
#define sensorPin A0
int val = 0;
int LDRvalue = 0;
int IRSensor = 7;
int servoPin = 9;
int thresholdup = 0;
int thresholddown = 100;
const int LEDpin = 11;
const int LEDpin1 = 12;
const int LEDpin2 = 13;
const int LEDpin3 = 10;

Servo myServo;

void setup() {
  // put your setup code here, to run once:
pinMode(LEDpin, LOW);
pinMode(IRSensor,INPUT);
digitalWrite(LEDpin,OUTPUT);
digitalWrite(LEDpin1,OUTPUT);
digitalWrite(LEDpin2,OUTPUT);
digitalWrite(LEDpin3,OUTPUT);  
pinMode(sensorPower, OUTPUT);
digitalWrite(sensorPower, LOW);
myServo.attach(9);

}

void loop() {
  // put your main code here, to run repeatedly:
  LDRvalue = analogRead(LDRpin);
 
if (LDRvalue>300){
digitalWrite(LEDpin,HIGH);}
else{
digitalWrite(LEDpin,LOW);
}

int sensorStatus = digitalRead(IRSensor);
if(sensorStatus == 1)
{
  digitalWrite(LEDpin1,HIGH);
  digitalWrite(LEDpin2,LOW);
  myServo.write(90);
  delay(1000);}
else
{
  digitalWrite(LEDpin1,LOW);
  digitalWrite(LEDpin2,HIGH);
  myServo.write(180);
  delay(1000);
  myServo.write(0);
  delay(1000);}

  int level = analogRead(sensorPin);
  
 if(level < 20)
 {
 //digitalWrite(threshold, HIGH);
 digitalWrite(LEDpin3, HIGH);
 }
 else
 { 
 //digitalWrite(threshold, LOW);
 digitalWrite(LEDpin3, LOW);
 }
}
