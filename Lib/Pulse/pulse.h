#ifndef PULSE_H
#define PULSE_H
#include <inttypes.h>
#include "pwm.h"
#include "timer.h"

typedef struct Pulse{
    uint16_t totalTicks;
    uint16_t activeTicks;
    ClkDivs clockDiv;
}Pulse;

Pulse make_pulse(double totalTime_ms, double activeTime_ms, ClkDivs clkDiv);

#define NUM_PHASES 2
typedef struct PulseHandler{
    Pulse pulse;
    uint16_t phaseTimes[NUM_PHASES];
    uint8_t  phaseIdx;
    IoPin    timerPin;
    IoPin    pulsePin;
    flexAddr ocrAddr;
    flexAddr timeAddr;
    void (*timerFunc)(void);
    void (*handler)(struct PulseHandler*);
    void (*init)(struct PulseHandler*, Pulse, IoPin timer, IoPin pulse, void(*timerFunc)(void));
    void (*startPulse)(struct PulseHandler*);
}PulseHandler;

void start_pulse(PulseHandler* handler);
void handle_interrupt8(PulseHandler *handler);
void handle_interrupt16(PulseHandler *handler);
void adjustPulse(Pulse* pulse, uint16_t max);
void init_pulse_handler(PulseHandler* handler, Pulse pulse, IoPin timerPin, IoPin pulsePin, void(*timerFunc)(void));

#define EMPTY_PULSE {0, 0, CLK_STOP}
#define PULSE_HANDLER(name) PulseHandler name = {EMPTY_PULSE, {0,0}, 0, IO_PIN_NONE, IO_PIN_NONE, {0}, {0}, 0, 0, init_pulse_handler, start_pulse}

#endif