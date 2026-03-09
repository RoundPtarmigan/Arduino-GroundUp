#define __AVR_ATmega328P__
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "ioPort.h"
#include "pulse.h"
#include <util/atomic.h>

// handle interrupt to interpret button change level
// use atomic
// this will control an LED on board
PULSE_HANDLER(pulse_handler);
void timerFunc(void){
    pulse_handler.handler(&pulse_handler);
}

int main(void){
    IoPin timerPin = IO_PINB1;
    IoPin pulsePin = IO_PINB4;
    double ms = 1.5;
    Pulse pulse = make_pulse(20, ms, CLK_DIV_8);
    pulse_handler.init(&pulse_handler, pulse, timerPin, pulsePin, timerFunc);
    pulse_handler.phaseTimes[0] = .5;
    pulse_handler.startPulse(&pulse_handler);
    _delay_ms(500);
    sei();
    while(1){
        if(ms < 2.5){
            ms = ms + .1;
        }
        _delay_ms(1000);
    }
}