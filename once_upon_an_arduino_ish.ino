const
int switchPin1 = 8; //the switch connect to pin 12
int switchPin2 = 9;
int switchPin3 = 10;

const
int ledPin = 13;//the led connect to pin 6

/**********************************/

int
switchState1 = 0;
int switchState2 = 0;
int switchState3 = 0;

void
setup()

{

  pinMode(switchPin1, INPUT);
  pinMode(switchPin2, INPUT);
  pinMode(switchPin3, INPUT);

  pinMode(ledPin, OUTPUT); //initialize the led

}

/**********************************/

void
loop()

{

  //read the state of the switch value

  switchState1 = digitalRead(switchPin1);
  switchState2 = digitalRead(switchPin2);
  switchState3 = digitalRead(switchPin3);

  if (switchState1 == HIGH) //if it is,the

  {

   
digitalWrite(ledPin, HIGH); //turn the led on

  }

  else

  {

    digitalWrite(ledPin, LOW); //turn the led

  }

}
