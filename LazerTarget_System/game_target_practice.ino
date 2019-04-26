int game_target_practice()
{
    while (gameMode == GAME_TARGET_PRACTICE)
    {        
        int ledIndex = 0;
        if (isTargetHit()) 
        {
            
            // INDICATE HIT OCCURRED
  
            // OUTPUT SPEECH FOR HIT EVENT
            // NOTE: USE 'false' ARGUMENT FOR NON-BLOCKING SPEECH
            voice.say(spHIT, false);
  
            // OUTPUT MESSAGE TO SERIAL CONSOLE
            Serial.println("HIT");

            ledIndex = 0;
            while (++ledIndex <= LED_BLINK_CYCLES)
            {
                leds[0] = CRGB::Green;
                leds[1] = CRGB::Green;
                leds[2] = CRGB::Green;
                leds[3] = CRGB::Green;
                FastLED.show();
                delay(LED_DELAY_TIME);
                
                leds[0] = CRGB::Black;
                leds[1] = CRGB::Black;
                leds[2] = CRGB::Black;
                leds[3] = CRGB::Black;
                FastLED.show();
                delay(LED_DELAY_TIME);
            }              
        }
    }
    
    return 0;
}
