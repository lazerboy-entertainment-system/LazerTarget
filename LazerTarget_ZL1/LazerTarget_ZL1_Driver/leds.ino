//void leds_blinkColor(CRGB color, uint8_t brightness, uint8_t numCycles, uint32_t delayTime, uint8_t arg_gameMode)
//{
//  
//    FastLED.setBrightness(brightness);
//    
//    ledIndex = 0;
//    while (++ledIndex <= numCycles && gameMode == arg_gameMode)
//    {
//        leds[0] = color;
//        leds[1] = color;
//        leds[2] = color;
//        leds[3] = color;
//        FastLED.show();
//        
//        timer_delay(LED_GP_TIMER_NUMBER, delayTime);
//        while (timer_isActive(LED_GP_TIMER_NUMBER));
//        
//        leds[0] = CRGB::Black;
//        leds[1] = CRGB::Black;
//        leds[2] = CRGB::Black;
//        leds[3] = CRGB::Black;
//        FastLED.show();
//
//        timer_delay(LED_GP_TIMER_NUMBER, delayTime);
//        while (timer_isActive(LED_GP_TIMER_NUMBER)); 
//}
