#include <Servo.h>
//Workstation Switch Variables
int goodKitchSwitch = 12;
int badKitchSwitch = 13;
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

bool allDoingJobs = false;

//Testing LED
int ledPin = 2;

//Servo Pins
int birdPin = 7;
int wellPin = 6;
int dogPin = 5;
int firePin = 4;

//Bird Talking Variables
Servo birdServo;
bool speech1 = false;
bool speech2 = false;
bool birdTimer1 = false;
bool birdTimer2 = false;

//Death Variables
Servo wellServo;
bool birdDeath = false;

Servo dogServo;
bool sausDeath = false;
bool dogTimer = true; 

Servo fireServo;
bool mouseDeath = false;

//Clock Variables
unsigned long previousMillis = 0;

//Story Variables
bool act1 = true;
bool act1Message = false;
bool act2 = false;
bool act2Message = false;
bool act3 = false;
bool act3Message = false;

void setup()

{
  pinMode(goodKitchSwitch, INPUT);
  pinMode(badKitchSwitch, INPUT);
  pinMode(badForestSwitch, INPUT);
  pinMode(goodForestSwitch, INPUT);
  pinMode(badWellSwitch, INPUT);
  pinMode(goodWellSwitch, INPUT);

  pinMode(ledPin, OUTPUT);
  birdServo.attach(birdPin);
  birdServo.write(180);

  wellServo.attach(wellPin);
  wellServo.write(0);

  dogServo.attach(dogPin);
  dogServo.write(0);

  fireServo.attach(firePin);
  fireServo.write(180);
  
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
}

void loop(){
  unsigned long currentMillis = millis();
  
  goodKitchState = digitalRead(goodKitchSwitch);
  badKitchState = digitalRead(badKitchSwitch);
  badForestState = digitalRead(badForestSwitch);
  goodForestState = digitalRead(goodForestSwitch);
  badWellState = digitalRead(badWellSwitch);
  goodWellState = digitalRead(goodWellSwitch);

  if (act1 && !act2){
    if (!act1Message){
      act1Message = true;
      Serial.println("act1");
    }
    if (goodKitchState == HIGH && goodForestState == HIGH && goodWellState == HIGH){
      digitalWrite(ledPin, HIGH);
      allDoingJobs = true;
    }
    else{
      digitalWrite(ledPin, LOW);
      allDoingJobs = false;    
    }
    
    if (allDoingJobs && !speech1 && !speech2){
      birdServo.write(90);
      speech1 = true;
      act1 = false;
      act2 = true;
    } 
  }
  
  if (act2 && !act1){
    if (!act2Message){
      act2Message = true;
      Serial.println("act2");
    }
    if (badForestState == HIGH && dogTimer){
      previousMillis = currentMillis;
      dogTimer = false;
      sausDeath = true;
    }
    if (currentMillis - previousMillis >= 1000 && sausDeath){
      dogServo.write(180);
      sausDeath = false;
      previousMillis = currentMillis;
      birdTimer1 = true;
      act2 = false;
      act3 = true;
    }
  }
  
  if (!act2 && act3){
    if (!act3Message){
       act3Message = true;
       Serial.println("act3");
    }
    if (currentMillis - previousMillis >= 1000 && birdTimer1){
      birdServo.write(0);
      speech1 = false;
      speech2 = true;
      birdTimer1 = false;
      mouseDeath = true;
    }
    
    if (badKitchState == HIGH && mouseDeath){
      Serial.println("successful mousedeath yuhh");
      fireServo.write(10);
      mouseDeath = false;
      previousMillis = currentMillis;
      birdTimer2 = true;
    }
    if (currentMillis - previousMillis >= 1000 && birdTimer2){
      birdServo.write(180);
      speech2 = false;
      birdTimer2 = false;
    }

    if (badWellState == HIGH && !birdDeath){
      wellServo.write(110);
      birdDeath = false;
      act3 = false;
    }
  }
}
