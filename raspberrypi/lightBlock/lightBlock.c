#include <wiringPi.h>
#include <stdio.h>

#define LightBreakPin     5
#define LedPin            25

int main(void)
{

	if(wiringPiSetup() == -1) {
 		printf("setup wiringPi failed !");
		return 1;
	}

	pinMode(LightBreakPin, INPUT);
	pinMode(LedPin,  OUTPUT);

  int last = HIGH;
  int cur;

	while(1) {
    cur = digitalRead(LightBreakPin);
    if (cur != last) {
      last = cur;
      if(cur == HIGH){
        printf("led on !\n");
        digitalWrite(LedPin, HIGH);     //led on
      }
      else{
        printf("led off !\n");
        digitalWrite(LedPin, LOW);
      }
    }
	}

	return 0;
}
