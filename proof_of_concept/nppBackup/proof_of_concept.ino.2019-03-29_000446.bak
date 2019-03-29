// BRIAN SUMNER
// IN AFFILIATION WITH KAMIL ADYLOV AND PHI HUYNH
// UCDENVER CSCI 4287
// SPRING 2019
// LAZERBOY ENTERTAINMENT SYSTEM:
// LAZERTARGET DRIVER
// PROOF_OF_CONCEPT
// VERSION: ALPHA_03


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


  
  
  
  
  
  
  
  
  if (analogRead(ANALOG_PIN_LDR) >= LUX_THRESHOLD)
  {

    // INDICATE HIT OCCURRED
    Serial.println("HIT");

//    voice.say(spGREAT2, false);
    voice.say(spHIT, false);
    
    
    // BLINK LED
    for (int i = 0; i < 8; ++i)
    {
      digitalWrite(PIN_LED, HIGH);
      delay(50);
      digitalWrite(PIN_LED, LOW);
      delay(50);
    }
    
  }
}
