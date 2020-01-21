/*******DMX512 motor control with DIP addressing *******

  Speed channel, the next channel up after start channel ex: start chan 1, speed channel 2
  25-255 (motor starts spinning at 10%)

  here is a good dip switch calculator:
  https://www.laserworld.com/en/laserworld-toolbox/dmx-address-setting.html

  by r holsopple 2019

*/

#include <Arduino.h>
#include <Conceptinetics.h>
#include <Wire.h>
#include "MCP23017.h"
MCP23017 mcp;
#include "DualG2HighPowerMotorShield.h"
DualG2HighPowerMotorShield24v18 md;

//set the number of DMX channels to be controlled
#define DMX_SLAVE_CHANNELS  4
DMX_Slave dmx_slave ( DMX_SLAVE_CHANNELS ); // Configure a DMX slave controller


//Create and Define DIP Addressing Variables
int dipPins[] = {7, 8, 9, 10, 11, 12, 13, 14, 15}; //DIP Switch Pins usng mcp23017 board
word DMXaddress;

const int ledPin = 3;
int speedValue = 0;
int speedValue2 = 0;

void stopIfFault()
{
  if (md.getM1Fault())
  {
    md.disableDrivers();
    delay(1);
    //Serial.println("M1 fault");
    READYblink(50000);
    while (1);
  }
  if (md.getM2Fault())
  {
    md.disableDrivers();
    delay(1);
    // Serial.println("M2 fault");
    READYblink(50000);
    while (1);
  }
}

void setup() {

  // Dual G2 high power motor shield Pololu
  md.init();
  md.calibrateCurrentOffsets();
  delay(10);
  // Uncomment to flip a motor's direction:
  //md.flipM1(true);
  //md.flipM2(true);

  brake2();//make sure motor is stopped

  //load dip switch readings connected to mcp expansion board i2c
  mcp.begin(7);

  delay(100);

  //initialize DIP Pins
  //with mcp lib worked better this way than making a loop to init
  //Configue Port PA0 Output
  mcp.pinMode(7, INPUT);
  mcp.pinMode(8, INPUT);
  mcp.pinMode(9, INPUT);
  mcp.pinMode(10, INPUT);
  mcp.pinMode(11, INPUT);
  mcp.pinMode(12, INPUT);
  mcp.pinMode(13, INPUT);
  mcp.pinMode(14, INPUT);
  mcp.pinMode(15, INPUT);

  //turn on a 100K pullup internally
  mcp.pullUp(7, HIGH);
  mcp.pullUp(8, HIGH);
  mcp.pullUp(9, HIGH);
  mcp.pullUp(10, HIGH);
  mcp.pullUp(11, HIGH);
  mcp.pullUp(12, HIGH);
  mcp.pullUp(13, HIGH);
  mcp.pullUp(14, HIGH);
  mcp.pullUp(15, HIGH);

  //determine DMX address
  DMXaddress = address();
  delay(10);
  // Enable DMX slave interface and start recording
  // DMX data
  dmx_slave.enable ();
  // Load DIP PIN DMX address
  dmx_slave.setStartAddress (DMXaddress);
  READYblink(3);
  //READYblink(DMXaddress);
  analogWrite(ledPin, 10);


  //READYblink(DMXaddress);
  delay(1000);
}

void loop() {
  md.enableDrivers();
  delay(1);  // The drivers require a maximum of 1ms to elapse when brought out of sleep mode.

  // digitalWrite(ledPin, LOW);

  //adjust DMX start address with encoder change
  // dmx_slave.setStartAddress (encoderPos);

  //dmx 1 equals 31 motor rotates forwards //ISADORA 13
  if (( dmx_slave.getChannelValue (1) >= 31 ) && ( dmx_slave.getChannelValue (1) <= 33 ) ){
    speedValue = (dmx_slave.getChannelValue (2));
    // digitalWrite(ledPin, HIGH);
    motorFWD(speedValue);
  }
  //dmx 1 equals 63 motor rotates backwards//ISADORA 25
  else if (( dmx_slave.getChannelValue (1) >= 63 ) &&  dmx_slave.getChannelValue (1) <= 65 ){
    speedValue = (dmx_slave.getChannelValue (2));
    // digitalWrite(ledPin, HIGH);
    motorBWD(speedValue);
  }

  else if ( dmx_slave.getChannelValue (1) == 0 ) {
    // digitalWrite(ledPin, LOW);
    brake();
  }

  //dmx motor 2 equals 20 motor rotates forwards
  if (( dmx_slave.getChannelValue (3) >= 31 ) && ( dmx_slave.getChannelValue (3) <= 33 ) ){
    speedValue2 = (dmx_slave.getChannelValue (4));
    //digitalWrite(ledPin, HIGH);
    motorFWD2(speedValue2);
  }
  //dmx 1 equals 2 motor rotates backwards
  else   if (( dmx_slave.getChannelValue (3) >= 63 ) && ( dmx_slave.getChannelValue (3) <= 65 ) ){
    speedValue2 = (dmx_slave.getChannelValue (4));
    // digitalWrite(ledPin, HIGH);
    motorBWD2(speedValue2);
  }

  else if ( dmx_slave.getChannelValue (3) == 0 ) {
    //digitalWrite(ledPin, LOW);
    brake2();
  }
  //  delay (10);

}


//motor forward pololu
//convert -400 to 0 to 400 to a value of 0-255
void motorFWD(long speedVal) {
  md.setM2Speed((speedVal * 80 / 51 ));
  stopIfFault();
}

//motor backwards pololu
void motorBWD(long speedVal) {
  md.setM2Speed((speedVal * 80 / 51 * -1));
  stopIfFault();
}

void brake() {
  md.setM2Speed(0);
  stopIfFault();
}

//motor 2 forward
void motorFWD2(long speedVal2) {
  md.setM1Speed((speedVal2 * 80 / 51 ));
  stopIfFault();
}

//motor2 backwards
void motorBWD2(long speedVal2) {
  md.setM1Speed((speedVal2 * 80 / 51 * -1));
  stopIfFault();
}

void brake2() {
  md.setM1Speed(0);
  stopIfFault();
}
// end of sketch!
