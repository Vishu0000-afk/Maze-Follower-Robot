#define ct   17
#define e1   14
#define e2   15
#define e3   16

#define stby 4

#define in1  6
#define in2  5
#define in3  10
#define in4  9

void setup() {
  pinMode(ct,   OUTPUT);
  pinMode(e1,   INPUT);
  pinMode(e2,   INPUT);
  pinMode(e3,   INPUT);

  pinMode(in1,  OUTPUT);
  pinMode(in2,  OUTPUT);
  pinMode(in3,  OUTPUT);
  pinMode(in4,  OUTPUT);

  pinMode(stby, OUTPUT);
  digitalWrite(stby, HIGH);

  Serial.begin(9600);
}

long getDistance(int echoPin) {
  digitalWrite(ct, LOW);
  delayMicroseconds(2);
  digitalWrite(ct, HIGH);
  delayMicroseconds(10);
  digitalWrite(ct, LOW);

  long duration = pulseIn(echoPin, HIGH, 25000);
  long distance = duration * 0.034 / 2;

  if (distance == 0) distance = 400;
  return distance;
}

void stop() {
  analogWrite(in1, 0);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
  analogWrite(in4, 0);
}

void forward() {
  analogWrite(in1, 125);
  analogWrite(in2, 0);
  analogWrite(in3, 125);
  analogWrite(in4, 0);
}

void uturn() {
  analogWrite(in1, 150);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
  analogWrite(in4, 150);
}

void right() {
  analogWrite(in1, 150);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
  analogWrite(in4, 150);
}

void left() {
  analogWrite(in1, 0);
  analogWrite(in2, 150);
  analogWrite(in3, 150);
  analogWrite(in4, 0);
}

void loop() {
  int rightDist  = getDistance(e3);
  delay(30);
  int frontDist = getDistance(e1);
  delay(30);
  int leftDist = getDistance(e2);
  delay(30);

  Serial.print("L: ");  Serial.print(leftDist);
  Serial.print(" F: "); Serial.print(frontDist);
  Serial.print(" R: "); Serial.println(rightDist);

  if (frontDist > 10) {
    forward();
  } else {
    stop();
    delay(250);

    if (leftDist > 10 && rightDist > 10) {
      left();              
    } else if (leftDist > 10) {
      left();              
    } else if (rightDist > 10) {
      right();             
    } else if (frontDist < 12 && leftDist < 12 && rightDist < 12) {
      stop();
      delay(250);
      uturn();           
    }
  }
}