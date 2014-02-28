Clock 
=====

Clock Project Firmware. 


This bit of firmware is intended to run on a PIC16F818.

The current functionality:
=====
Reads from RTC over SPI (Fully functional, seperate RTC drivers)

Writes to shift register for display (Fully functional, seperate Display driver)

What to do:
=====
Create 5V power supply for standalone

Clean up breadboard

Put onto protoboard

Includes:
=====
Main file

Configuration header

RTC Driver (source & header)

Shift Register Display Driver (source & header)


Makefile (Using MPLABX & XC8 compiler)

MPLABX Config files

Author
=====
All files created by me (Cody Shaw). 
