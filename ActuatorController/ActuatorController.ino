// constants won't change. Used here to set a pin number:
const int ledPin =  LED_BUILTIN;// the number of the LED pin
const int Forward_Pin = 1; //H bridge input 1 on pin D1
const int Backward_Pin = 2; //H bridge input 2 on pin D2
const int InterruptForward = 3; //manual button to go forward
const int InterruptBackward = 4; //manual button to go backward


// Variables will change:
bool homed =  false;

unsigned long TimeMoved = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 1000;           // interval at which to blink (milliseconds)

void setup() {
  // initialize mode of pins
  pinMode(ledPin, OUTPUT);
  pinMode(Forward_Pin, OUTPUT);
  pinMode(Backward_Pin, OUTPUT);
  pinMode(InterruptBackward, INPUT);
  pinMode(InterruptForward, INPUT);

  //default pins to no movement
  digitalWrite(FWD_Pin, LOW);
  digitalWrite(BWD_Pin, LOW);
}

void loop() {
    
}

// This function returns 0 if no button was pushed, or 1 if a button was pushed.
byte delayWhileCheckingPushButtons(unsigned int delayTime)
{
  for (unsigned int i = 0; i < delayTime; i += 10)
  {
    delay(10);
    if (digitalRead(InterruptFoward) == HIGH || digitalRead(InterruptBackward) == HIGH)
      return(1);
  }
  return(0);
}
