// BRIAN SUMNER
// KAMIL ADYLOV
// PHI HUYNH
// UCDENVER CSCI 4287
// SPRING 2019
// LAZERBOY ENTERTAINMENT SYSTEM:
// LAZERTARGET DRIVER
// VERSION: ALPHA_04




// INCLUDES
#include <Arduino.h>
#include "talkie.h"
#include "FastLED.h"
#include "vocab.h"
#include "game_mode.h"

// CONSTANT DEFINITIONS
#define PIN_SPEAKER                   3
#define PIN_LED_GREEN                 12
#define PIN_GDM_LDR                   14    // THIS IS ANALOG PIN A0
#define PIN_SWITCH_BTN                2     // button for switching between two game mode. 


#define LUX_THRESHOLD_GDM_LDR         280

#define TIMER_INTERVAL_MILLISECONDS   10
#define CPU_MHZ                       16
#define TIMER_PRESCALAR               1024
#define NUMBER_OF_GDM_LDRS            6

#define NUM_LEDS                      4
#define LED_BLINK_CYCLES              5
#define LED_DELAY_TIME                4

#define NUMBER_OF_GP_TIMERS           8

#define BTN_DEBOUNCE_COUNT            15   // debounce count for switch button

// ------------------------------------------------------------------------------------------------------
// VOICE OBJECT FOR SPEECH / AUDIO OUTPUT
Talkie voice;


// TYPE DEFINITIONS
typedef struct timer32_t timer32_t;
struct timer32_t
{
  uint32_t flag_isEnabled     : 1;
  uint32_t count              : 31;
  uint32_t maxCount           : 31;
  uint32_t flag_doEvent       : 1;
};

// GLOBAL CONSTANTS
const double MAX_TIMER_ISR_COUNT = ((CPU_MHZ * 1000.0) / TIMER_PRESCALAR * TIMER_INTERVAL_MILLISECONDS) - 1;

// array of eight general purpose timer32_t records
volatile timer32_t timer_gpArray[8] = {0, 0, 31, 0};
volatile timer32_t timer_btnDebounce = {0, 0, BTN_DEBOUNCE_COUNT , 0};


// timers for turning on and off the leds
volatile timer32_t timer_ledOn = {0, LED_DELAY_TIME, LED_DELAY_TIME , 0};
volatile timer32_t timer_ledOff = {0, LED_DELAY_TIME, LED_DELAY_TIME , 0};

// -----------------------------------------------------------------------------------------------------------------------------------------
volatile bool flag_isBtnEnabled = false;
volatile int gameMode = 0;
volatile int led_blinkCounter = LED_BLINK_CYCLES;      // counter of how many times leds will blink


// array of leds
CRGB leds[NUM_LEDS];


// -----------------------------------------------------------------------------------------------------------------------------------------
// FORWARD DECLARATIONS:

bool isTargetHit();     // RETURN TRUE IF THE TARGET HAS BEEN HIT

void blinkRedLED();     // BLINKS THE RED LED
void blinkGreenLED();   // BLINKS THE GREEN LED
void blinkBlueLED();    // BLINKS THE BLUE LED

bool isRoomTooBright();  // RETURN TRUE IF ROOM IS TOO BRIGHT FOR PLAYING THE GAME

// -----------------------------------------------------------------------------------------------------------------------------------------


// PROGRAM INITIALIZATION
void setup()
{

    Serial.begin(115200);
    Serial.println("INITIALIZING TARGET");
  
    // SET UP PIN MODES
    pinMode(PIN_SPEAKER, OUTPUT);
    pinMode(PIN_SWITCH_BTN, INPUT_PULLUP);                 // D2 input mode with pull-up resistor
  
  
    FastLED.addLeds<WS2812, PIN_LED_GREEN, RGB>(leds, NUM_LEDS);
  
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
  
  
  
//    voice.say(spINTRO, false);
  
    gameMode = -1;
    flag_isBtnEnabled = true;
  
    
    // Do a cool LED effect while the intro is being spoken
    int colorIndex = 0;
    while (voice.talking())
    {
        for (int i = 0; i < NUM_LEDS; ++i)
        {
            leds[i] = ColorFromPalette(RainbowColors_p, colorIndex, 255, LINEARBLEND);
            colorIndex += 30;
            FastLED.show();
        }
    }
    // Reset LEDs
    for (int i = 0; i < NUM_LEDS; ++i)
    {
        leds[i] = CRGB::Black;
        FastLED.show();
    }
  
    Serial.println("FINISHED INITIALIZING TARGET");
}

// MAIN PROGRAM LOOP
void loop()
{

    // It notifies the player of current mode once after the switch btn is pressed
    // Then, one of the game types will be played according to the game mode
    switch (gameMode) 
    {
  
        case GAME_TARGET_PRACTICE: 
        
            // Target Practice
            Serial.println("Game Mode0....");
            voice.say(spTARGET);
            game_target_practice();
            break;    
    
        case GAME_DUCK_DUCK_GOOSE:

            // Duck Duck Goose game mode
            Serial.println("Game Mode1....");
            voice.say(spGREAT2);
            game_duck_duck_goose();
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
            gameMode = 0;
    }


}

