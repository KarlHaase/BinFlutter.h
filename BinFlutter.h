/* Binary Flutter Header
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

#ifndef BinFlutter_h
#define BinFlutter_h

class Flutter
{
  public:
    Flutter(int pin, long minF, long maxF, int dutyC);
    void Enable();
    void Update();
    void Change(long minF, long maxF, int dutyC);
    void Disable();
  private:
    bool enabled;
    int ledPin;
    long minFlick;
    long maxFlick;
    int dutyCycle;
    unsigned long FlickTime;
    unsigned long prevMillis;
    unsigned long currentMillis;
    unsigned long passedMillis;
    bool Brightness;

};

#endif
