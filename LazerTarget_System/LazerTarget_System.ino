// BRIAN SUMNER
// PHI HUYNH
// KAMIL ADYLOV
// UCDENVER CSCI 4287
// SPRING 2019
// LAZERBOY ENTERTAINMENT SYSTEM:
// LAZERTARGET DRIVER
// GAME DEVELOPMENT MODULE
// VERSION: ALPHA_02




// INCLUDES
#include <Arduino.h>


#include "talkie.h"
#include "FastLED.h"
#include "vocab.h"
#include "game_mode.h"

// CONSTANT DEFINITIONS
#define PIN_SPEAKER       3

#define PIN_LED_RED       13
#define PIN_LED_GREEN     13
#define PIN_LED_BLUE      13

#define PIN_GDM_LDR       14    // THIS IS ANALOG PIN A0

#define PIN_SWITCH_BTN    2     // button for switching between two game mode. 
#define PIN_LED           6
#define LUX_THRESHOLD_GDM_LDR   280

#define LED_BLINK_DELAY   80
#define LED_BLINK_CYCLES  5

#define TIMER_INTERVAL_MILLISECONDS   4
#define CPU_MHZ                       16
#define TIMER_PRESCALAR               1024

#define NUMBER_OF_GDM_LDRS 6

#define NUM_LEDS 1
#define NUMBER_OF_GP_TIMERS 8

// ------------------------------------------------------------------------------------------------------
// VOICE OBJECT FOR SPEECH / AUDIO OUTPUT
Talkie voice;


// TYPE DEFINITIONS
typedef struct timer32_t timer32_t;
struct timer32_t
{
  bool flag_isEnabled     : 1;
  uint32_t count          : 31;
  uint32_t maxCount       : 31;
  bool flag_doEvent       : 1;
};

// GLOBAL CONSTANTS
const double MAX_TIMER_ISR_COUNT = ((CPU_MHZ * 1000.0) / TIMER_PRESCALAR * TIMER_INTERVAL_MILLISECONDS) - 1;

#define BTN_DEBOUNCE_TIME 15   // debounce time whose value is 100ms

// array of eight general purpose timer32_t records
volatile timer32_t timer_gpArray[8] = {0, 0, 31, 0};
volatile timer32_t timer_btnDebounce = {false, 0, BTN_DEBOUNCE_TIME , false};

// -----------------------------------------------------------------------------------------------------------------------------------------
volatile bool flag_isBtnEnabled = false;
volatile int game_mode = 0;
volatile bool flag_activateGameModeVoice = false;
volatile bool flag_targetHit = false;
volatile unsigned long lastTime = millis();                       // store current time in milliseconds after the program starts

// -----------------------------------------------------------------------------------------------------------------------------------------
// FORWARD DECLARATIONS:

bool isTargetHit();     // RETURN TRUE IF THE TARGET HAS BEEN HIT

void blinkRedLED();     // BLINKS THE RED LED
void blinkGreenLED();   // BLINKS THE GREEN LED
void blinkBlueLED();    // BLINKS THE BLUE LED

bool isRoomTooBright();  // RETURN TRUE IF ROOM IS TOO BRIGHT FOR PLAYING THE GAME

// -----------------------------------------------------------------------------------------------------------------------------------------
CRGB leds[NUM_LEDS];


// PROGRAM INITIALIZATION
void setup()
{

  Serial.begin(115200);
  Serial.println("INITIALIZING TARGET");

  // SET UP PIN MODES
  pinMode(PIN_SPEAKER, OUTPUT);
  pinMode(PIN_SWITCH_BTN, INPUT_PULLUP);                 // D2 input mode with pull-up resistor


  FastLED.addLeds<WS2812, PIN_LED, RGB>(leds, NUM_LEDS);
// FastLED.setBrightness(1);

  // DISABLE INTERRUPTS
  cli();

  // attach an interrupt on int0 and call ISR_BTN_PRESSED() when triggered
  attachInterrupt(digitalPinToInterrupt(PIN_SWITCH_BTN), ISR_BTN_PRESSED, FALLING);


  // CLEAR TIMER/COUNTER REGISTERS
  TCCR0A = 0;
  TCCR0B = 0;
  TCNT0  = 0;

  // SET MAX TIMER COUNTER    Serial.print("mode: ");
  Serial.println(game_mode);
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



  voice.say(spINTRO);

  game_mode = -1;
  flag_activateGameModeVoice = false;
  flag_isBtnEnabled = true;

  Serial.print("mode: ");
  Serial.println(game_mode);

  Serial.println("FINISHED INITIALIZING TARGET");
}

// MAIN PROGRAM LOOP
void loop()
{

  leds[0] = CRGB::Red;
  FastLED.show();
  delay(1000);

  leds[0] = CRGB::Black;
  FastLED.show();
  delay(1000);


  
  if (timer_btnDebounce.flag_doEvent)  {
    if (digitalRead(PIN_SWITCH_BTN) == HIGH) {
      timer_btnDebounce.flag_doEvent = false;
      timer_btnDebounce.count = BTN_DEBOUNCE_TIME;
      flag_isBtnEnabled = true;
    }
  }


  // It notifies the player of current mode once after the switch btn is pressed
  // Then, one of the game types will be played according to the game mode
  switch (game_mode) {
    case GAME0: {                                     // Target Mode

        Serial.println("Game Mode0....");
        if (flag_activateGameModeVoice)
          voice.say(spREADY, false);

        flag_activateGameModeVoice = false;


        if (isTargetHit())
        {
          // INDICATE HIT OCCURRED

          // OUTPUT SPEECH FOR HIT EVENT
          // NOTE: USE 'false' ARGUMENT FOR NON-BLOCKING SPEECH
          voice.say(spHIT, false);

          // OUTPUT MESSAGE TO SERIAL CONSOLE
          Serial.println("HIT");

          // BLINK LED
          //blinkGreenLED();



        }       // END IF
        break;
      }

    case GAME1: {                                     // Duck Duck game mode                                         

        Serial.println("Game Mode1....");

        if (flag_activateGameModeVoice)
          voice.say(spREADY);

        flag_activateGameModeVoice = false;

        break;
      }

    case GAME2: {                                     // Director Mode?

        Serial.println("Game Mode2....");
        if (flag_activateGameModeVoice)
          voice.say(spREADY);

        flag_activateGameModeVoice = false;
        break;
      }

//          default:
//            Serial.println("Game Mode DEFAULT....");
//            voice.say(spGREAT2);
//            game_mode = -1;
  }


}

