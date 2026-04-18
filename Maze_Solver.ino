#include <Ultrasonic.h>

const int leftSensorTrig     = 8;
const int leftSensorEcho     = 9;
const int frontSensorTrig    = 10;
const int frontSensorEcho    = 11;
const int rightSensorTrig    = 12;
const int rightSensorEcho    = 13;

const int motorLeftForward   = 3;
const int motorLeftBackward  = 5;
const int motorRightForward  = 6;
const int motorRightBackward = 9;

int motorSpeed = 150;
int turnSpeed  = 120;

Ultrasonic leftSensor(leftSensorTrig, leftSensorEcho);
Ultrasonic frontSensor(frontSensorTrig, frontSensorEcho);
Ultrasonic rightSensor(rightSensorTrig, rightSensorEcho);

void setup() {
  pinMode(motorLeftForward,   OUTPUT);
  pinMode(motorLeftBackward,  OUTPUT);
  pinMode(motorRightForward,  OUTPUT);
  pinMode(motorRightBackward, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int distanceLeft  = leftSensor.read(CM);
  int distanceFront = frontSensor.read(CM);
  int distanceRight = rightSensor.read(CM);

  Serial.print("L: "); Serial.print(distanceLeft);
  Serial.print(" F: "); Serial.print(distanceFront);
  Serial.print(" R: "); Serial.println(distanceRight);

  if (distanceFront > 40 && distanceLeft > 40 && distanceRight > 40 ||distanceFront < 10 && distanceLeft < 10 && distanceRight < 10 ) {
    stopMotors();
    Serial.println("Maze Completed!");
    while(true);
  }

  if (distanceFront < 15 && distanceLeft < 15) {
    turnRight();
  } else if (distanceFront < 15) {
    turnRight();
  } else if (distanceLeft > 15) {
    turnLeft();
  } else {
    moveForward();
  }
}

void moveForward() {
  analogWrite(motorLeftForward,   motorSpeed);
  analogWrite(motorRightForward,  motorSpeed);
  analogWrite(motorLeftBackward,  0);
  analogWrite(motorRightBackward, 0);
}

void moveBackward() {
  analogWrite(motorLeftForward,   0);
  analogWrite(motorRightForward,  0);
  analogWrite(motorLeftBackward,  motorSpeed);
  analogWrite(motorRightBackward, motorSpeed);
  delay(300);
}

void stopMotors() {
  analogWrite(motorLeftForward,   0);
  analogWrite(motorRightForward,  0);
  analogWrite(motorLeftBackward,  0);
  analogWrite(motorRightBackward, 0);
}

void turnLeft() {
  stopMotors();
  delay(100);
  analogWrite(motorLeftForward,   0);
  analogWrite(motorRightForward,  turnSpeed);
  analogWrite(motorLeftBackward,  0);
  analogWrite(motorRightBackward, 0);
  delay(500);
}

void turnRight() {
  stopMotors();
  delay(100);
  analogWrite(motorLeftForward,   turnSpeed);
  analogWrite(motorRightForward,  0);
  analogWrite(motorLeftBackward,  0);
  analogWrite(motorRightBackward, 0);
  delay(500);
}