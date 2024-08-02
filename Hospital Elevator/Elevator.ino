 #include <Servo.h>

// Create servo objects
 Servo servoL;
Servo servoR;

// Define the pins for the servo motors
const int servoLPin = 2;  // Pin for servo 1
const int servoRPin = 3;  // Pin for servo 2

const int irSensorPin = 8;  // IR sensor pin

const int in1 = 2;
const int in2 = 3;
// Define the pins for the ultrasonic sensor

const int redPin = 11;    // Echo pin
const int greenPin = 12;  // Echo pin

// Define the servo motor object

void setup() {
  // Initialize the IR sensor pin as an input
  servoL.attach(servoLPin);
   servoR.attach(servoRPin);
  pinMode(irSensorPin, INPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  // Initialize the servo motor
  Serial.begin(9600);
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
}

void loop() {
  // Read the IR sensor value()
  int irSensorValue = digitalRead(irSensorPin);
  Serial.print("IR: ");
  Serial.println(irSensorValue);
  // close_GATE();
  // // If the IR sensor detects an object
  if (irSensorValue == LOW) {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    lift_UP();
    lift_DOWN();
    // close_GATE();
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
  }
}
void lift_UP() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(8[000);
  lift_STOP();
}
void lift_DOWN() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(8000);
  lift_STOP();
}
void lift_STOP() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}
void redLED_ON() {
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);
}
void greenLED_ON() {
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
}
void ALL_LED_OFF() {
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
}
// void open_GATE() {
//   servoL.write(0);    // Open
//   servoR.write(180);  // Open
// }
// void close_GATE() {
//   servoL.write(180);  // Close
//   servoR.write(0);    // Close
// }
