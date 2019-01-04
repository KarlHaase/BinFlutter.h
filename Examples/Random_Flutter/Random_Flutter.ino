/* Binary Flutter Advanced Demonstration
 *
 * BinFlutter is a library that randomly cycles a digital output within a given range of periods and duty cycle.
 * 
 * This allows an light or LED to appear to be random or unstable.
 * This designed for simulating weak signals registering on status lights or poor electical connections.
 * 
 * Uses the millis() timer to schedule updates, does not block usings delay(), allowing other code to run between updates.
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

// Creating an Fluttering LED object with initial conditions
// Flutter ObjectName(Arduino_Pin,min ms, max ms, duty cycle)
// Should work on any arduino pin that can be an output.
// min and max ms are the time between the LED is updated with a new random value. Smaller values mean more frequent state changes.
// duty cycle is the fraction of the time the LED is lit, range from 0 to 255
Flutter LED_Flutter(LED_BUILTIN, 5, 50, 128);

// the setup function runs once when you press reset or power the board
void setup() {
  
  // Start Fluttering the LED. 
  LED_Flutter.Enable();

  //Start a Serial Session for Status Updates
  Serial.begin(9600);

  
}

// the loop function runs over and over again forever
void loop() {
  
  //Next time we change duty cycles
  static unsigned long int Next_Update = millis() + 1000UL;
  
  //Next time we toggle the fluttering LED
  static unsigned long int Next_Pause = millis() + 10000UL;
  
  //Keep track of which duty cycle we're on
  static int index = 0;
  
  // An array of duty cycles to test. Duty cycle can range from 0 255.
  // 0 means LED lit 0% of the time
  // 255 means LED is lit 100% of the time
  // 128 means LED is lit 50% of the time
  const int DutyCycles[8] = { 32,64,128,192,255,128,64,32 };

  
  if(millis() < Next_Update){

    // Every time Update() is called, the status of the LED will be refreshed.
    // Idealy should be called with a frequency<min ms
    LED_Flutter.Update();
    
  } else {
    Serial.print("Updating Duty Cycle:");
    Serial.println(DutyCycles[index],DEC);   

    // Update the parameters of the fluttering LED
    // Change(min ms, max ms, duty cycle)
    // Same format as above
    LED_Flutter.Change(5, 50, DutyCycles[index]);

    // Duty cycle and schedule bookkeeping
    index++;
    if(index > 7) index = 0;
    Next_Update = millis() + 1000UL; 

  }

//We may want to turn off the fluttering LED for some reason.
  if(millis()>Next_Pause)
  {
    Serial.println("We can call 10,000 times in a tight loop...");
    for(int i=0;i<10000;i++){
      //Calls Update(), but since there are few scheduled wakeups, doesn't cost much CPU
      LED_Flutter.Update();
    }
    Serial.println("...and it won't be noticably different than in the main body.");
    
    Serial.println("Disabling Flutter for 5 seconds...");
    //Turns off LED and disables flutter related computations.
    LED_Flutter.Disable();

    //Now if we call Update(), nothing happens!
    Serial.println("Uselessly Calling Update();");
    for(int i=0;i<10000;i++){
      //Calls Update(), but since were disabled, no computation happens.
      LED_Flutter.Update();
    }
    delay(5000);
    Serial.println("Enabling Flutter for 10 seconds");
    
    //Renable fluttering
    LED_Flutter.Enable();

    //Book keeping for next pause
    Next_Pause = millis() + 10000UL;
  }

}

