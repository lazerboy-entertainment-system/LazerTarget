// BRIAN SUMNER
// PHI HUYNH
// KAMIL ADYLOV
// UCDENVER CSCI 4287
// SPRING 2019
// LAZERBOY ENTERTAINMENT SYSTEM:
// LAZERTARGET DRIVER
// GAME DEVELOPMENT MODULE
// VERSION: ALPHA_01




// INCLUDES
#include <Arduino.h>

#include "talkie.h"
#include "vocab.h"




// CONSTANT DEFINITIONS
#define PIN_SPEAKER       3

#define PIN_LED_RED       13
#define PIN_LED_GREEN     13
#define PIN_LED_BLUE      13

#define PIN_GDM_LDR       14    // THIS IS ANALOG PIN A0

#define LUX_THRESHOLD_GDM_LDR   512

#define LED_BLINK_DELAY   80
#define LED_BLINK_CYCLES  5




// VOICE OBJECT FOR SPEECH / AUDIO OUTPUT
Talkie voice;




// FORWARD DECLARATIONS:

bool isTargetHit();     // RETURN TRUE IF THE TARGET HAS BEEN HIT

void blinkRedLED();     // BLINKS THE RED LED
void blinkGreenLED();   // BLINKS THE GREEN LED
void blinkBlueLED();    // BLINKS THE BLUE LED




// PROGRAM INITIALIZATION
void setup() 
{

    Serial.begin(115200);
    Serial.println("INITIALIZING TARGET");

    // SET UP PIN MODES
    pinMode(PIN_SPEAKER, OUTPUT);

    voice.say(spINTRO);

    Serial.println("FINISHED INITIALIZING TARGET");

}




// MAIN PROGRAM LOOP
void loop() 
{

  if (isTargetHit())
  {
    // INDICATE HIT OCCURRED


    // OUTPUT SPEECH FOR HIT EVENT
    // NOTE: USE 'false' ARGUMENT FOR NON-BLOCKING SPEECH
    voice.say(spHIT, false); 
    // voice.say(spGREAT2, false); 


    // OUTPUT MESSAGE TO SERIAL CONSOLE
    Serial.println("HIT");


    // BLINK LED
    blinkGreenLED(); 


  // END IF
  }


// END LOOP
}





// NOTE:  NONE OF THE FUNCTIONS BELOW NEED TO BE MODIFIED
// NOTE:  PARAMETERS FOR THE FUNCTIONS BELOW ARE DEFINED BY CONSTANTS AT TOP OF FILE


// RETURN TRUE IF THE TARGET HAS BEEN HIT
bool isTargetHit()
{
  bool result = false;

  // READ ANALOG PIN 6 TIMES TO EMULATE FULL PROTOTYPE TIMING
  if (analogRead(PIN_GDM_LDR) >= LUX_THRESHOLD_GDM_LDR)
  {
    result = true;
  }
  if (analogRead(PIN_GDM_LDR) >= LUX_THRESHOLD_GDM_LDR)
  {
    result = true;
  }
  if (analogRead(PIN_GDM_LDR) >= LUX_THRESHOLD_GDM_LDR)
  {
    result = true;
  }
  if (analogRead(PIN_GDM_LDR) >= LUX_THRESHOLD_GDM_LDR)
  {
    result = true;
  }
  if (analogRead(PIN_GDM_LDR) >= LUX_THRESHOLD_GDM_LDR)
  {
    result = true;
  }
  if (analogRead(PIN_GDM_LDR) >= LUX_THRESHOLD_GDM_LDR)
  {
    result = true;
  }

  return result;
}


// BLINKS THE RED LED
void blinkRedLED() 
{
     // BLINK LED
    for (int i = 0; i < LED_BLINK_CYCLES; ++i)
    {
      digitalWrite(PIN_LED_RED, HIGH);
      delay(LED_BLINK_DELAY);
      digitalWrite(PIN_LED_RED, LOW);
      delay(LED_BLINK_DELAY);
    }
}

// BLINKS THE GREEN LED
void blinkGreenLED() 
{
     // BLINK LED
    for (int i = 0; i < LED_BLINK_CYCLES; ++i)
    {
      digitalWrite(PIN_LED_RED, HIGH);
      delay(LED_BLINK_DELAY);
      digitalWrite(PIN_LED_RED, LOW);
      delay(LED_BLINK_DELAY);
    }
}

// BLINKS THE BLUE LED
void blinkBlueLED() 
{
     // BLINK LED
    for (int i = 0; i < LED_BLINK_CYCLES; ++i)
    {
      digitalWrite(PIN_LED_RED, HIGH);
      delay(LED_BLINK_DELAY);
      digitalWrite(PIN_LED_RED, LOW);
      delay(LED_BLINK_DELAY);
    }
}
