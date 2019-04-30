// BRIAN SUMNER
// KAMIL ADYLOV
// PHI HUYNH
// UCDENVER CSCI 4287
// SPRING 2019
// LAZERBOY ENTERTAINMENT SYSTEM:
// LAZERTARGET ZL1 DRIVER
// VERSION: BETA_02


// ======================================================================================================


// INCLUDES

#include <Arduino.h>
#include "talkie.h"
#include "FastLED.h"
#include "vocab.h"
#include "game_modes.h"


// ======================================================================================================


// CONSTANT DEFINITIONS

#define PIN_SPEAKER                   3
#define PIN_LEDS                      12

#define PIN_LDR_0                     14
#define PIN_LDR_1                     15
#define PIN_LDR_2                     16
#define PIN_LDR_3                     17
#define PIN_LDR_4                     18
#define PIN_LDR_5                     19
#define PIN_BUTTON_SWITCH                2     // button for switching between two game mode. 


#define LDR_LUX_THRESHOLD             280

// NOTE:  OUR DYNAMIC MAX_TIMER_ISR_COUNT CALCULATION WAS BEHAVING ALARMINGLY INCONSISTENTLY
//        FOR TIMER0, SO INSTEAD WE ARE EMULATING A TIMER OVERFLOW AND HAVE CALIBRATED THE
//        TIMER INTERVAL FOR OUR DEVICE USING A STOPWATCH
#define TIMER_INTERVAL_MILLISECONDS   16.3
#define MAX_TIMER_ISR_COUNT           255

//#define CPU_MHZ                       16
//#define TIMER_PRESCALAR               1024
//#define TIMER_CALIBRATION             1


#define NUM_LEDS                      4

#define LED_GP_TIMER_NUMBER           7

#define LED_FAST_BLINK_CYCLES         5
#define LED_FAST_DELAY_TIME           75
#define LED_SLOW_BLINK_CYCLES         3
#define LED_SLOW_DELAY_TIME           200

#define LED_BRIGHTNESS_LOW            20
#define LED_BRIGHTNESS_HIGH           255


#define NUMBER_OF_GP_TIMERS           8

#define BUTTON_DEBOUNCE_COUNT            15   // debounce count for switch button


// ======================================================================================================


// TYPE DEFINITIONS
typedef struct timer32_t timer32_t;
struct timer32_t
{
  uint32_t flag_isEnabled     : 1;
  uint32_t flag_doEvent       : 1;
  uint32_t count              : 30;
};


// ======================================================================================================


// GLOBAL CONSTANTS

// SEE NOTE ABOVE WHY WE ARE NOT USING THIS CALCULATION
//const uint32_t MAX_TIMER_ISR_COUNT = (uint32_t) ((CPU_MHZ * 1000.0) / TIMER_PRESCALAR * TIMER_INTERVAL_MILLISECONDS * TIMER_CALIBRATION);


// ======================================================================================================


// VOLATILE GLOBAL VARIABLES

// array of eight general purpose timer32_t records
volatile timer32_t timer_gpArray[NUMBER_OF_GP_TIMERS];

volatile timer32_t timer_buttonDebounce = {0, 0, BUTTON_DEBOUNCE_COUNT};
volatile uint8_t gpTimerIndex = 0;

volatile bool flag_isButtonEnabled = false;
//volatile uint8_t gameMode = GAME_TARGET_PRACTICE;
volatile uint8_t gameMode = GAME_TARGET_PRACTICE;


// ======================================================================================================


// GLOBAL VARIABLES

// VOICE OBJECT FOR SPEECH / AUDIO OUTPUT
Talkie voice;

// USED FOR isTargetHit()
uint8_t LDR_register = 0;
bool flag_isTargetHit = 0;

// USED FOR LEDS
CRGB leds[NUM_LEDS];
uint8_t ledIndex = 0;
uint32_t colorIndex = 0;

// ======================================================================================================


// PROGRAM INITIALIZATION
void setup()
{

    Serial.begin(115200);
    Serial.println("INITIALIZING TARGET");
    Serial.print("MAX_COUNT:  ");
    Serial.println(MAX_TIMER_ISR_COUNT);
  
    // SET UP PIN MODES
    pinMode(PIN_SPEAKER, OUTPUT);
    pinMode(PIN_BUTTON_SWITCH, INPUT_PULLUP);                 // D2 input mode with pull-up resistor
  
  
    FastLED.addLeds<WS2812, PIN_LEDS, RGB>(leds, NUM_LEDS);
  
    // DISABLE INTERRUPTS
    cli();
  
    // attach an interrupt on int0 and call ISR_BUTTON_PRESSED() when triggered
    attachInterrupt(digitalPinToInterrupt(PIN_BUTTON_SWITCH), ISR_BUTTON_PRESSED, FALLING);
  
  
    // CLEAR TIMER/COUNTER REGISTERS
    TCCR0A = 0;
    TCCR0B = 0;
    TCNT0  = 0;
  
    // SET MAX TIMER COUNTER  
    OCR0A = MAX_TIMER_ISR_COUNT;
  
    // CLEAR TIMER ON COMPARE MATCH
    TCCR0B |= (1 << WGM12);
  
    // SET CS12 AND CS10 TO USE PRESCALAR 1024
    TCCR0B |= (1 << CS12);
    TCCR0B |= (1 << CS10);
  
    // ENBABLE TIMER COMPARE INTERRUPT
    TIMSK0 |= (1 << OCIE0A);
  
    // ENABLE INTERRUPTS
    sei();
  

    // ENABLE THE ONLY BUTTON
    flag_isButtonEnabled = true;

  
    // SPEAK INTRO
    voice.say(spINTRO, false);
  
    
    // DO A COOL LED EFFECT WHILE THE INTRO IS BEING SPOKEN
    colorIndex = 0;
    while (voice.talking())
    {
        for (ledIndex = 0; ledIndex < NUM_LEDS; ++ledIndex)
        {
            leds[ledIndex] = ColorFromPalette(RainbowColors_p, colorIndex, LED_BRIGHTNESS_HIGH, LINEARBLEND);
            colorIndex += 30;
            FastLED.show();
        }
    }


    // RESET LEDS
    leds_setColor(CRGB::Black, LED_BRIGHTNESS_HIGH);
    
  
    Serial.println("FINISHED INITIALIZING TARGET");

}


