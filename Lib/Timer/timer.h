#ifndef TIMER_H
#define TIMER_H
#include <pwm.h>
typedef enum {
    TIMER_INVALID = -1,
    TIMER0A = 0,
    TIMER0B,
    TIMER1A,
    TIMER1B,
    TIMER2A,
    TIMER2B,
    NUM_TIMERS
} TimerId;


void attach_timer_function(IoPin timerPin, void (*func)(void));
void config_timer(IoPin timerPin);
void set_timer_params(IoPin timerPin, uint16_t duty, ClkDivs clkDiv);
void disable_timer(IoPin timerPin);
void configure_basic_timer(TimerId timer, ClkDivs clkDiv);
uint16_t get_curr_time(TimerId timer);
uint16_t add_times_and_wrap(TimerId timer, uint16_t base, uint16_t add);

#endif