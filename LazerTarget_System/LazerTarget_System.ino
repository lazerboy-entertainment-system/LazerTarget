// BRIAN SUMNER
// KAMIL ADYLOV
// PHI HUYNH
// UCDENVER CSCI 4287
// SPRING 2019
// LAZERBOY ENTERTAINMENT SYSTEM:
// LAZERTARGET DRIVER
// VERSION: BETA_01


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
#define PIN_SWITCH_BTN                2     // button for switching between two game mode. 


#define LDR_LUX_THRESHOLD             280

#define TIMER_INTERVAL_MILLISECONDS   10
#define CPU_MHZ                       16
#define TIMER_PRESCALAR               1024


#define NUM_LEDS                      4

#define LED_FAST_BLINK_CYCLES         5
#define LED_FAST_DELAY_TIME           44
#define LED_SLOW_BLINK_CYCLES         3
#define LED_SLOW_DELAY_TIME           150

#define LED_BRIGHTNESS_LOW            30
#define LED_BRIGHTNESS_HIGH           255


#define NUMBER_OF_GP_TIMERS           8

#define BTN_DEBOUNCE_COUNT            15   // debounce count for switch button


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

const double MAX_TIMER_ISR_COUNT = ((CPU_MHZ * 1000.0) / TIMER_PRESCALAR * TIMER_INTERVAL_MILLISECONDS) - 1;


// ======================================================================================================


// VOLATILE GLOBAL VARIABLES

// array of eight general purpose timer32_t records
volatile timer32_t timer_gpArray[NUMBER_OF_GP_TIMERS];

volatile timer32_t timer_btnDebounce = {0, 0, BTN_DEBOUNCE_COUNT};
volatile uint8_t gpTimerIndex = 0;

volatile bool flag_isBtnEnabled = false;
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
  
    // SET UP PIN MODES
    pinMode(PIN_SPEAKER, OUTPUT);
    pinMode(PIN_SWITCH_BTN, INPUT_PULLUP);                 // D2 input mode with pull-up resistor
  
  
    FastLED.addLeds<WS2812, PIN_LEDS, RGB>(leds, NUM_LEDS);
  
    // DISABLE INTERRUPTS
    cli();
  
    // attach an interrupt on int0 and call ISR_BTN_PRESSED() when triggered
    attachInterrupt(digitalPinToInterrupt(PIN_SWITCH_BTN), ISR_BTN_PRESSED, FALLING);
  
  
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
    flag_isBtnEnabled = true;

  
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
    for (ledIndex = 0; ledIndex < NUM_LEDS; ++ledIndex)
    {
        leds[ledIndex] = CRGB::Black;
        FastLED.show();
    }

  
    Serial.println("FINISHED INITIALIZING TARGET");

}


// ======================================================================================================


// MAIN PROGRAM LOOP
void loop()
{

    // It notifies the player of current mode once after the switch btn is pressed
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
            voice.say(spDUCK);
            voice.say(spDUCK);
            voice.say(spGOOSE);
            game_duckDuckGoose();
            break;
          
    
//        case GAME2:
//    
//            // Game2
//            Serial.println("Game Mode2....");
//            voice.say(spREADY);
//            break;
    
        default:
          
            // Back to Target Practice (Game0)
            Serial.println("Game Mode DEFAULT....");
            voice.say(spTARGET);
            gameMode = GAME_TARGET_PRACTICE;
    }

}


// ======================================================================================================


// INTERRUPT SERVICE ROUTINE FOR INPUT BUTTON
// activates debounce timer and switches to the next game mode once the push button is pressed
void ISR_BTN_PRESSED() 
{
    if (flag_isBtnEnabled) 
    {
        flag_isBtnEnabled = false;
    
        timer_btnDebounce.count = BTN_DEBOUNCE_COUNT;
        timer_btnDebounce.flag_isEnabled = 1;
    
        ++gameMode;
        
        leds[0] = CRGB::Black;
        leds[1] = CRGB::Black;
        leds[2] = CRGB::Black;
        leds[3] = CRGB::Black;
        FastLED.setBrightness(LED_BRIGHTNESS_HIGH);
        FastLED.show();
    
    }
}


// ====================================================================================================== 


// INTERRUPT SERVICE ROUTINE FOR TIMER1
ISR(TIMER0_COMPA_vect)
{
    // After the switch button is pressed, the debounce flag will be enabled
    // The debounce timer will be disabled when its count reaches to zero
    
    if (timer_btnDebounce.flag_isEnabled) 
    {
        if (timer_btnDebounce.count <= 0) 
        {
                timer_btnDebounce.count = BTN_DEBOUNCE_COUNT;
                timer_btnDebounce.flag_isEnabled = 0;
                flag_isBtnEnabled = true;
        }
        else
          --timer_btnDebounce.count;
    }


    // ISR IMPLEMENTATION FOR GENERAL PURPOSE TIMERS
    for (gpTimerIndex = 0; gpTimerIndex < NUMBER_OF_GP_TIMERS; ++gpTimerIndex)
    {
        if (timer_gpArray[gpTimerIndex].flag_isEnabled)
        {
            if (timer_gpArray[gpTimerIndex].count <= 0) 
            {
                timer_gpArray[gpTimerIndex].flag_isEnabled = 0;
                timer_gpArray[gpTimerIndex].flag_doEvent = 1;
            }
            else
                --timer_gpArray[gpTimerIndex].count;
        }
    }
}    


// ====================================================================================================== 


// GENERAL PURPOSE TIMER FUNCTIONS:


// NON-BLOCKING TIMER DELAY
// NOTE: FOR A BLOCKING DELAY, TRY:  while(timer_isActive(timerNumber)); 
void timer_delay(uint8_t timerNumber, uint32_t milliseconds) 
{
    // resets the timer, then sets count to (milliseconds / TIMER_INTERVAL_MILLISECONDS), then starts the timer 
    timer_gpArray[timerNumber].flag_isEnabled = 0;
    timer_gpArray[timerNumber].flag_doEvent = 0;
    timer_gpArray[timerNumber].count = milliseconds / TIMER_INTERVAL_MILLISECONDS;
    timer_gpArray[timerNumber].flag_isEnabled = 1;
}


// sets enabled flag for gp timer
void timer_start(uint8_t timerNumber) 
{
    timer_gpArray[timerNumber].flag_isEnabled = 1;
}


// clears enabled flag for gp timer
void timer_stop(uint8_t timerNumber) 
{
    timer_gpArray[timerNumber].flag_isEnabled = 0;
}


// sets count
void timer_setCount(uint8_t timerNumber, uint32_t count) 
{
    timer_gpArray[timerNumber].count = count;
}


// sets doEvent flag
void timer_setDoEvent(uint8_t timerNumber) 
{
    timer_gpArray[timerNumber].flag_doEvent = 1;
}


// clears doEvent flag
void timer_clearDoEvent(uint8_t timerNumber) 
{
    timer_gpArray[timerNumber].flag_doEvent = 0;
}


// returns true if timer is enabled and greater than 0
bool timer_isActive(uint8_t timerNumber) 
{
    if (timer_gpArray[timerNumber].flag_isEnabled && timer_gpArray[timerNumber].count > 0)
        return true;
    else return false;
}


// RESETS TIMER
void timer_reset(uint8_t timerNumber) 
{
    // resets all record fields to zero for gp timer
    timer_gpArray[timerNumber].flag_isEnabled = 0;
    timer_gpArray[timerNumber].flag_doEvent = 0;
    timer_gpArray[timerNumber].count = 0;
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
