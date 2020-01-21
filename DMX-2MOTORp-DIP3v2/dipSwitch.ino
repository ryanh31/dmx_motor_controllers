//reads dip switch positions from mcp expansion board i/o
//read binary

 
 //Create Address from DIP Switch (9 positions used)
word address() {
  word i, j = 0;

  //Get the switches state
  for (i = 0; i < 9; i++) {
    j = (j << 1) | !mcp.digitalRead(dipPins[i]);   // read the input pin
  }
  return j; //return address
}

// Blink the RED LED:
void READYblink(int howManyTimes) {
  int i;
  for (i=0; i< howManyTimes; i++) {
    analogWrite(ledPin, 100);
    delay(50);
    analogWrite(ledPin, 0);
    delay(50);  
  }
}

