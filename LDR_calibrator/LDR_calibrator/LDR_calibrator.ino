// BRIAN SUMNER
// KAMIL ADYLOV
// IN AFFILIATION WITH PHI HUYNH
// UCDENVER CSCI 4287
// SPRING 2019
// LAZERBOY ENTERTAINMENT SYSTEM:
// LAZERTARGET DRIVER
// LDR_CALIBRATOR
// VERSION: ALPHA_07


#include <Arduino.h>

#include "talkie.h"
#include "vocab.h"

#define PIN_SPEAKER       3
#define PIN_LED           13
     
#define LUX_THRESHOLD_0     280
#define LUX_THRESHOLD_1     280
#define LUX_THRESHOLD_2     280
#define LUX_THRESHOLD_3     280
#define LUX_THRESHOLD_4     280
#define LUX_THRESHOLD_5     280


Talkie voice;


int LDR_register = 0;

int tempValA0 = 0;
int tempValA1 = 0;
int tempValA2 = 0;
int tempValA3 = 0;
int tempValA4 = 0;
int tempValA5 = 0;

int tempHiVal = 0;
int tempHiLine = 0;


void setup() 
{

    Serial.begin(115200);
    Serial.println("INITIALIZING TARGET");

    // SET UP PIN MODES
    pinMode(PIN_SPEAKER, OUTPUT);


//    voice.say(spINTRO);
    voice.say(spREADY);


    Serial.println("FINISHED INITIALIZING TARGET");

//    delay(1000);

}


void loop() 
{
/*
  if (analogRead(0) >= LUX_THRESHOLD_0)
  {
    LDR_register |= B00000001;
  }

  if (analogRead(1) >= LUX_THRESHOLD_1)
  {
    LDR_register |= B00000010;
  }

  if (analogRead(2) >= LUX_THRESHOLD_2)
  {
    LDR_register |= B00000100;
  }

  if (analogRead(3) >= LUX_THRESHOLD_3)
  {
    LDR_register |= B00001000;
  }

  if (analogRead(4) >= LUX_THRESHOLD_4)
  {
    LDR_register |= B00010000;
  }

  if (analogRead(5) >= LUX_THRESHOLD_5)
  {
    LDR_register |= B00100000;
  }

*/
  tempValA0 = analogRead(0);
  tempValA1 = analogRead(1);
  tempValA2 = analogRead(2);
  tempValA3 = analogRead(3);
  tempValA4 = analogRead(4);
  tempValA5 = analogRead(5);

  tempHiVal = 0;
  
  if (tempValA0 > tempHiVal)
  {
    tempHiVal = tempValA0;
    tempHiLine = 0;
  }
  if (tempValA1 > tempHiVal)
  {
    tempHiVal = tempValA1;
    tempHiLine = 1;
  }
  if (tempValA2 > tempHiVal)
  {
    tempHiVal = tempValA2;
    tempHiLine = 2;
  }
  if (tempValA3 > tempHiVal)
  {
    tempHiVal = tempValA3;
    tempHiLine = 3;
  }
  if (tempValA4 > tempHiVal)
  {
    tempHiVal = tempValA4;
    tempHiLine = 4;
  }
  if (tempValA5 > tempHiVal)
  {
    tempHiVal = tempValA5;
    tempHiLine = 5;
  }


  if (tempValA0 >= LUX_THRESHOLD_0)
  {
    LDR_register |= B00000001;
  }

  if (tempValA1 >= LUX_THRESHOLD_1)
  {
    LDR_register |= B00000010;
  }

  if (tempValA2 >= LUX_THRESHOLD_2)
  {
    LDR_register |= B00000100;
  }

  if (tempValA3 >= LUX_THRESHOLD_3)
  {
    LDR_register |= B00001000;
  }

  if (tempValA4 >= LUX_THRESHOLD_4)
  {
    LDR_register |= B00010000;
  }

  if (tempValA5 >= LUX_THRESHOLD_5)
  {
    LDR_register |= B00100000;
  }



  if (LDR_register == B00111111)
  {
    voice.say(spROOMS_TOO_BRIGHT);
    Serial.println("ROOM IS TOO BRIGHT");
  }  
  else if (LDR_register != 0)
  {

    // INDICATE HIT OCCURRED
//    voice.say(spHIT, false);
//    voice.say(spGREAT2, false);

    tone(PIN_SPEAKER, 50, 50);
    delay(5);
    noTone(PIN_SPEAKER);    



    Serial.print("HIGH VAL:    ");
    Serial.print(tempHiVal);
        
    Serial.print("    ON LINE:    ");
    Serial.println(tempHiLine);
        

//    Serial.print("LINE 4 =  ");
//    Serial.println(tempValA4);
//        
//    Serial.print("LINE 5 =  ");
//    Serial.println(tempValA5);
//        
//    Serial.println("");

    delay(50);
    
//    Serial.println("HIT");

   
//     // BLINK LED
//    for (int i = 0; i < 8; ++i)
//    {
//      digitalWrite(PIN_LED, HIGH);
//      delay(50);
//      digitalWrite(PIN_LED, LOW);
//      delay(50);
//    }

  }


  

  // END IF  
//  }

  LDR_register = 0;
  
//  tempValA0 = 0;
//  tempValA1 = 0;
//  tempValA2 = 0;
//  tempValA3 = 0;
//  tempValA4 = 0;
//  tempValA5 = 0;
//

// END LOOP
}
