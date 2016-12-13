//www.elegoo.com
//2016.09.23
#include <Servo.h>

#define MIN_SPEED 90
#define MAX_SPEED 255


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

int speed = 255;
int duration = 0;
int angle = 90;

int raw_distance()
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

#define DISTANCE_SAMPLES 5
int distance() {
  int arr[DISTANCE_SAMPLES];
  int d;
  int s;
  int i, j;
  for (i =0; i < DISTANCE_SAMPLES; i++) {
    arr[i] = 0;
  }
  for(i =0; i < DISTANCE_SAMPLES; i++) {
    d = raw_distance();
    for(j = 0; j < i; j++) {
      if(d < arr[j]) {
        s = arr[j];
        arr[j] = d;
        d = s;
      }
    }
    arr[i] = d;
  }
  for(i = 0; i < DISTANCE_SAMPLES; i++) {
    Serial.print(arr[i]);
    Serial.print(" ");
  }
  Serial.println("");
  return arr[DISTANCE_SAMPLES / 2];
}

void lookAt(int a) {
  angle = a;
  servo.write(angle);
}
void lookLeft(int delta) {
  lookAt(delta + 90);
}
void lookRight(int delta) {
  lookAt(90 - delta);
}
void lookStraight() {
  lookLeft(0);
}

void reportDurationAndSpeed(int duration, int speed)
{
  Serial.print(" Duration of ");
  Serial.print(duration);
  Serial.print(" at speed ");
  Serial.println(speed);
}

void reportDistance(int d)
{
  Serial.print(millis());
  Serial.print(" Distance at ");
  Serial.print(angle);
  Serial.print(" = ");
  Serial.println(d);
}

int look_delay = 100;
int look_delta = 30;

void reportLookDelay()
{
  Serial.print("Look delay ");
  Serial.print(" = ");
  Serial.println(look_delay);
}

void runTillObstacle()
{
  int d, d0, d1, d2;
  int moving = 0;
  int max_speed = speed;
  int last_time = millis();
  int cur_time = millis();
  int diff_time = millis();
  int last_dist = 0, diff_dist = 0;

  while(true) {
    lookLeft(look_delta);
    delay(look_delay);
    d1 = distance();
    reportDistance(d1);

    lookStraight();
    delay(look_delay);
    d0 = distance();
    reportDistance(d0);

    lookRight(look_delta);
    delay(look_delay);
    d2 = distance();
    reportDistance(d2);

    lookStraight();
    delay(look_delay);
    d = distance();
    d0 = min(d, d0);
    reportDistance(d0);

    d = min(d0, min(d1, d2));

    // compute change in time and dist
    cur_time = millis();
    diff_time = cur_time - last_time;
    last_time = cur_time;
    diff_dist = last_dist - d;
    last_dist = d;

    // report
    Serial.print("Moved ");
    Serial.print(diff_dist);
    Serial.print(" in time ");
    Serial.println(diff_time);


    if(d < 20) {
      break;
    } else {
      if (d < 100) {
        speed = min(max_speed, MIN_SPEED + (d - 20));
        setSpeed(speed);
      }
      if(moving == 0) {
        carMoveFwd();
        moving = 1;
      }
    }
  }
  carStop();
  speed = max_speed;
  setSpeed(speed);
}

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
    speed = MAX_SPEED;
    reportDurationAndSpeed(duration, speed);
    setSpeed(speed);
    break;
  case '2':
    speed = min(MAX_SPEED, speed + 5);
    reportDurationAndSpeed(duration, speed);
    setSpeed(speed);
    break;
  case '3':
    speed = max(MIN_SPEED, speed - 5);
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
    duration = max(0, duration - 100);
    reportDurationAndSpeed(duration, speed);
    break;
  case '0':
    duration = 0;
    reportDurationAndSpeed(duration, speed);
    break;

  // for look delay
  case 'i':
    look_delay += 25;
    reportLookDelay();
    break;
  case 'o':
    look_delay = max(0, look_delay - 25);
    reportLookDelay();
    break;
  case 'p':
    look_delay = 0;
    reportLookDelay();
    break;

  // for look delta
  case 'j':
    look_delta += 5;
    break;
  case 'k':
    look_delta -= 5;
    break;
  case 'l':
    look_delta = 30;
    break;
  }

  if(duration != 0) {
    delay(duration);
    carStop();
  }
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
  lookStraight();
}
