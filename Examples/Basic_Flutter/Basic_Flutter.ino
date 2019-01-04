/* Binary Flutter Basic Demonstration
 *
 * BinFlutter is a library that randomly cycles a digital output within a given range of periods and duty cycle.
 * 
 * This allows an light or LED to appear to be random or unstable.
 * This designed for simulating weak signals registering on status lights or poor electical connections.
 * 
 * Uses the millis() timer to schedule updates, does not block usings delay(), allowing other code to run between updates.
 * 
 * See advanced demonstration to see Enable(), Disable(), and Change() methods in action.
 *  
 * Based loosely on Flicker.h
 * https://github.com/greygoo/Flicker/blob/master/examples/tenSecondFlicker/tenSecondFlicker.pde
 *
 * Informed by Adafruit Multi-Tasking with Arduino:
 * https://learn.adafruit.com/multi-tasking-the-arduino-part-1/
 *
 * MIT License
 * Copyright (c) 2019 Karl Haase
*/

#include "./BinFlutter.h"

// Creating an Fluttering LED object with initial conditions using the arduino built-in LED
// 5 ms minimum period between on/off random cycling
// 50 ms max period between on/off random cycling
// Duty cycle of 128 (meaning 128/255, or 50% of the time the LED will be on
Flutter LED_Flutter(LED_BUILTIN, 5, 50, 128);

// the setup function runs once when you press reset or power the board
void setup() {
  
  // Start Fluttering the LED. 
  LED_Flutter.Enable();
 
}

// the loop function runs over and over again forever
void loop() {
  
    // Every time Update() is called, the status of the LED will be refreshed.
    // Idealy should be called with a frequency<min ms
    LED_Flutter.Update();
    
 
}

