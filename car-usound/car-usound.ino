//www.elegoo.com
//2016.09.23
#include <Servo.h>

// For motor
int IN1=6;
int IN2=7;
int IN3=8;
int IN4=9;
int ENA=5;
int ENB=11;

// For servo
Servo servo;
int Echo = A4;
int Trig = A5;


int distance()
{
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);
  float d = pulseIn(Echo, HIGH);
  d = d / 58;
  return (int)d;
}

void leftWheelsRev()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
}

void rightWheelsRev()
{
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}

void leftWheelsFwd()
{
  digitalWrite(IN2,HIGH);
  digitalWrite(IN1,LOW);
}

void rightWheelsFwd()
{
  digitalWrite(IN4,LOW);
  digitalWrite(IN3,HIGH);
}

void leftWheelsStop()
{
  digitalWrite(IN2,LOW);
  digitalWrite(IN1,LOW);
}

void rightWheelsStop()
{
  digitalWrite(IN4,LOW);
  digitalWrite(IN3,LOW);
}

void carMoveFwd()
{
  leftWheelsFwd();
  rightWheelsFwd();
}

void carMoveRev()
{
  leftWheelsRev();
  rightWheelsRev();
}

void carStop()
{
  leftWheelsStop();
  rightWheelsStop();
}

void carRotateClockwise()
{
  leftWheelsRev();
  rightWheelsFwd();
}

void carRotateCounterClockwise()
{
  leftWheelsFwd();
  rightWheelsRev();
}

void setSpeed(int speed)
{
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

void setup()
{
  // For motor (L298)
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);

  // For bluetooth
  Serial.begin(9600);

  // set speed to max.
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);

  // for USound
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);

  // servo
  servo.attach(3);
  servo.write(90);
}

void reportDurationAndSpeed(int duration, int speed)
{
  Serial.print("Duration of ");
  Serial.print(duration);
  Serial.print(" at speed ");
  Serial.println(speed);
}

void reportDistance(int angle, int d)
{
  Serial.print("Distance at ");
  Serial.print(angle);
  Serial.print(" = ");
  Serial.println(d);
}

void runTillObstacle()
{
  int d;
  while(true) {
    d = distance();
    reportDistance(90, d);
    if(d < 20) {
      break;
    } else {
      carMoveFwd();
      delay(100);
      carStop();
    }
  }
}

int speed = 255;
int duration = 0;

void loop()
{
  char getstr = Serial.read();

  switch(getstr) {
  case 'A':
  case 'a':
    carRotateCounterClockwise();
    break;

  case 'W':
  case 'w':
    carMoveFwd();
    break;

  case 'D':
  case 'd':
    carRotateClockwise();
    break;

  case 'S':
  case 's':
    carMoveRev();
    break;

  case 'X':
  case 'x':
    carStop();
    break;

  // speed controls
  case '1':
    speed = 128;
    reportDurationAndSpeed(duration, speed);
    setSpeed(speed);
    break;
  case '2':
    speed = 192;
    reportDurationAndSpeed(duration, speed);
    setSpeed(speed);
    break;
  case '3':
    speed = 255;
    reportDurationAndSpeed(duration, speed);
    setSpeed(speed);
    break;

  case ' ':
    runTillObstacle();
    break;

  // for controlling duration
  case '+':
    duration += 100;
    reportDurationAndSpeed(duration, speed);
    break;
  case '-':
    duration -= 100;
    reportDurationAndSpeed(duration, speed);
    break;
  case '0':
    duration = 0;
    reportDurationAndSpeed(duration, speed);
    break;
  }

  if(duration != 0) {
    delay(duration);
    carStop();
  }
}
