#include <wiringPi.h>
#include <stdio.h>
#include <sys/time.h>

#define DigitalSoundPin   5
#define LedPin            25

int secondsSinceEpoch() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec;
}

int main(void)
{

	if(wiringPiSetup() == -1) {
 		printf("setup wiringPi failed !");
		return 1;
	}

	pinMode(DigitalSoundPin, INPUT);
	pinMode(LedPin,  OUTPUT);

  int last = HIGH;
  int lastTime = secondsSinceEpoch();
  int cur, curTime;
  int counter = 0;

	while(1) {
    cur = digitalRead(DigitalSoundPin);
    if (cur != last) {
      last = cur;
      curTime = secondsSinceEpoch();
      if(curTime - lastTime >= 1) {
        if(cur == 1)
          counter++;

        printf("%d : Value = %d\n", counter, cur);
        printf("led toggle!\n");
        digitalWrite(LedPin, !digitalRead(LedPin));
      }
      lastTime = curTime;
    }

	}

	return 0;
}
