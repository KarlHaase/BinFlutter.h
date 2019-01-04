/* Binary Flutter Library
 *
 * BinFlutter is a library that randomly cycles a digital output within a given range of periods and duty cycle.
 * 
 * This allows an light or LED to appear to be random or unstable.
 * This designed for simulating weak signals registering on status lights or poor electical connections.
 * 
 * Uses the millis() timer to schedule updates, does not block usings delay(), allowing other code to run between updates.
 *  
 * Based very loosely on Flicker.h
 * https://github.com/greygoo/Flicker/blob/master/examples/tenSecondFlicker/tenSecondFlicker.pde
 *
 * Informed by Adafruit Multi-Tasking with Arduino:
 * https://learn.adafruit.com/multi-tasking-the-arduino-part-1/
 *
 * MIT License
 * Copyright (c) 2019 Karl Haase
*/

#include "Arduino.h"
#include "BinFlutter.h"

Flutter::Flutter(int pin, long minF, long maxF, int dutyC)
{
      enabled = 0;
      ledPin = pin;
      minFlick = minF;
      maxFlick = maxF;
      dutyCycle = dutyC;
      currentMillis = millis();
      prevMillis = 0UL;
      Brightness=true;
}


//Enables Computation and sets up the LED
void Flutter::Enable()
{
  enabled = true;
  pinMode(ledPin, OUTPUT);
  prevMillis = millis();
  FlickTime = random(maxFlick - minFlick) + minFlick;
}

//Turns off the LED and dissables computation
void Flutter::Disable()
{
  enabled=false;
  prevMillis = 0UL;
  FlickTime = 0L;
  Brightness=false;
  digitalWrite(ledPin, Brightness);

}

//Changes the constants used to determine LED behavior
void Flutter::Change(long minF, long maxF, int dutyC)
{
      minFlick = minF;
      maxFlick = maxF;
      dutyCycle = dutyC;
}
 
//Checks to see if it is time to update the LED
//If so, generates new random state and period.
void Flutter::Update()
{

  if(enabled) 
  { 
    //Update the time  
    currentMillis = millis();
    passedMillis = currentMillis - prevMillis;
    
    //Recalculate and update state if we have passed the deadline.
    if (passedMillis >= FlickTime)
    {
      //Duty Cycle is basically a threshold
      Brightness = (random(0,255)>dutyCycle) ? false:true;
      //Recalculate the time until the next update.
      FlickTime = passedMillis + (unsigned long) random(maxFlick - minFlick) + (unsigned long)minFlick;
      //Set the output. Probably the least efficient line of the program.
      //https://jeelabs.org/2010/01/06/pin-io-performance/
      digitalWrite(ledPin, Brightness);
    }
  }
}
