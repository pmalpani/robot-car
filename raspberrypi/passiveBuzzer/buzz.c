#include <wiringPi.h>
#include <stdio.h>

#define GPIO_18 1
#define GPIO_12 26

#define BuzzerPin GPIO_12

int main(void)
{
  int i;

	if(wiringPiSetup() == -1){ //when initialize wiring failed,print messageto screen
		printf("setup wiringPi failed !");
		return 1;
	}

	pinMode(BuzzerPin,  OUTPUT);

  for(i = 0; i < 10000; i++) {
    digitalWrite(BuzzerPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(BuzzerPin, LOW);
    delayMicroseconds(1000);
  }

	return 0;
}
