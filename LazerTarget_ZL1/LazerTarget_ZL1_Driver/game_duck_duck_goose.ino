void game_duckDuckGoose()
{

    // Duck delay
    uint16_t delay_duck = 1500;
    
    // Goose delay
    uint16_t delay_goose = 5000;
    
    // Round delay
    uint16_t delay_round = 1500;

    // Speedup Factor
    float speedupFactor = 0.8;
    
    // Random number
    uint8_t rand_num;
    
    // Random max and min
    uint8_t rand_min = 1;
    uint8_t rand_max = 5;

    // Duck index
    uint8_t duckNumber = 0;

    // Success flag
    bool flag_success = false;
    

    randomSeed(analogRead(PIN_LDR_0)+analogRead(PIN_LDR_1)+analogRead(PIN_LDR_2)+analogRead(PIN_LDR_3)+analogRead(PIN_LDR_4)+analogRead(PIN_LDR_5));
    Serial.println("GAME:  START");

//    voice.say(spSHOOT_GOOSE, true);
//    voice.say(spDONT_SHOOT_DUCKS, true);

    while (gameMode == GAME_DUCK_DUCK_GOOSE)
    {            
        
        timer_delay(3, delay_round);
        while (timer_isActive(3) && gameMode == GAME_DUCK_DUCK_GOOSE);

        flag_success = false;

        // Generate random from 1 to 5 for duck
        rand_num = random(rand_min, rand_max);

        Serial.print("NUMBER OF DUCKS:  ");
        Serial.println(rand_num);

        leds_setColor(CRGB::Yellow, LED_BRIGHTNESS_LOW);

        
        for (duckNumber = 0; duckNumber < rand_num; ++duckNumber)
        {

            Serial.print("DUCK:  ");
            Serial.println(duckNumber + 1);
            
            voice.say(spDUCK, false);

            timer_delay(0, delay_duck);
            while ((timer_isActive(0) || voice.talking()) && gameMode == GAME_DUCK_DUCK_GOOSE)
            {
                if (isTargetHit())
                {
                    Serial.println("YOU LOSE");

                    leds_blinkColor(CRGB::Red, LED_BRIGHTNESS_HIGH, LED_SLOW_BLINK_CYCLES, LED_SLOW_DELAY_TIME, GAME_DUCK_DUCK_GOOSE);

                    timer_delay(3, delay_round);
                    while (timer_isActive(3));

                    return;
                }
            }

        }

        if (gameMode != GAME_DUCK_DUCK_GOOSE) return;
        
        Serial.println("GOOSE");
        
        voice.say(spGOOSE, false);

        leds_setColor(CRGB::Blue, LED_BRIGHTNESS_LOW);

        timer_delay(1, delay_goose);
        while ((timer_isActive(1) || voice.talking()) && gameMode == GAME_DUCK_DUCK_GOOSE)
        {
            if (isTargetHit())
            {
                Serial.println("YOU WIN");
                flag_success = true;

                leds_blinkColor(CRGB::Green, LED_BRIGHTNESS_HIGH, LED_FAST_BLINK_CYCLES, LED_FAST_DELAY_TIME, GAME_DUCK_DUCK_GOOSE);

            }
        }

        // BLOCK UNTIL SPEECH FINISHED IN CASE TARGET WINDOW IS SHORTER THAN SPEECH DURATION
        while(voice.talking() && gameMode == GAME_DUCK_DUCK_GOOSE);

        
        if (flag_success)
        {
            timer_delay(3, delay_round);
            while (timer_isActive(3) && gameMode == GAME_DUCK_DUCK_GOOSE);

            voice.say(spGREAT2);

            delay_duck *= speedupFactor;
            delay_goose *= speedupFactor;
        }
        else 
        {
            // SHOOT THE GOOSE!
            leds_blinkColor(CRGB::Red, LED_BRIGHTNESS_HIGH, LED_SLOW_BLINK_CYCLES, LED_SLOW_DELAY_TIME, GAME_DUCK_DUCK_GOOSE);

            timer_delay(3, delay_round);
            while (timer_isActive(3) && gameMode == GAME_DUCK_DUCK_GOOSE);

            return;
        }
    }

    return;
}
