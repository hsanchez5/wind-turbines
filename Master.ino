// MASTER
#include <Wire.h>



char t[10]={};                        //empty string array to store numbers comming from the slave
volatile int Val;                     // varaible used by the master to sent data to the slave
float t_float;                        // takes slave string data and stores into a float var


///////////////////////////////////////// SETUP ///////////////////////////////////////////
void setup() {
  Wire.begin(8);                       // join i2c bus (address optional for master)
  Serial.begin(9600);                 // start serial for output
}



/////////////////////////////////// LOOP: RECEIVE/SEND DATA /////////////////////////////
void loop() {
  Wire.requestFrom(8, 4);             // request 3 bytes from slave device #8

  int i=0;                             //counter for each byte as it arrives
  while (Wire.available()) {           //gathers data comming from slave
    t[i] = Wire.read();                // every character that arrives it put in order in the empty array "t"
    i=i+1;
  }

    
  t_float = atof(t);                // reads string sent from slave and stores as a float
  t_float = map(t_float, 0.00, 1023.00, 1023.00,0.00) - 325.00;     // configure the data correctly
  t_float = t_float * 5.00/1023.00;           // display voltage value

  Serial.println(t_float);   //shows the data that was converted from a string to voltage float
  delay(10); //give some time to relax


  // send data to slave. here I am just sending the number 2
  Val=2;
  Wire.beginTransmission (8);
  Wire.write (Val);
  Wire.endTransmission ();
}
