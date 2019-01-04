# BinFlutter.h
## BinFlutter - Randomly cycle arduino digital pin for an unstable lighting effect

BinFlutter (binary fluttering) is a library that randomly cycles a digital output within a given range of periods and duty cycle.

The justification for this library is the need to create lighting effects that contained noise that simulated sparking, poor contacts, or weak or pulse signals (like from a gieger counter), while not using arduino analog outputs (so it will work on any output pin) and not block other code from running. 

Uses the Arduino millis() timer to schedule updates, does not block usings delay(), allowing other code to run between updates.

## Installation:
For a single program, copy BinFlutter.h and BinFlutter.cpp into the arduino sketch folder and add the following to the top of the sketch:
#include "./Binflutter.h"

Or you can install it for yourself in your home arduino folder:
https://www.arduino.cc/en/guide/libraries

## Examples
After installing the libraries, there is a basic example that will setup the builtin arduino LED to flutter, and an advanced examples that demonstrates all the features of the library.

## Known limitiations
* Uses digitalWrite() which is fairly slow compared to direct port access via avr-gcc
* No ability to programatically create Fluttering outputs at runtime: must be determined in advance
* Does not use PWM or analog write: pins are set at full intensity
* Does not use any fancy timer/interrupt tricks. Blocking code can cause fluttering to pause or stop. Needs to be called about once every 5 ms to avoid huge overruns.

## Tested on:
* Arduino Uno
* Arduino Leonardo
* Arduino Pro Mini

## References
Based very loosely on: Flicker.h
[https://github.com/greygoo/Flicker/](https://github.com/greygoo/Flicker/)

Informed by Adafruit Multi-Tasking with Arduino:
[https://learn.adafruit.com/multi-tasking-the-arduino-part-1/
](https://learn.adafruit.com/multi-tasking-the-arduino-part-1/)

MIT License
Copyright (c) 2019 Karl Haase