// ======================================================================================================


// MAIN PROGRAM LOOP
void loop()
{

    // It notifies the player of current mode once after the switch button is pressed
    // Then, one of the game types will be played according to the game mode
    switch (gameMode) 
    {
  
        case GAME_TARGET_PRACTICE: 
        
            // Target Practice
            Serial.println("GAME:  TARGET PRACTICE");
            game_targetPractice();
            break;    
    
        case GAME_DUCK_DUCK_GOOSE:

            // Duck Duck Goose game mode
            Serial.println("GAME:  DUCK DUCK GOOSE");
            if (gameMode == GAME_DUCK_DUCK_GOOSE) voice.say(spDUCK);
            if (gameMode == GAME_DUCK_DUCK_GOOSE) voice.say(spDUCK);
            if (gameMode == GAME_DUCK_DUCK_GOOSE) voice.say(spGOOSE);
            game_duckDuckGoose();
            break;
          
    
        case GAME_DRAW:
    
            // Draw!
            Serial.println("GAME:  DRAW!");
            voice.say(spDRAW);
            game_draw();
            break;
    
        default:
          
            // Back to Target Practice (Game0)
            Serial.println("Game Mode DEFAULT....");
            voice.say(spTARGET);
            gameMode = GAME_TARGET_PRACTICE;
    }

    leds_setColor(CRGB::Black, LED_BRIGHTNESS_HIGH);
    timer_delay(0, 1000);
}


// ======================================================================================================


// INTERRUPT SERVICE ROUTINE FOR INPUT BUTTON
// activates debounce timer and switches to the next game mode once the push button is pressed
void ISR_BUTTON_PRESSED() 
{
    if (flag_isButtonEnabled) 
    {
        flag_isButtonEnabled = false;
    
        timer_buttonDebounce.count = BUTTON_DEBOUNCE_COUNT;
        timer_buttonDebounce.flag_isEnabled = 1;
    
        ++gameMode;

        // LEDS ARE TURNED OFF IN LOOP
//        leds_setColor(CRGB::Black, LED_BRIGHTNESS_HIGH);
    
    }
}


// ====================================================================================================== 

void leds_setColor(CRGB color, uint8_t brightness)
{
    FastLED.setBrightness(brightness);
    leds[0] = color;
    leds[1] = color;
    leds[2] = color;
    leds[3] = color;
    FastLED.show();  
}


// NOTE: TO AVOID HUGE HASSLES WITH THE COMPILER, THIS FUNCTION MUST BE IN THIS .INO FILE
void leds_blinkColor(CRGB color, uint8_t brightness, uint8_t numCycles, uint32_t delayTime, uint8_t arg_gameMode)
{
  
    FastLED.setBrightness(brightness);
    
    ledIndex = 0;
    while (++ledIndex <= numCycles && gameMode == arg_gameMode)
    {
        leds[0] = color;
        leds[1] = color;
        leds[2] = color;
        leds[3] = color;
        FastLED.show();
        
        timer_delay(LED_GP_TIMER_NUMBER, delayTime);
        while (timer_isActive(LED_GP_TIMER_NUMBER));
        
        leds[0] = CRGB::Black;
        leds[1] = CRGB::Black;
        leds[2] = CRGB::Black;
        leds[3] = CRGB::Black;
        FastLED.show();

        timer_delay(LED_GP_TIMER_NUMBER, delayTime);
        while (timer_isActive(LED_GP_TIMER_NUMBER)); 
    }
}



// ====================================================================================================== 


// RETURNS TRUE IF THE TARGET HAS BEEN HIT
bool isTargetHit() {

    flag_isTargetHit = true;
    LDR_register = 0;
  
    if (analogRead(PIN_LDR_0) >= LDR_LUX_THRESHOLD)
        LDR_register |= B00000001;
  
    if (analogRead(PIN_LDR_1) >= LDR_LUX_THRESHOLD)
        LDR_register |= B00000010;
  
    if (analogRead(PIN_LDR_2) >= LDR_LUX_THRESHOLD)
        LDR_register |= B00000100;
  
    if (analogRead(PIN_LDR_3) >= LDR_LUX_THRESHOLD)
        LDR_register |= B00001000;
  
    if (analogRead(PIN_LDR_4) >= LDR_LUX_THRESHOLD)
        LDR_register |= B00010000;
  
    if (analogRead(PIN_LDR_5) >= LDR_LUX_THRESHOLD)
        LDR_register |= B00100000;
  
  
    if (LDR_register == B00111111)
    {
      voice.say(spROOMS_TOO_BRIGHT);
      Serial.println("ROOM IS TOO BRIGHT");
      flag_isTargetHit = false;
    }
    else if (LDR_register == 0)
      flag_isTargetHit = false;
  
  
    return flag_isTargetHit;
}


// ======================================================================================================
