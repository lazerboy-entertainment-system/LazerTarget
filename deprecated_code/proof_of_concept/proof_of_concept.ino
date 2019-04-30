// BRIAN SUMNER
// KAMIL ADYLOV
// IN AFFILIATION WITH PHI HUYNH
// UCDENVER CSCI 4287 
// EMBEDDED SYSTEMS PROGRAMMING
// SALIM LAKHANI, PHD.
// SPRING 2019

// SPECIAL THANKS TO: 
// DONALD VUKOVIC OF TINKERMILL

// LAZERBOY ENTERTAINMENT SYSTEM:
// LAZERTARGET DRIVER
// PROOF_OF_CONCEPT
// VERSION: ALPHA_04


#include <Arduino.h>

#include "talkie.h"
#include "vocab.h"

#define PIN_SPEAKER       3
#define PIN_LED           13
#define ANALOG_PIN_LDR    0       
#define LUX_THRESHOLD     512


Talkie voice;


void setup() 
{

    Serial.begin(115200);
    Serial.println("INITIALIZING TARGET");

    // SET UP PIN MODES
    pinMode(PIN_SPEAKER, OUTPUT);


//    voice.say(spTARGET);
//    voice.say(spREADY);
    voice.say(spINTRO);

    Serial.println("FINISHED INITIALIZING TARGET");


}

void loop() 
{

  // THIS SIMULATES THE TIME OVERHEAD REQUIRED TO POLL 6 PINS
  if (analogRead(4) >= LUX_THRESHOLD)
  {
    digitalWrite(PIN_LED, HIGH);
    delay(50);
    digitalWrite(PIN_LED, LOW);
    delay(50);
  }

  if (analogRead(4) >= LUX_THRESHOLD)
  {
    digitalWrite(PIN_LED, HIGH);
    delay(50);
    digitalWrite(PIN_LED, LOW);
    delay(50);
  }

  if (analogRead(4) >= LUX_THRESHOLD)
  {
    digitalWrite(PIN_LED, HIGH);
    delay(50);
    digitalWrite(PIN_LED, LOW);
    delay(50);
  }

  if (analogRead(4) >= LUX_THRESHOLD)
  {
    digitalWrite(PIN_LED, HIGH);
    delay(50);
    digitalWrite(PIN_LED, LOW);
    delay(50);
  }

  if (analogRead(4) >= LUX_THRESHOLD)
  {
    digitalWrite(PIN_LED, HIGH);
    delay(50);
    digitalWrite(PIN_LED, LOW);
    delay(50);
  }


  
  // THIS IS THE ONLY PIN THAT HAS A PHOTORESISTOR LDR
  if (analogRead(ANALOG_PIN_LDR) >= LUX_THRESHOLD)
  {

    // INDICATE HIT OCCURRED
    Serial.println("HIT");

//    voice.say(spGREAT2, false);
    voice.say(spHIT, false);
    
    
    // BLINK LED WITH BLOCKING DELAY
    for (int i = 0; i < 8; ++i)
    {
      digitalWrite(PIN_LED, HIGH);
      delay(50);
      digitalWrite(PIN_LED, LOW);
      delay(50);
    }
    
  }

  
// END LOOP  
}
