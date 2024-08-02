
#include <Servo.h>

const int IR_In = 10;
const int IR_Out = 11;

const int LED_Green = 2;
const int LED_Red = 3;

int Count = 0;

Servo Gate_Servo;

void setup() {
  pinMode(IR_In, INPUT);
  pinMode(IR_Out, INPUT);

  pinMode(LED_Green, OUTPUT);
  pinMode(LED_Red, OUTPUT);

  Gate_Servo.attach(7);

  Gate_Servo.write(0);

  Serial.begin(9600);
}

void loop() {
  // Handling IR1
  if (digitalRead(IR_In) == LOW) {
    if (Count < 8) {
      Gate_Servo.write(85);
      digitalWrite(LED_Green, HIGH);
      delay(3000);
      digitalWrite(LED_Green, LOW);
      Gate_Servo.write(0);
      Count=Count+1;
      Serial.println(Count);
    }

    else if (Count >= 8) {
      Gate_Servo.write(0);
      digitalWrite(LED_Red, HIGH);
      delay(3000);
      digitalWrite(LED_Red, LOW);
      Serial.println(Count);
    }
  }
  // Handling IR2
  if (digitalRead(IR_Out) == LOW) {
    if (Gate_Servo.read() == 0) {
      Gate_Servo.write(85);
      digitalWrite(LED_Green, HIGH);
      delay(3000);
      digitalWrite(LED_Green, LOW);
      Gate_Servo.write(0);
      Count=Count-1;
      Serial.println("Going Out Now.");
    }
    else{
      Gate_Servo.write(0);
      digitalWrite(LED_Red, HIGH);
      delay(3000);
      digitalWrite(LED_Red, LOW);
      Serial.println("No Going Out.");
    }
  }
}