// activates debounce timer and switches to the next game mode once the push button is pressed
// In addition, when the button is pressed in order to switch to consequence game mode,
// the voice will inform the player of what game mode is activated
// Moreover, disable led timer
void ISR_BTN_PRESSED() 
{
    if (flag_isBtnEnabled) 
    {
        flag_isBtnEnabled = false;
    
        timer_btnDebounce.count = BTN_DEBOUNCE_COUNT;
        timer_btnDebounce.flag_isEnabled = 1;
    
        gameMode += 1;
    
        disableLED_timers();
    }
}


// INTERRUPT SERVICE ROUTINE FOR TIMER1
ISR(TIMER0_COMPA_vect)
{
  /* after the switch button is pressed, the debounce flag will be enabled
    // the debounce timer will be disabled when its count reaches to zero
    // and the switch is no longer depressed
  */
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

  // both timers (ledOn and ledOff) will be kept enabled and disabled until the blink counter reaches to zero
  if (led_blinkCounter >= 0) {

    if (timer_ledOn.flag_isEnabled == 1) {

      if (timer_ledOn.count <= 0) {
        timer_ledOn.flag_isEnabled = 0;

        timer_ledOn.flag_doEvent = 1;

        timer_ledOn.count = LED_DELAY_TIME;

        timer_ledOff.flag_isEnabled = 1;

      }
      else
        --timer_ledOn.count;
    }

    // after the ledOn timer is expired, activate ledOff timer
    // deactivate the ledoff timer after its counter reaches to zero
    if (timer_ledOff.flag_isEnabled) 
    {
        if (timer_ledOff.count <= 0) 
        {
  
          timer_ledOff.flag_isEnabled = 0;
  
          timer_ledOff.flag_doEvent = 1;
  
          timer_ledOff.count = LED_DELAY_TIME;
  
          timer_ledOn.flag_isEnabled = 1;

      }
      else
          --timer_ledOff.count;
    }

    // reset enable flags of both timers (ledOn and ledOff) after leds blink the specified amount of time
  } else if (led_blinkCounter == 0) {
    timer_ledOff.flag_isEnabled = 0;
    timer_ledOn.flag_isEnabled = 0;
  }

}

// sets enabled flag for gp timer
void timer_start(uint8_t timerNumber) {
  timer_gpArray[timerNumber].flag_isEnabled = 1;
}

// clears enabled flag for gp timer
void timer_stop(uint8_t timerNumber) {
  timer_gpArray[timerNumber].flag_isEnabled = 0;

}

// sets count
void timer_setCount(uint8_t timerNumber, uint32_t count) {
  timer_gpArray[timerNumber].count = count;
}

// sets maxCount
void timer_setMaxCount(uint8_t timerNumber, uint32_t maxCount) {
  timer_gpArray[timerNumber].maxCount = maxCount;
}

// sets doEvent flag
void timer_setDoEvent(uint8_t timerNumber) {
  timer_gpArray[timerNumber].flag_doEvent = 1;
}


// clears doEvent flag
void timer_clearDoEvent(uint8_t timerNumber) {
  timer_gpArray[timerNumber].flag_doEvent = 0;
}

// returns true if timer is enabled and greater than 0
bool timer_isActive(uint8_t timerNumber) {

  if (timer_gpArray[timerNumber].flag_isEnabled && timer_gpArray[timerNumber].count > 0)
    return true;

  else return false;

}

/* enables or disables leds timer (e.g. timer_ledOn)
   and reset blink counter and the led's timer' counter to their default values
*/
void enableLED_timer() {

  timer_ledOn.count = LED_DELAY_TIME;
  timer_ledOn.flag_isEnabled = 1;
}


/*
  disables led timers (e.g timer_ledOn and timer_ledOff)
  and set their counters to default values
*/
void disableLED_timers() {

  timer_ledOn.flag_isEnabled = timer_ledOff.flag_isEnabled = 0;
  timer_ledOn.count = timer_ledOff.count = LED_DELAY_TIME;
}




bool isTargetHit() {

  bool flag = true;

  int LDR_register = 0;

  if (analogRead(0) >= LUX_THRESHOLD_GDM_LDR)
    LDR_register |= B00000001;

  if (analogRead(1) >= LUX_THRESHOLD_GDM_LDR)
    LDR_register |= B00000010;

  if (analogRead(2) >= LUX_THRESHOLD_GDM_LDR)
    LDR_register |= B00000100;

  if (analogRead(3) >= LUX_THRESHOLD_GDM_LDR)
    LDR_register |= B00001000;

  if (analogRead(4) >= LUX_THRESHOLD_GDM_LDR)
    LDR_register |= B00010000;

  if (analogRead(5) >= LUX_THRESHOLD_GDM_LDR)
    LDR_register |= B00100000;


  if (LDR_register == B00111111)
  {
    voice.say(spROOMS_TOO_BRIGHT);
    Serial.println("ROOM IS TOO BRIGHT");
    flag = false;
  }
  else if (LDR_register == 0)
    flag = false;

  LDR_register = 0;

  return flag;
}
