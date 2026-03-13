#ifndef CLOCKS_H
#define CLOCKS_H
#include <timer.h>

typedef struct CircularCompClock{
    TimerId  timer;
    uint16_t currCount; 
    uint16_t watchCount;
} CircularCompClock;

CircularCompClock config_circular_comp_clock(TimerId timer, ClkDivs clkDiv);
void set_circular_comp_clock(CircularCompClock* clock, uint16_t counts);
uint8_t wait_circular_comp_clock(CircularCompClock* clock);

#endif