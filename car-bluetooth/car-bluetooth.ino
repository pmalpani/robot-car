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


  //For bluetooth magic
  Serial.begin(9600);
  
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

int speed = 0;
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
    setSpeed(128);
    break;    
  case '2':
    setSpeed(192);
    break;    
  case '3':
    setSpeed(255);
    break;

  // for controlling duration  
  case '+':
    duration += 100;
    Serial.write(duration);
    break;
  case '-':
    duration -= 100;
    Serial.write(duration);
    break;
  case '0':
    duration = 0;
    Serial.write(duration);
    break;
  }
  
  if(duration != 0) {
    delay(duration);
    carStop();
  }  
}
