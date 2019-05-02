void game_targetPractice()
{
    leds_setColor(CRGB::Blue, LED_BRIGHTNESS_LOW);  
    while (gameMode == GAME_TARGET_PRACTICE)
    {      

        ledIndex = 0;
        if (isTargetHit()) 
        {
            
            // INDICATE HIT OCCURRED
  
            // OUTPUT SPEECH FOR HIT EVENT
            // NOTE: USE 'false' ARGUMENT FOR NON-BLOCKING SPEECH
            voice.say(spHIT, false);
  
            // OUTPUT MESSAGE TO SERIAL CONSOLE
            Serial.println("HIT");

            leds_blinkColor(CRGB::Green, LED_BRIGHTNESS_HIGH, LED_FAST_BLINK_CYCLES, LED_FAST_DELAY_TIME, GAME_TARGET_PRACTICE);
            leds_setColor(CRGB::Blue, LED_BRIGHTNESS_LOW);  
        }
    }
    
    return;
}
