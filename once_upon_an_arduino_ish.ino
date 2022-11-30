#include <Servo.h>
/*Workstation Switch Variables*/
int goodKitchSwitch = 8;
int badKitchSwitch = 9;
int badForestSwitch = 10;
int goodForestSwitch = 11;
int badWellSwitch = 12;
int goodWellSwitch = 13;

int goodKitchState = 0;
int badKitchState = 0;
int badForestState = 0;
int goodForestState = 0;
int badWellState = 0;
int goodWellState = 0;

bool allDoingJobs = false;

/*Testing LED*/
int ledPin = 2;

/*Bird Talking Variables*/

Servo birdServo;
int birdPos = 180;
bool speech1 = true;
bool speech2 = false;

//death variables
Servo wellServo;
int wellPos = 0;

Servo dogServo;
int dogPos = 0;

Servo fireServo;
int firePos = 0;

/*Timer Variables*/
unsigned long previousMillis = 0;

//Story Variables
bool act1 = true;
bool act2 = false;
void setup()

{
  pinMode(goodKitchSwitch, INPUT);
  pinMode(badKitchSwitch, INPUT);
  pinMode(badForestSwitch, INPUT);
  pinMode(goodForestSwitch, INPUT);
  pinMode(badWellSwitch, INPUT);
  pinMode(goodWellSwitch, INPUT);

  pinMode(ledPin, OUTPUT);
  birdServo.attach(7);
  birdServo.write(180);

  wellServo.attach(6);
  wellServo.write(0);

  dogServo.attach(5);
  dogServo.write(0);

  fireServo.attach(4);
  fireServo.write(180);
  
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

  if (act1 && !act2)
  {
    Serial.println("act1");
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
        goodWellState == HIGH){
      digitalWrite(ledPin, HIGH);
      allDoingJobs = true;
    }
    else{
      digitalWrite(ledPin, LOW);
      allDoingJobs = false;    
    }
    
    if (allDoingJobs && speech1 && !speech2){
      birdServo.write(90);
      act1 = false;
      act2 = true;
    }
  }
  
  if (act2 && !act1){
    Serial.println("act2");
    if (badForestState == HIGH){
        dogServo.write(170);
      
      /*if (speech1 && !speech2){
        previousMillis = currentMillis;
        speech1 = false;
        speech2 = true;
      }
      Serial.println(currentMillis - previousMillis);
      if (currentMillis - previousMillis >= 2000 && speech2){*/
        birdServo.write(0);
      
    }
    if (badKitchState == HIGH){
      fireServo.write(0);
      birdServo.write(180);
    }
    if (badWellState == HIGH){
      wellServo.write(80);
      act2 = false;
    }
  }
}
