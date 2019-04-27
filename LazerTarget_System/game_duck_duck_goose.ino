void game_duckDuckGoose()
{

    // Duck delay
    uint16_t duck_delay = 1000;
    
    // Goose delay
    uint16_t gooseDelay = 2000;
    
    // Round delay
    uint16_t roundDelay = 1500;
    
    // Random number
    uint8_t rand_num;
    
    // Random max and min
    uint8_t rand_min = 1;
    uint8_t rand_max = 10;

    // Duck index
    uint8_t duckNumber = 0;

    // Success flag
    bool flag_success = false;
    

    randomSeed(analogRead(PIN_LDR_0)+analogRead(PIN_LDR_1)+analogRead(PIN_LDR_2)+analogRead(PIN_LDR_3)+analogRead(PIN_LDR_4)+analogRead(PIN_LDR_5));
    Serial.println("GAME:  START");


    while (gameMode == GAME_DUCK_DUCK_GOOSE)
    {            
        timer_delay(3, roundDelay);
        while (timer_isActive(3) && gameMode == GAME_DUCK_DUCK_GOOSE);

        flag_success = false;

        // Generate random from 1 to 5 for duck
        rand_num = random(rand_min, rand_max);

        Serial.print("NUMBER OF DUCKS:  ");
        Serial.println(rand_num);

        leds[0] = CRGB::Yellow;
        leds[1] = CRGB::Yellow;
        leds[2] = CRGB::Yellow;
        leds[3] = CRGB::Yellow;
        FastLED.setBrightness(LED_BRIGHTNESS_LOW);
        FastLED.show();
        
        for (duckNumber = 0; duckNumber < rand_num; ++duckNumber)
        {

            Serial.print("DUCK:  ");
            Serial.println(duckNumber + 1);
            
            voice.say(spDUCK, false);

            timer_delay(0, 1000);
            while (timer_isActive(0) && gameMode == GAME_DUCK_DUCK_GOOSE)
            {
                if (isTargetHit())
                {
                    Serial.println("YOU LOSE");
                    ledIndex = 0;
                    while (++ledIndex <= LED_SLOW_BLINK_CYCLES)
                    {
                        leds[0] = CRGB::Red;
                        leds[1] = CRGB::Red;
                        leds[2] = CRGB::Red;
                        leds[3] = CRGB::Red;
                        FastLED.show();
                        
                        timer_delay(2, LED_SLOW_DELAY_TIME);
                        while (timer_isActive(2));
                        
                        leds[0] = CRGB::Black;
                        leds[1] = CRGB::Black;
                        leds[2] = CRGB::Black;
                        leds[3] = CRGB::Black;
                        FastLED.show();
    
                        timer_delay(2, LED_SLOW_DELAY_TIME);
                        while (timer_isActive(2));
                    }     

                    timer_delay(3, roundDelay);
                    while (timer_isActive(3));

                    return;
                }
            }
        }

        if (gameMode != GAME_DUCK_DUCK_GOOSE) return;
        
        Serial.println("GOOSE");
        
        voice.say(spGOOSE, false);

        leds[0] = CRGB::Blue;
        leds[1] = CRGB::Blue;
        leds[2] = CRGB::Blue;
        leds[3] = CRGB::Blue;
        FastLED.setBrightness(LED_BRIGHTNESS_LOW);
        FastLED.show();

        timer_delay(1, gooseDelay);
        while (timer_isActive(1) && gameMode == GAME_DUCK_DUCK_GOOSE)
        {
            if (isTargetHit())
            {
                Serial.println("YOU WIN");
                flag_success = true;

                ledIndex = 0;
                FastLED.setBrightness(LED_BRIGHTNESS_HIGH);
                while (++ledIndex <= LED_FAST_BLINK_CYCLES)
                {
                    leds[0] = CRGB::Green;
                    leds[1] = CRGB::Green;
                    leds[2] = CRGB::Green;
                    leds[3] = CRGB::Green;
                    FastLED.show();
                    
                    timer_delay(2, LED_FAST_DELAY_TIME);
                    while (timer_isActive(2));
                    
                    leds[0] = CRGB::Black;
                    leds[1] = CRGB::Black;
                    leds[2] = CRGB::Black;
                    leds[3] = CRGB::Black;
                    FastLED.show();

                    timer_delay(2, LED_FAST_DELAY_TIME);
                    while (timer_isActive(2));
                }              
            }
        }
        
        if (flag_success)
        {
            timer_delay(3, roundDelay);
            while (timer_isActive(3) && gameMode == GAME_DUCK_DUCK_GOOSE);

            voice.say(spREADY, true);
        }
        else 
        {
            ledIndex = 0;
            FastLED.setBrightness(LED_BRIGHTNESS_HIGH);
            while (++ledIndex <= LED_SLOW_BLINK_CYCLES)
            {
                leds[0] = CRGB::Red;
                leds[1] = CRGB::Red;
                leds[2] = CRGB::Red;
                leds[3] = CRGB::Red;
                FastLED.show();
                
                timer_delay(2, LED_SLOW_DELAY_TIME);
                while (timer_isActive(2));
                
                leds[0] = CRGB::Black;
                leds[1] = CRGB::Black;
                leds[2] = CRGB::Black;
                leds[3] = CRGB::Black;
                FastLED.show();
    
                timer_delay(2, LED_SLOW_DELAY_TIME);
                while (timer_isActive(2));
            }     

            timer_delay(3, roundDelay);
            while (timer_isActive(3) && gameMode == GAME_DUCK_DUCK_GOOSE);

            return;
        }
    }

    return;
}
