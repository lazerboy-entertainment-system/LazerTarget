#define DELAY_GAME_START        2500
#define DELAY_READY             2000
#define DELAY_MAX_ROUND_WINDOW  9900
#define DELAY_ROUND_RESET       3000

void game_draw()
{
 
    while (gameMode == GAME_DRAW)
    {
        // BLOCKING DELAY FOR GAME TO START
        timer_delay(1, DELAY_GAME_START);
        while(timer_isActive(1) && gameMode == GAME_DRAW);

        if (gameMode != GAME_DRAW) return;
        voice.say(spREADY, false);
        
        leds_setColor(CRGB::Yellow, LED_BRIGHTNESS_LOW);        

        timer_delay(1, DELAY_READY);
        while((voice.talking() || timer_isActive(1)) && gameMode == GAME_DRAW);
        
        if (gameMode != GAME_DRAW) return;

        voice.say(spDRAW, false);
        
        leds_setColor(CRGB::Blue, LED_BRIGHTNESS_LOW);        
        
        timer_delay(5, DELAY_MAX_ROUND_WINDOW);
        while(timer_isActive(5) && gameMode == GAME_DRAW)
        {
            if (isTargetHit())
            {
                timer_stop(5);
                leds_blinkColor(CRGB::Green, LED_BRIGHTNESS_HIGH, LED_FAST_BLINK_CYCLES, LED_FAST_DELAY_TIME, GAME_DRAW);
                break;
            }
        }

        double seconds = (DELAY_MAX_ROUND_WINDOW - (timer_getCount(5) * TIMER_INTERVAL_MILLISECONDS)) / 1000.0;
       
        Serial.print("SECONDS SPENT:  ");
        Serial.println(seconds);


        if (gameMode != GAME_DRAW) return;

        if (timer_getCount(5) > 0)
        {
            for (uint8_t i = 0; i < 3; ++i)
            {
                if (gameMode != GAME_DRAW) return;
                switch ((uint8_t) seconds)
                {
                    case 0:
                        voice.say(spZERO);
                        break;
                    case 1:
                        voice.say(spONE);
                        break;
                    case 2:
                        voice.say(spTWO);
                        break;
                    case 3:
                        voice.say(spTHREE);
                        break;
                    case 4:
                        voice.say(spFOUR);
                        break;
                    case 5:
                        voice.say(spFIVE);
                        break;
                    case 6:
                        voice.say(spSIX);
                        break;
                    case 7:
                        voice.say(spSEVEN);
                        break;
                    case 8:
                        voice.say(spEIGHT);
                        break;
                    case 9:
                        voice.say(spNINE);
                        break;
                }
    
                if (i == 0)
                    voice.say(spPOINT);    
    
                seconds -= (uint8_t) seconds;
                seconds *= 10;
            }
            
            voice.say(spSECONDS);
        }
        else
        {
            leds_setColor(CRGB::Black, LED_BRIGHTNESS_HIGH);
            if (gameMode != GAME_DRAW) return;
            
            voice.say(spTOO_SLOW, false);
            leds_blinkColor(CRGB::Red, LED_BRIGHTNESS_HIGH, LED_SLOW_BLINK_CYCLES, LED_SLOW_DELAY_TIME, GAME_DRAW);
            
            while(voice.talking() && gameMode == GAME_DRAW);
 
        }   

        timer_delay(2, DELAY_ROUND_RESET);
        while(timer_isActive(2) && gameMode == GAME_DRAW);
      
    }

    return;
}
