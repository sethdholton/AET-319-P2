#include <Servo.h>
/*Workstation Switch Variables*/
int goodKitchSwitch = 13;
int badKitchSwitch = 12;
int badForestSwitch = 11;
int goodForestSwitch = 10;
int badWellSwitch = 9;
int goodWellSwitch = 8;

int goodKitchState = 0;
int badKitchState = 0;
int badForestState = 0;
int goodForestState = 0;
int badWellState = 0;
int goodWellState = 0;

bool switchesOn = false;

/*Testing LED*/
int ledPin = 2;

/*Bird Talking Variables*/
bool firstStage = false;
bool secondStage = false;

Servo birdServo;
int birdPos = 0;

/*Timer Variables*/
unsigned long previousMillis = 0;

void setup()

{
  pinMode(goodKitchSwitch, INPUT);
  pinMode(badKitchSwitch, INPUT);
  pinMode(badForestSwitch, INPUT);
  pinMode(goodForestSwitch, INPUT);
  pinMode(badWellSwitch, INPUT);
  pinMode(goodWellSwitch, INPUT);

  pinMode(ledPin, OUTPUT);
  birdServo.attach(6);
  birdServo.write(0);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
}

void loop()
{
  unsigned long currentMillis = millis();
  
  goodKitchState = digitalRead(goodKitchSwitch);
  badKitchState = digitalRead(badKitchSwitch);
  badForestState = digitalRead(badForestSwitch);
  goodForestState = digitalRead(goodForestSwitch);
  badWellState = digitalRead(badWellSwitch);
  goodWellState = digitalRead(goodWellSwitch);
  
  birdServo.write(birdPos);

  if (goodKitchState == HIGH && goodForestState == HIGH && 
      goodWellState == HIGH)
  {
    digitalWrite(ledPin, HIGH);
  }
  else
  {
    digitalWrite(ledPin, LOW);
  }
  
  if (goodKitchState == HIGH && goodForestState == HIGH && 
      goodWellState == HIGH)
  {
  //digitalWrite(ledPin, HIGH);
  switchesOn = true;
  }
  else
  {
    //digitalWrite(ledPin, LOW);
    switchesOn = false;
    firstStage = false;
    secondStage = false;
    birdPos = 0;
    
  }
  
  if (switchesOn && !firstStage){
    birdPos = 90;
    firstStage = true;
    previousMillis = currentMillis;
  }

  
  if (firstStage && !secondStage && currentMillis - previousMillis == 3000){
    birdPos = 180;
    secondStage = true;
    
  }

}
