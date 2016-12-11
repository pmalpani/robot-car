//www.elegoo.com
//2016.09.23

// For Motors
int ENA=5; 
int ENB=11; 
int IN1=6;
int IN2=7;
int IN3=8;
int IN4=9;

void setup()
{
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  digitalWrite(ENA,HIGH);  
  digitalWrite(ENB,HIGH);      

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

int speed = 0;

void loop()
{
  speed = (speed + 64) % 256; 
  setSpeed(speed);

  carRotateClockwise();
  delay(500);
  carStop();
  delay(500);

  carRotateCounterClockwise();
  delay(500);
  carStop();
  delay(500);
}
