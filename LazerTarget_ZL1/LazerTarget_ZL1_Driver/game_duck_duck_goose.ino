#define MAX_DELAY_DUCK          2000
#define MAX_DELAY_GOOSE         7000
#define DELAY_MISTAKE           500
#define DELAY_SUCCESS           1000
#define DELAY_ROUND_START       1500
#define DELAY_ROUND_END         5000
#define SPEEDUP_FACTOR          0.7

#define RAND_MIN_DEFAULT        1
#define RAND_MAX_DEFAULT        5
#define RAND_MAX_ADD_PER_ROUND  1


void game_duckDuckGoose()
{
    if (gameMode == GAME_DUCK_DUCK_GOOSE)
    {
    
        // Duck delay
        uint16_t delay_duck = MAX_DELAY_DUCK;
        
        // Goose delay
        uint16_t delay_goose = MAX_DELAY_GOOSE;
        
        // Random number
        uint8_t rand_numberOfDucks;
        
        // Random max and min
        uint8_t rand_min = RAND_MIN_DEFAULT;
        uint8_t rand_max = RAND_MAX_DEFAULT;
    
        // Duck index
        uint8_t duckNumber = 0;
    
        // Flags
        bool flag_shotDuck = false;
        bool flag_shotGoose = false;
        
    
        randomSeed(analogRead(PIN_LDR_0)+analogRead(PIN_LDR_1)+analogRead(PIN_LDR_2)+analogRead(PIN_LDR_3)+analogRead(PIN_LDR_4)+analogRead(PIN_LDR_5));
        Serial.println("GAME:  START");

        timer_delay(3, DELAY_ROUND_START);
        while (timer_isActive(3) && gameMode == GAME_DUCK_DUCK_GOOSE);

        if (gameMode != GAME_DUCK_DUCK_GOOSE) return;
            
        voice.say(spSHOOT_GOOSE_NOT_DUCKS);
        while(voice.talking() && gameMode == GAME_DUCK_DUCK_GOOSE);
    
        while (gameMode == GAME_DUCK_DUCK_GOOSE)
        {            
            
            timer_delay(3, DELAY_ROUND_START);
            while (timer_isActive(3) && gameMode == GAME_DUCK_DUCK_GOOSE);
    
            flag_shotDuck = false;
            flag_shotGoose = false;
    
            // Generate random number of ducks
            rand_numberOfDucks = random(rand_min, rand_max);
    
            Serial.print("NUMBER OF DUCKS:  ");
            Serial.println(rand_numberOfDucks);
    
            leds_setColor(CRGB::Yellow, LED_BRIGHTNESS_LOW);
    
            
            for (duckNumber = 0; duckNumber < rand_numberOfDucks; ++duckNumber)
            {
                if (gameMode != GAME_DUCK_DUCK_GOOSE) return;
                
                Serial.print("DUCK:  ");
                Serial.println(duckNumber + 1);
                
                voice.say(spDUCK, false);
    
                timer_delay(0, delay_duck);
                while ((timer_isActive(0) || voice.talking()) && gameMode == GAME_DUCK_DUCK_GOOSE)
                {
                    if (isTargetHit())
                    {
                        Serial.println("YOU LOSE");
                        flag_shotDuck = true;

                        leds_blinkColor(CRGB::Red, LED_BRIGHTNESS_HIGH, LED_SLOW_BLINK_CYCLES, LED_SLOW_DELAY_TIME, GAME_DUCK_DUCK_GOOSE);
    
                        timer_delay(3, DELAY_MISTAKE);
                        while (timer_isActive(3) && gameMode == GAME_DUCK_DUCK_GOOSE);

                        if (gameMode != GAME_DUCK_DUCK_GOOSE) return;
                
                        voice.say(spGAME_OVER, false);

                        timer_delay(2, DELAY_ROUND_END);
                        while (timer_isActive(2) && gameMode == GAME_DUCK_DUCK_GOOSE);
            
                        return;
                    }
                }
    
            }
    
            if (gameMode != GAME_DUCK_DUCK_GOOSE) return;

            if (!flag_shotDuck)
            {
                Serial.println("GOOSE");
                
                voice.say(spGOOSE, false);
        
                leds_setColor(CRGB::Blue, LED_BRIGHTNESS_LOW);
        
                timer_delay(1, delay_goose);
                while ((timer_isActive(1) || voice.talking()) && gameMode == GAME_DUCK_DUCK_GOOSE)
                {
                    if (isTargetHit())
                    {
                        Serial.println("NEXT LEVEL");
                        flag_shotGoose = true;
        
                        leds_blinkColor(CRGB::Green, LED_BRIGHTNESS_HIGH, LED_FAST_BLINK_CYCLES, LED_FAST_DELAY_TIME, GAME_DUCK_DUCK_GOOSE);
                        break;
                    }
                }
            }

            if (gameMode != GAME_DUCK_DUCK_GOOSE) return;
            
            // BLOCK UNTIL SPEECH FINISHED IN CASE TARGET WINDOW IS SHORTER THAN SPEECH DURATION
            while(voice.talking() && gameMode == GAME_DUCK_DUCK_GOOSE);
    
            
            if (flag_shotGoose)
            {
                timer_delay(5, DELAY_SUCCESS);
                while (timer_isActive(5) && gameMode == GAME_DUCK_DUCK_GOOSE);
    
                if (gameMode != GAME_DUCK_DUCK_GOOSE) return;
                
                voice.say(spNEXT_LEVEL);
    
                delay_duck *= SPEEDUP_FACTOR;
                delay_goose *= SPEEDUP_FACTOR;
                rand_max += RAND_MAX_ADD_PER_ROUND;
                
            }

            else
            {
                // DID NOT SHOOT GOOSE
                leds_blinkColor(CRGB::Red, LED_BRIGHTNESS_HIGH, LED_SLOW_BLINK_CYCLES, LED_SLOW_DELAY_TIME, GAME_DUCK_DUCK_GOOSE);

                timer_delay(3, DELAY_MISTAKE);
                while (timer_isActive(3) && gameMode == GAME_DUCK_DUCK_GOOSE);

                if (gameMode != GAME_DUCK_DUCK_GOOSE) return;
                
                voice.say(spGAME_OVER, false);

                timer_delay(2, DELAY_ROUND_END);
                while (timer_isActive(2) && gameMode == GAME_DUCK_DUCK_GOOSE);
    
                return;
            }            
        }
    }
    
    return;
}
