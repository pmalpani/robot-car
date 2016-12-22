#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define TRIG 6
#define ECHO 26

void setup() {
  wiringPiSetup();
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  //TRIG pin must start LOW
  digitalWrite(TRIG, LOW);
  delay(200);
}

int getCM() {
  long startTime;
  long waitTime;

  //Send trig pulse
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(20);
  digitalWrite(TRIG, LOW);

  //Wait for echo start
  startTime = micros();
  while(digitalRead(ECHO) == LOW) {
    waitTime = micros() - startTime;
    if (waitTime > 100000)
      break;
  }

  //Wait for echo end
  startTime = micros();
  while(digitalRead(ECHO) == HIGH);
  long travelTime = micros() - startTime;

  //Get distance in cm
  int distance = travelTime / 58;

  return distance;
}

int main(void) {
  int i;
  setup();

  for(i = 0; i < 100; i++) {
    printf("Distance: %dcm\n", getCM());
    delay(1000);
  }

  return 0;
}
