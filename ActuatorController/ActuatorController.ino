#include <Arduino.h>


// constants won't change. Used here to set a pin number:
const int ledPin =  LED_BUILTIN;// the number of the LED pin
const int Forward_Pin = 1; //H bridge input 1 on pin D1
const int Backward_Pin = 2; //H bridge input 2 on pin D2
const int ButtonForward = 3; //manual button to go forward
const int ButtonBackward = 4; //manual button to go backward


bool homed =  false;
unsigned long TimeMoved = 0;        // will store the elapsed time during a move

// constants won't change:
const int ms_per_mm = 100;           // Time in ms to move actuator 1 mm (10mm/s)

void setup() {
  // initialize mode of pins
  pinMode(ledPin, OUTPUT);
  pinMode(Forward_Pin, OUTPUT);
  pinMode(Backward_Pin, OUTPUT);
  pinMode(ButtonBackward, INPUT);
  pinMode(ButtonForward, INPUT);

  //default pins to no movement
  digitalWrite(Forward_Pin, LOW);
  digitalWrite(Backward_Pin, LOW);
}

void loop() {
    
}

// This function returns 0 if no button was pushed, or 1 if a button was pushed.
byte delayWhileCheckingPushButtons(unsigned int delayTime)
{
  for (unsigned int i = 0; i < delayTime; i += 10)
  {
    delay(10);
    if (digitalRead(Buttonforward) == HIGH || digitalRead(ButtonBackward) == HIGH)
      return(1);
  }
  return(0);
}

void home(){
  
}
