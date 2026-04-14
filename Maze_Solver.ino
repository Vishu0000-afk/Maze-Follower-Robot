#include <Ultrasonic.h>

const int leftSensorTrig = 8;
const int leftSensorEcho = 9;
const int frontSensorTrig = 10;
const int frontSensorEcho = 11;
const int rightSensorTrig = 12;
const int rightSensorEcho = 13;

const int motorLeftForward = 2;
const int motorLeftBackward = 3;
const int motorRightForward = 4;
const int motorRightBackward = 5;

Ultrasonic leftSensor(leftSensorTrig, leftSensorEcho);
Ultrasonic frontSensor(frontSensorTrig, frontSensorEcho);
Ultrasonic rightSensor(rightSensorTrig, rightSensorEcho);

void setup() {
  pinMode(motorLeftForward, OUTPUT);
  pinMode(motorLeftBackward, OUTPUT);
  pinMode(motorRightForward, OUTPUT);
  pinMode(motorRightBackward, OUTPUT);
  Serial.begin(9600);
}

void loop() {
int distanceLeft  = leftSensor.read(CM);
int distanceFront = frontSensor.read(CM);
int distanceRight = rightSensor.read(CM);
  if (distanceFront < 15) {

    turnRight();
  } else if (distanceLeft < 10) {

    moveForward();
  } else if (distanceRight < 10) {
    moveForward();
  } else {

    turnLeft();
  }
}

void moveForward() {
  digitalWrite(motorLeftForward, HIGH);
  digitalWrite(motorRightForward, HIGH);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightBackward, LOW);
}

void turnLeft() {
  digitalWrite(motorLeftForward, LOW);
  digitalWrite(motorRightForward, HIGH);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightBackward, LOW);
  delay(500);
}

void turnRight() {
  digitalWrite(motorLeftForward, HIGH);
  digitalWrite(motorRightForward, LOW);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightBackward, LOW);
  delay(500);
}


