

// INTERRUPT SERVICE ROUTINE FOR TIMER1
ISR(TIMER0_COMPA_vect)
{
    // After the switch button is pressed, the debounce flag will be enabled
    // The debounce timer will be disabled when its count reaches to zero
    
    if (timer_buttonDebounce.flag_isEnabled) 
    {
        if (timer_buttonDebounce.count <= 0) 
        {
                timer_buttonDebounce.count = BUTTON_DEBOUNCE_COUNT;
                timer_buttonDebounce.flag_isEnabled = 0;
                flag_isButtonEnabled = true;
        }
        else
          --timer_buttonDebounce.count;
    }


    // ISR IMPLEMENTATION FOR GENERAL PURPOSE TIMERS
    for (gpTimerIndex = 0; gpTimerIndex < NUMBER_OF_GP_TIMERS; ++gpTimerIndex)
    {
        if (timer_gpArray[gpTimerIndex].flag_isEnabled)
        {
            if (timer_gpArray[gpTimerIndex].count <= 0) 
            {
                timer_gpArray[gpTimerIndex].flag_isEnabled = 0;
                timer_gpArray[gpTimerIndex].flag_doEvent = 1;
            }
            else
                --timer_gpArray[gpTimerIndex].count;
        }
    }
}    


// ====================================================================================================== 


// GENERAL PURPOSE TIMER FUNCTIONS:


// NON-BLOCKING TIMER DELAY
// NOTE: FOR A BLOCKING DELAY, TRY:  while(timer_isActive(timerNumber)); 
void timer_delay(uint8_t timerNumber, uint32_t milliseconds) 
{
    // resets the timer, then sets count to (milliseconds / TIMER_INTERVAL_MILLISECONDS), then starts the timer 
    timer_gpArray[timerNumber].flag_isEnabled = 0;
    timer_gpArray[timerNumber].flag_doEvent = 0;
    timer_gpArray[timerNumber].count = (uint32_t) milliseconds / TIMER_INTERVAL_MILLISECONDS;
    timer_gpArray[timerNumber].flag_isEnabled = 1;
}


// sets enabled flag for gp timer
void timer_start(uint8_t timerNumber) 
{
    timer_gpArray[timerNumber].flag_isEnabled = 1;
}


// clears enabled flag for gp timer
void timer_stop(uint8_t timerNumber) 
{
    timer_gpArray[timerNumber].flag_isEnabled = 0;
}


// sets count
void timer_setCount(uint8_t timerNumber, uint32_t count) 
{
    timer_gpArray[timerNumber].count = count;
}


// gets count
uint32_t timer_getCount(uint8_t timerNumber) 
{
    return timer_gpArray[timerNumber].count;
}


// sets doEvent flag
void timer_setDoEvent(uint8_t timerNumber) 
{
    timer_gpArray[timerNumber].flag_doEvent = 1;
}


// clears doEvent flag
void timer_clearDoEvent(uint8_t timerNumber) 
{
    timer_gpArray[timerNumber].flag_doEvent = 0;
}


// returns true if timer is enabled and greater than 0
bool timer_isActive(uint8_t timerNumber) 
{
    if (timer_gpArray[timerNumber].flag_isEnabled && timer_gpArray[timerNumber].count > 0)
        return true;
    else return false;
}


// RESETS TIMER
void timer_reset(uint8_t timerNumber) 
{
    // resets all record fields to zero for gp timer
    timer_gpArray[timerNumber].flag_isEnabled = 0;
    timer_gpArray[timerNumber].flag_doEvent = 0;
    timer_gpArray[timerNumber].count = 0;
}
