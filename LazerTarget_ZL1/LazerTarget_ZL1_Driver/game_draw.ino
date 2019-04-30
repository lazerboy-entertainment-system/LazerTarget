void game_draw()
{
    const uint32_t MAX_MILLISECONDS = 9900;
  
    while (gameMode == GAME_DRAW)
    {
        timer_delay(1, 3000);
        while(timer_isActive(1) && gameMode == GAME_DRAW);

        if (gameMode != GAME_DRAW) return;
        
        voice.say(spREADY);
        timer_delay(1, 3000);
        while(timer_isActive(1) && gameMode == GAME_DRAW);
        
        voice.say(spFIRE, false);
        
        leds_setColor(CRGB::Blue, LED_BRIGHTNESS_LOW);        
        
        timer_delay(5, MAX_MILLISECONDS);
        while(timer_isActive(5) && gameMode == GAME_DRAW)
        {
            if (isTargetHit())
            {
                timer_stop(5);
                leds_blinkColor(CRGB::Green, LED_BRIGHTNESS_HIGH, LED_FAST_BLINK_CYCLES, LED_FAST_DELAY_TIME, GAME_DRAW);
                break;
            }
        }

        double seconds = (MAX_MILLISECONDS - (timer_getCount(5) * TIMER_INTERVAL_MILLISECONDS)) / 1000.0;
       
        Serial.print("SECONDS SPENT:  ");
        Serial.println(seconds);


        if (gameMode != GAME_DRAW) return;

        if (timer_getCount(5) > 0)
        {
            for (uint8_t i = 0; i < 3; ++i)
            {
                if (gameMode != GAME_DRAW) return;
                switch ((int) seconds)
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
    
                seconds -= (int) seconds;
                seconds *= 10;
            }
            
            voice.say(spSECONDS);
        }
        else
        {
            leds_setColor(CRGB::Black, LED_BRIGHTNESS_HIGH);
            if (gameMode != GAME_DRAW) return;
            voice.say(spZERO);    
        }   

      
    }

    return;
}
