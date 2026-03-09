#include <inttypes.h>
#include "pwm.h"
#include "timer.h"
#include <pulse.h>
#ifndef F_CPU
#define F_CPU 16000000
#endif

#define PULSE_MIN_CLKS 256

Pulse make_pulse(double totalTime_ms, double activeTime_ms, ClkDivs clkDiv){
    Pulse pulse = {0, 0, CLK_STOP};
    if(mapClkDivToVal[clkDiv]!=0){
        double msPerTick = (1/(double)F_CPU)*mapClkDivToVal[clkDiv]*1000;
        pulse.clockDiv    = clkDiv;
        pulse.totalTicks  = (uint16_t)(totalTime_ms/msPerTick);
        pulse.activeTicks = (uint16_t)(activeTime_ms/msPerTick);
    }
    uint16_t minTicks = PULSE_MIN_CLKS/mapClkDivToVal[clkDiv] + 2;
    if(pulse.activeTicks < minTicks){
        pulse.activeTicks = minTicks;
    }
    if(pulse.totalTicks < minTicks){
        pulse.totalTicks = minTicks;
    }
    return pulse;
}


void start_pulse(PulseHandler* handler){
    config_io_pin(handler->pulsePin, IO_OUT_LO);
    clear_pwm_counter(handler->timerPin);
    config_timer(handler->timerPin);
    attach_timer_function(handler->timerPin, handler->timerFunc);
    set_timer_params(handler->timerPin, handler->pulse.totalTicks, handler->pulse.clockDiv);
}

void handle_interrupt8(PulseHandler *handler){
    if(handler->phaseIdx == 0){
        set_io_pin_low(handler->pulsePin);
        *(handler->timeAddr.asByte) = (uint8_t)handler->phaseTimes[0];
        *(handler->ocrAddr.asByte) = (uint8_t)handler->phaseTimes[1];
        handler->phaseIdx = 1;
    }
    else if(handler->phaseIdx == 1){
        *(handler->timeAddr.asByte) = 0;
        *(handler->ocrAddr.asByte) = (uint8_t)handler->phaseTimes[0];
        handler->phaseIdx = 0;
        set_io_pin_high(handler->pulsePin);
    }
}

void handle_interrupt16(PulseHandler *handler){
    if(handler->phaseIdx == 0){
        set_io_pin_low(handler->pulsePin);
        *(handler->timeAddr.asWord) = handler->phaseTimes[0];
        *(handler->ocrAddr.asWord) = handler->phaseTimes[1];
        handler->phaseIdx = 1;
    }
    else if(handler->phaseIdx == 1){
        *(handler->ocrAddr.asWord) = handler->phaseTimes[0];
        handler->phaseIdx = 0;
        set_io_pin_high(handler->pulsePin);
        *(handler->timeAddr.asWord) = 0;
    }
}

void adjustPulse(Pulse* pulse, uint16_t max){
    // nonsense, don't run the timer
    if(pulse->totalTicks == 0 || (pulse->totalTicks < pulse->activeTicks)){
        pulse->clockDiv = CLK_STOP;
    }
    // adjust to chosen max
    if(pulse->totalTicks >= max){
        pulse->totalTicks = max;
    }
    if(pulse->activeTicks >= max){
        pulse->activeTicks = max;
    }
    // if active and total ticks are the same, adjust the window
    if(pulse->activeTicks == pulse->totalTicks && pulse->totalTicks!= max){
        pulse->totalTicks++;
    }
    else{
        pulse->activeTicks--;
    }
}

void init_pulse_handler(PulseHandler* handler, Pulse pulse, IoPin timerPin, IoPin pulsePin, void(*timerFunc)(void)){
    PwmPort port = pin_to_pwm_port(timerPin);
    switch(port){
        case PWM_PORT_D:
        case PWM_PORT_X:
            handler->handler = handle_interrupt8;
            adjustPulse(&pulse, UINT8_MAX);
            break;
        case PWM_PORT_B:
            handler->handler = handle_interrupt16;
            adjustPulse(&pulse, UINT16_MAX);
            break;
        default:
            break;
    }
    handler->pulse = pulse;
    handler->phaseTimes[0] = handler->pulse.activeTicks;
    handler->phaseTimes[1] = handler->pulse.totalTicks;
    handler->phaseIdx = 0;
    handler->timerPin = timerPin;
    handler->pulsePin = pulsePin;
    handler->ocrAddr = get_comp_reg(port, pin_to_pwm_reg(timerPin));
    handler->timeAddr = get_time_reg(port);
    handler->timerFunc = timerFunc;    
}