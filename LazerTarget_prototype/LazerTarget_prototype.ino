// BRIAN SUMNER
// IN AFFILIATION WITH KAMIL ADYLOV AND PHI HUYNH
// UCDENVER CSCI 4287
// SPRING 2019
// LAZERBOY ENTERTAINMENT SYSTEM:
// LAZERTARGET DRIVER
// PROTOTYPE
// VERSION: ALPHA_05


#include <Arduino.h>

#include "talkie.h"
#include "vocab.h"

#define PIN_SPEAKER       3
#define PIN_LED           13
     
#define LUX_THRESHOLD_0     300
#define LUX_THRESHOLD_1     300
#define LUX_THRESHOLD_2     300
#define LUX_THRESHOLD_3     300
#define LUX_THRESHOLD_4     300
#define LUX_THRESHOLD_5     300


Talkie voice;


int LDR_register = 0;

int tempValA0 = 0;
int tempValA1 = 0;
int tempValA2 = 0;
int tempValA3 = 0;
int tempValA4 = 0;
int tempValA5 = 0;


void setup() 
{

    Serial.begin(115200);
    Serial.println("INITIALIZING TARGET");

    // SET UP PIN MODES
    pinMode(PIN_SPEAKER, OUTPUT);


    voice.say(spINTRO);


    Serial.println("FINISHED INITIALIZING TARGET");

}


void loop() 
{

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


//  tempValA0 = analogRead(0);
//  tempValA1 = analogRead(1);
//  tempValA2 = analogRead(2);
//  tempValA3 = analogRead(3);
//  tempValA4 = analogRead(4);
//  tempValA5 = analogRead(5);
//
//
//  if (tempValA0 >= LUX_THRESHOLD_0)
//  {
//    LDR_register |= B00000001;
//  }
//
//  if (tempValA1 >= LUX_THRESHOLD_1)
//  {
//    LDR_register |= B00000010;
//  }
//
//  if (tempValA2 >= LUX_THRESHOLD_2)
//  {
//    LDR_register |= B00000100;
//  }
//
//  if (tempValA3 >= LUX_THRESHOLD_3)
//  {
//    LDR_register |= B00001000;
//  }
//
//  if (tempValA4 >= LUX_THRESHOLD_4)
//  {
//    LDR_register |= B00010000;
//  }
//
//  if (tempValA5 >= LUX_THRESHOLD_5)
//  {
//    LDR_register |= B00100000;
//  }



  if (LDR_register == B00111111)
  {
    voice.say(spROOMS_TOO_BRIGHT);
    Serial.println("ROOM IS TOO BRIGHT");
  }  
  else if (LDR_register != 0)
  {

    // INDICATE HIT OCCURRED
    voice.say(spHIT, false);
    
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

//    Serial.print("LINE 0 =  ");
//    Serial.println(tempValA0);
//        
//    Serial.print("LINE 1 =  ");
//    Serial.println(tempValA1);
//        
//    Serial.print("LINE 2 =  ");
//    Serial.println(tempValA2);
//        
//    Serial.print("LINE 3 =  ");
//    Serial.println(tempValA3);
//        
//    Serial.print("LINE 4 =  ");
//    Serial.println(tempValA4);
//        
//    Serial.print("LINE 5 =  ");
//    Serial.println(tempValA5);
//        
//    Serial.println("");


  

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
