#include <Servo.h>
//Workstation Switch Variables
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

bool allDoingJobs = false;

//Testing LED
int ledPin = 2;

//Bird Talking Variables
Servo birdServo;
int birdPos = 180;

bool speech1 = true;
bool speech2 = false;
bool birdLeave = false;

//death variables
Servo wellServo;
int wellPos = 0;
bool birdDeath = false;

Servo dogServo;
int dogPos = 0;
bool sausDeath = false;

Servo fireServo;
int firePos = 0;
bool mouseDeath = false;

//Timer Variables
unsigned long previousMillis = 0;

//Story Variables
bool act1 = true;
bool act2 = false;
bool scene1 = true;
bool scene3 = true;
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
  fireServo.write(0);
  
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
    //Scene 1: Mouse, Bird, Sausage all do their jobs. 
    if (scene1){
      Serial.println("scene1");
      scene1 = false;
    }
    
    if (goodKitchState == HIGH && goodForestState == HIGH && 
        goodWellState == HIGH){
      digitalWrite(ledPin, HIGH);
      allDoingJobs = true;
      }
    }
    else{
      digitalWrite(ledPin, LOW);
      allDoingJobs = false;    
    }
    
    if (allDoingJobs && speech1 && !speech2){
      //Scene 2: Other Bird talks to Bird and tells him that Sausage should get the wood instead.
      Serial.println("scene2");
      birdServo.write(90);
      act1 = false;
      act2 = true;
    }
  if (act2 && !act1){
    if (badForestState == HIGH && sausDeath == false){
      if (scene3){
      //Scene 3: While getting wood, Sausage gets eaten by a dog.
      Serial.println("scene3");
      scene3 = false;
      }
      dogServo.write(180);
      sausDeath = true;
      if (speech1 && !speech2){
        previousMillis = currentMillis;
        speech1 = false;
        speech2 = true;
      }
      if (currentMillis - previousMillis >= 2000 && speech2){
        //Scene 4: Other bird tells bird that Mouse should cook.
        Serial.println("scene4");
        birdServo.write(0);
        speech2 = false;
      }
    }
    if (badKitchState == HIGH && !mouseDeath){
      //Scene 5: Mouse dies by cooking herself.
      Serial.println("scene5");
      fireServo.write(180);
      mouseDeath = true;
      previousMillis = currentMillis;
      birdLeave = true;
    }
    if (currentMillis - previousMillis >= 2000 && !speech1 && !speech2 && birdLeave){
        birdServo.write(180);
        birdLeave = false;
      }
    if (badWellState == HIGH && !birdDeath){
      //Scene 6: Bird tries to extinguish house by getting water from the well, falls in.
      Serial.println("scene6");
      wellServo.write(180);
      birdDeath = true;
    }
    if (sausDeath == true && mouseDeath == true && birdDeath == true){
      act2 = false;
    }
  }
}
