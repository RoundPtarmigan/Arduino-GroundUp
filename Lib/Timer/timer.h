#ifndef TIMER_H
#define TIMER_H
#include <pwm.h>
void attach_timer_function(IoPin timerPin, void (*func)(void));
void config_timer(IoPin timerPin);
void set_timer_params(IoPin timerPin, uint16_t duty, ClkDivs clkDiv);
void disable_timer(IoPin timerPin);

#endif