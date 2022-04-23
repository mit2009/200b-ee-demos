/*
  A super simple reed switch demo!

  README! (yes, you)

  There are two types of reed switches. NO and NC. 
  This stands for normally open, and normally closed.
  You'll discover that the effects will be flipped based on 
  what kind of a reed switch you have!

  To setup:
  Connect one end of the reed switch to ground (doesn't matter which)
  Connect the other end to pin 2 of the arduino.

  Now, upload the code. Hold a magnet right beside the reed switch.
  Now take it away. You should see the BUILT-IN LED on the Arduino
  change state as you move the magnet. Hooray!

  Questions?
  [Victor Hung](vhung@mit.edu)
*/

const int reedSwitch = 2;    // the number of the reed switch pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int reedState = 0;           // variable for reading the reed switch status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the reed switch pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // read the state of the reedSwitch value:
  reedState = digitalRead(reedSwitch);

  // check if the reedSwitch is active. If it is, the reedSwitch is HIGH:
  if (reedState == HIGH) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}
