//www.elegoo.com
//2016.09.23
#include <IRremote.h>

// For motor
int IN1=6;
int IN2=7;
int IN3=8;
int IN4=9;
int ENA=5;
int ENB=11;

// For IR
int IR_PIN = 12;
#define IR_BUTTON_A 16736925
#define IR_BUTTON_B 16754775
#define IR_BUTTON_C 16720605
#define IR_BUTTON_D 16761405
#define IR_BUTTON_X 16712445
IRrecv irrecv(IR_PIN);
decode_results decoded;
unsigned long decoded_value;

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
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);

  // For bluetooth 
  Serial.begin(9600);

  //For IR magic
  pinMode(IR_PIN,INPUT);
  irrecv.enableIRIn(); 

  // set speed to max.
  digitalWrite(ENA,HIGH);  
  digitalWrite(ENB,HIGH);      
}

void loop()
{
  if (not irrecv.decode(&decoded))
    return;
  
  decoded_value = decoded.value;
  irrecv.resume();
    
  switch(decoded_value) {
  case IR_BUTTON_A:
    Serial.println("A pressed\n");
    carMoveFwd();
    break;
    
  case IR_BUTTON_B:
    Serial.println("B pressed\n");
    carMoveRev();
    break;
    
  case IR_BUTTON_C:
    Serial.println("C pressed\n");
    carRotateCounterClockwise();
    break;
    
  case IR_BUTTON_D: 
    Serial.println("D pressed\n");
    carRotateClockwise();
    break;
    
  case IR_BUTTON_X:
    Serial.println("X pressed\n");
    carStop();
    break;
  }

  // stop everything after 500ms
  delay(500);
  carStop();  
}
