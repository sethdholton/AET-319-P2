const int switchPin = 13;

const int ledPin = 7;

int switchState = 0;


void
setup()

{

  pinMode(switchPin, INPUT);


  pinMode(ledPin, OUTPUT);


}


void
loop()

{


  switchState = digitalRead(switchPin);

  if (switchState == HIGH )

  {

   
digitalWrite(ledPin, HIGH);

  }

  else

  {

    digitalWrite(ledPin, LOW);

  }

}

/************************************/