// activates debounce timer and switches to the next game mode once the push button is pressed
// In addition, when the button is pressed in order to switch to consequence game mode,
// the voice will inform the player of what game mode is activated
void ISR_BTN_PRESSED() {


  if (flag_isBtnEnabled) {
    flag_isBtnEnabled = false;

    timer_btnDebounce.flag_isEnabled = true;

    game_mode += 1;

    flag_activateGameModeVoice = true;


  }

}


// INTERRUPT SERVICE ROUTINE FOR TIMER1
ISR(TIMER0_COMPA_vect)
{

  if (timer_btnDebounce.flag_isEnabled) {

    if (timer_btnDebounce.count <= 0) {
      timer_btnDebounce.flag_isEnabled = false;
      timer_btnDebounce.flag_doEvent = true;
    }
    else
      --timer_btnDebounce.count;
  }

  //  if (isTargetHit()) {
  //    flag_targetHit = true;
  //   // Serial.println("HIT00000");
  //  }
}

// sets enabled flag for gp timer
void timer_start(uint32_t timerNumber) {
  timer_gpArray[timerNumber].flag_isEnabled = true;
}

// clears enabled flag for gp timer
void timer_stop(uint32_t timerNumber) {
  timer_gpArray[timerNumber].flag_isEnabled = false;

}

// sets count
void timer_setCount(uint32_t timerNumber, uint32_t count) {
  timer_gpArray[timerNumber].count = count;
}

// sets maxCount
void timer_setMaxCount(int timerNumber, uint32_t maxCount) {
  timer_gpArray[timerNumber].maxCount = maxCount;
}

// sets doEvent flag
void timer_setDoEvent(uint32_t timerNumber) {
  timer_gpArray[timerNumber].flag_doEvent = true;
}


// clears doEvent flag
void timer_clearDoEvent(uint32_t timerNumber) {
  timer_gpArray[timerNumber].flag_doEvent = false;
}

// returns true if timer is enabled and greater than 0
bool timer_isActive(uint32_t timerNumber) {

  if (timer_gpArray[timerNumber].flag_isEnabled && timer_gpArray[timerNumber].count > 0)
    return true;

  else return false;

}

// RETURN TRUE IF THE TARGET HAS BEEN HIT
bool isTargetHit() {

  if (analogRead(0) >= LUX_THRESHOLD_GDM_LDR)
    return true;

  if (analogRead(1) >= LUX_THRESHOLD_GDM_LDR)
    return true;

  if (analogRead(2) >= LUX_THRESHOLD_GDM_LDR)
    return true;

  if (analogRead(3) >= LUX_THRESHOLD_GDM_LDR)
    return true;

  if (analogRead(4) >= LUX_THRESHOLD_GDM_LDR)
    return true;

  if (analogRead(5) >= LUX_THRESHOLD_GDM_LDR)
    return true;

  if (analogRead(6) >= LUX_THRESHOLD_GDM_LDR)
    return true;

  return false;
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
void blinkBlueLED() {

  // BLINK LED
  for (int i = 0; i < LED_BLINK_CYCLES; ++i)
  {
    digitalWrite(PIN_LED_RED, HIGH);
    delay(LED_BLINK_DELAY);
    digitalWrite(PIN_LED_RED, LOW);
    delay(LED_BLINK_DELAY);
  }
}



bool isRoomTooBright() {

  bool flag = false;

  int LDR_register = 0;

  for (int i = 0; i < NUMBER_OF_GDM_LDRS; ++i) {
    if (analogRead(i) >= LUX_THRESHOLD_GDM_LDR) {
      LDR_register |= (LDR_register << (i + 1));
    }
  }

  //  if (analogRead(0) >= LUX_THRESHOLD_GDM_LDR)
  //    LDR_register |= B00000001;
  //
  //  if (analogRead(1) >= LUX_THRESHOLD_GDM_LDR)
  //    LDR_register |= B00000010;
  //
  //  if (analogRead(2) >= LUX_THRESHOLD_GDM_LDR)
  //    LDR_register |= B00000100;
  //
  //  if (analogRead(3) >= LUX_THRESHOLD_GDM_LDR)
  //    LDR_register |= B00001000;
  //
  //  if (analogRead(4) >= LUX_THRESHOLD_GDM_LDR)
  //    LDR_register |= B00010000;
  //
  //  if (analogRead(5) >= LUX_THRESHOLD_GDM_LDR)
  //    LDR_register |= B00100000;



  if (LDR_register == B00111111)
  {
    voice.say(spROOMS_TOO_BRIGHT);
    Serial.println("ROOM IS TOO BRIGHT");
    flag = true;
  }


  LDR_register = 0;

  return flag;
}
