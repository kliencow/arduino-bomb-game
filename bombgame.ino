
//Pin setup
const int button1Pin = 2; 
const int button2Pin = 3;
const int bombPin =  12; 
const int tryLedPin1 = 11;
const int tryLedPin2 = 10;
const int tryLedPin3 = 9;

const int b1Val = 3;
const int b2Val = 1;

bool b1down = false;
bool b2down = false; 

//blink variables
int lastTime; // time passed since last loop
int timeLog; //time passed since last blink cycle

//game variables
int secretNumber; // the secret number that's trying to be found
int guess; // the current value of the guess
int tries; // number of remaining tries.

void setup()
{
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

  pinMode(bombPin, OUTPUT);
  pinMode(tryLedPin1, OUTPUT);
  pinMode(tryLedPin2, OUTPUT);
  pinMode(tryLedPin3, OUTPUT);

  randomSeed(analogRead(0));
  
  secretNumber = random(1,10); 
  guess = 0;
  tries = 3;

  lastTime = millis();
  timeLog = 0;
}


void loop()
{
  dealWithButtons();

  checkWinCondition();

  lightTries();

  timeLog = millis() - lastTime;
}

void lightTries() {
  if (tries == 3) {
    digitalWrite(tryLedPin1, HIGH);
    digitalWrite(tryLedPin2, HIGH);
    digitalWrite(tryLedPin3, HIGH);
  } else if (tries == 2) {
    digitalWrite(tryLedPin1, LOW);
    digitalWrite(tryLedPin2, HIGH);
    digitalWrite(tryLedPin3, HIGH);
  } else if (tries == 1) {
    digitalWrite(tryLedPin1, LOW);
    digitalWrite(tryLedPin2, LOW);
    digitalWrite(tryLedPin3, HIGH);
  } else if (tries == 0) {
    digitalWrite(tryLedPin1, LOW);
    digitalWrite(tryLedPin2, LOW);
    digitalWrite(tryLedPin3, LOW);
  }
}

void checkWinCondition() {
  if (guess == secretNumber) {
    digitalWrite(bombPin, LOW);
  } else if (guess > secretNumber || tries == 0) {
    digitalWrite(bombPin, HIGH);
  } else {
    doBlink();
  }
}

void doBlink() {
  if (timeLog > 200 * (secretNumber - guess)) {
    timeLog = 0;
    lastTime = millis();
    digitalWrite(bombPin, HIGH);
  } else if (timeLog > 100 * (secretNumber - guess)) {
    digitalWrite(bombPin, LOW);
  }
}

/*
 * If a button is pressed, increment the guess, decrement the tries
 * In addition add some logic to deal with long button presses.
 */
void dealWithButtons() {
  int button1State, button2State;

  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);

  if (button1State == LOW) 
  { 
    if (b1down) {
      //skip
    } else {
      b1down = true;
      guess = guess + b1Val;
      tries = tries - 1;
    }
  }
  
  if (button2State == LOW) 
  {
    if (b2down) {
      //skip
    } else {
      b2down = true;
      guess = guess + b2Val;
      tries = tries - 1;
    }
  }
  
  if (button1State == HIGH) {
    b1down = false;
  } 
  
  if (button2State == HIGH) {
    b2down = false;
  }
}


