#define __AVR_ATmega328P__
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <ioPort.h>
#include "pwm.h"
#include <avr/interrupt.h>
#include "timer.h"


IoPin togglePin = IO_PINB4;
void timerFunc(void){
    toggle_io_pin(togglePin);
}
// simply make on-board led blink
int main(void){
    IoPin timerPin = IO_PINB1;
    config_io_pin(IO_PINB5, IO_OUT_LO);
    config_io_pin(togglePin, IO_OUT_LO);
    config_io_pin(timerPin, IO_OUT_HI);
    attach_timer_function(timerPin, timerFunc);
    config_timer(timerPin);
    set_timer_params(timerPin, 78, CLK_DIV_256);
    sei();
    enable_pwm_int(timerPin);
    while(1){
        
    }
}