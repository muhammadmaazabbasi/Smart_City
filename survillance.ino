#define enA 2 //Enable1 L298 Pin enA 
#define in1 3 //Motor1 L298 Pin in1 
#define in2 4 //Motor1 L298 Pin in2 
#define in3 5 //Motor2 L298 Pin in3 
#define in4 6 //Motor2 L298 Pin in4 
#define enB 7 //Enable2 L298 Pin enB 
#define L_S A0 //IR sensor Left
#define R_S A1 //IR sensor Right

#include "esp_camera.h"
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <iostream>
#include <sstream>

void setup() { 
  // put your setup code here, to run once
  Serial.begin(9600); // start serial communication at 9600bps
  pinMode(R_S, INPUT); // declare IR sensor as input  
  pinMode(L_S, INPUT); // declare IR sensor as input

  pinMode(enA, OUTPUT); // declare as output for L298 Pin enA 
  pinMode(in1, OUTPUT); // declare as output for L298 Pin in1 
  pinMode(in2, OUTPUT); // declare as output for L298 Pin in2 
  pinMode(in3, OUTPUT); // declare as output for L298 Pin in3   
  pinMode(in4, OUTPUT); // declare as output for L298 Pin in4 
  pinMode(enB, OUTPUT); // declare as output for L298 Pin enB 

  analogWrite(enA, 128); // Write The Duty Cycle 0 to 255 Enable Pin A for Motor1 Speed 
  analogWrite(enB, 128); // Write The Duty Cycle 0 to 255 Enable Pin B for Motor2 Speed 
}

void loop() {  
  // Line Follower
  // if Right Sensor and Left Sensor are at White color then it will call forward function
  if((digitalRead(R_S) == 0) && (digitalRead(L_S) == 0)) {
    forward();
  }
  // if Right Sensor is Black and Left Sensor is White then it will call turn Right function
  else if((digitalRead(R_S) == 1) && (digitalRead(L_S) == 0)) {
    turnRight();
  }
  // if Right Sensor is White and Left Sensor is Black then it will call turn Left function
  else if((digitalRead(R_S) == 0) && (digitalRead(L_S) == 1)) {
    turnLeft();
  }
  delay(10);
}

void forward() {  //forward
  digitalWrite(in1, HIGH); // Left Motor backward Pin 
  digitalWrite(in2, LOW); // Left Motor forward Pin 
  digitalWrite(in3, LOW); // Right Motor forward Pin 
  digitalWrite(in4, HIGH); // Right Motor backward Pin 
}

void backward() { //backward
  digitalWrite(in1, LOW); // Left Motor backward Pin 
  digitalWrite(in2, HIGH); // Left Motor forward Pin 
  digitalWrite(in3, HIGH); // Right Motor forward Pin 
  digitalWrite(in4, LOW); // Right Motor backward Pin 
}

void turnRight() { //turnRight
  digitalWrite(in1, HIGH); // Left Motor backward Pin 
  digitalWrite(in2, LOW); // Left Motor forward Pin 
  digitalWrite(in3, HIGH); // Right Motor forward Pin 
  digitalWrite(in4, LOW); // Right Motor backward Pin 
}

void turnLeft() { //turnLeft
  digitalWrite(in1, LOW); // Left Motor backward Pin 
  digitalWrite(in2, HIGH); // Left Motor forward Pin 
  digitalWrite(in3, LOW); // Right Motor forward Pin 
  digitalWrite(in4, HIGH); // Right Motor backward Pin 
}

void Stop() { //stop
  digitalWrite(in1, LOW); // Left Motor backward Pin 
  digitalWrite(in2, LOW); // Left Motor forward Pin 
  digitalWrite(in3, LOW); // Right Motor forward Pin 
  digitalWrite(in4, LOW); // Right Motor backward Pin 
}
**