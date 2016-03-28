#include <Wire.h>

char t[10];                     //empty array where to put the numbers going to the master
volatile int Val;               // variable used by the master to sent data to the slave



////////////////////////////// SETUP ///////////////////////////////////////////////////
void setup() {
  Wire.begin(8);                // Slave id #8
  Wire.onRequest(requestEvent); // fucntion to run when asking for data
  Wire.onReceive(receiveEvent); // what to do when receiving data
  Serial.begin(9600);           // serial for displaying data on your screen
}


////////////////////////////////// LOOP: ACTIVE VOLTAGE DIVIDER ///////////////////////////////////////////
void loop() {
  int aRead = analogRead(A0);   //plug a potentiometer or a resistor to pin A0, so you can see data being transfer

  // stores the Analog value to a string array called t
  dtostrf(aRead, 4, 4, t);     //converts the float or integer to a string. (floatVar, minStringWidthIncDecimalPoint, numVarsAfterDecimal, empty array);
  Serial.println(Val);         // print the character
  delay(10);
}


/////////////////////////////////INTERRUPTS: RECEIVE/SEND DATA /////////////////////////

// function: what to do when asked for data
// kind of like interrupts
void requestEvent() {
Wire.write(t); 
}

// what to do when receiving data from master
void receiveEvent(int howMany)
{Val = Wire.read();}
