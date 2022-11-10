#include <Servo.h>
int switchPin1 = 13;
int switchPin2 = 12;
int switchPin3 = 11;
int switchPin4 = 10;
int switchPin5 = 9;
int switchPin6 = 8;

int ledPin = 2;

Servo servo1;

bool switchesOn = false;
bool firstStage = false;
bool secondStage = false;

/**********************************/

int switchState1 = 0;
int switchState2 = 0;
int switchState3 = 0;
int switchState4 = 0;
int switchState5 = 0;
int switchState6 = 0;

int pos = 0;

unsigned long previousMillis = 0;

void setup()

{
  pinMode(switchPin1, INPUT);
  pinMode(switchPin2, INPUT);
  pinMode(switchPin3, INPUT);
  pinMode(switchPin4, INPUT);
  pinMode(switchPin5, INPUT);
  pinMode(switchPin6, INPUT);

  pinMode(ledPin, OUTPUT);
  servo1.attach(7);
  servo1.write(0);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
}

void loop()
{
  unsigned long currentMillis = millis();
  
  switchState1 = digitalRead(switchPin1);
  switchState2 = digitalRead(switchPin2);
  switchState3 = digitalRead(switchPin3);
  switchState4 = digitalRead(switchPin4);
  switchState5 = digitalRead(switchPin5);
  switchState6 = digitalRead(switchPin6);
  
  servo1.write(pos);
  if (switchState1 == HIGH && switchState2 == HIGH && 
      switchState3 == HIGH && switchState4 == HIGH && 
      switchState5 == HIGH && switchState6 == HIGH)
  {
	digitalWrite(ledPin, HIGH);
	switchesOn = true;
  }
  else
  {
    digitalWrite(ledPin, LOW);
    switchesOn = false;
    firstStage = false;
    secondStage = false;
    pos = 0;
    
  }
  
  if (switchesOn && !firstStage){
  	pos = 90;
    firstStage = true;
    previousMillis = currentMillis;
  }
  
  if (firstStage && !secondStage && currentMillis - previousMillis == 1000){
    pos = 180;
    secondStage = true;
    
  }

}
