#include <clocks.h>

// config timer and make Clock struct
CircularCompClock config_circular_comp_clock(TimerId timer, ClkDivs clkDiv){
    configure_basic_timer(timer, clkDiv);
    CircularCompClock clock = {timer, 0, 0};
    return clock;
}

// set the current count from timer and the watchCount to be waited on by "wait" fun
void set_circular_comp_clock(CircularCompClock* clock, uint16_t counts){
    clock->currCount = get_curr_time(clock->timer);
    clock->watchCount = add_times_and_wrap(clock->timer, clock->currCount, counts);
}

// wait function for a clock that wraps
// returns true if we have passed the watchpoint time
// returns falls if we have not
//
// Limitiations: must be called within one timer cycle
// can fail if timer clock div is very small on uint8_t precision timers
// can fail if long timing requirements are required      
uint8_t wait_circular_comp_clock(CircularCompClock* clock){
    if(clock->watchCount==clock->currCount){
        return 1;
    }
    // if watch point is before wraparound, we must look for wraparound
    else if(clock->watchCount > clock->currCount){
        uint16_t time = get_curr_time(clock->timer);
        if((time > clock->watchCount) || (time < clock->currCount)){ // either we're above watch point or we wrapped
            return 1;
        }
        else{
            return 0;
        }
    }
    // if watch point is AFTER wraparound, we just wait to pass it
    else{ // clock->watchCount < clock->currCount
        uint16_t time = get_curr_time(clock->timer);
        if(time > clock->watchCount){
            return 1;
        }
        else{
            return 0;
        }
    }
}