# dmx_motor_controllers
dmx motor control boxes 


DMX DUAL MOTOR DRIVER BOX

r holsopple 2020
Ryan.local@gmail.com

DMX receive ch 1-508
Box Fused for Motor output 1-15 AMP

Driver
Pololu Dual G2 High-Power Motor Driver 24v18 Shield for Arduino
https://www.pololu.com/product/2518
Motor: 5-24 vdc up to 20Amp per channel 

Box power supply 9V-12 DC tip positive
Change fuses for your Motor needs.

DMX ADDRESSING:
This Motor driver uses 4 Channels of DMX (1-508)
Use DIP switches on Box to choose your DMX START address.
up==ON

once adjusted, this DMX address will be initiated & retained after power cycle.
  here is a good dip switch calculator:
  https://www.laserworld.com/en/laserworld-toolbox/dmx-address-setting.html

Values in 0-255 (not percent)

Set START address to: 0 == motor Brake
Set START address to: 31 == motor Forward
Set START address to: 63 == motor Backward

Use the next channel after Start address to control Speed of Motor (most motors begin rotation about 10% power dmx 25)

The THIRD CHANNEL after START address is for MOTOR 2.

NOTE: MOTOR FAULT
if motor driver detects a power surge or fault, driver will stop and indicator LED will blink. Power cycle the driver box and this error will be cleared

Example: 
Light cue to move MOTOR 1 forward at full speed &  MOTOR 2 backwards at half speed with box set to DMX Channel 9 as starting address

Ch9 @ 31
Ch10 @ 255
Ch11 @ 63
Ch10 @ 127







