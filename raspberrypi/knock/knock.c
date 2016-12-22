#include <wiringPi.h>
#include <stdio.h>

#define KnockPin      5
#define LedPin        25

int main(void)
{
	if(wiringPiSetup() == -1){ //when initialize wiring failed,print messageto screen
		printf("setup wiringPi failed !");
		return 1;
	}

	pinMode(KnockPin, INPUT);
	pinMode(LedPin,  OUTPUT);

  int i = 0;
  int was_on = 0;
  printf("Waiting..\n");

	while(1) {
    if (digitalRead(KnockPin) == LOW) {
      if(was_on == 0) {
        was_on = 1;
        i++;
        printf("Knock %d\n", i);
        digitalWrite(LedPin, !digitalRead(LedPin));     //led on
      }
    }
    else {
      was_on = 0;
    }
	}

	return 0;
}
