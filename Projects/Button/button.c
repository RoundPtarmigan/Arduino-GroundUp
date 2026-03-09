#define __AVR_ATmega328P__
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "ioPort.h"

// handle interrupt to interpret button change level
// use atomic
// this will control an LED on board
int main(void){

    config_io_pin(IO_PIND5, IO_OUT_LO);
    config_io_pin(IO_PINB0, IO_IN_PULL);
    config_io_pin(IO_PINB1, IO_IN_PULL);
    while(1){
        if(!read_io_pin(IO_PINB0)){
            _delay_ms(100);
            if(!read_io_pin(IO_PINB0)){
                toggle_io_pin(IO_PIND5);
            }
            while(!read_io_pin(IO_PINB0));
            _delay_ms(50);
        }
        if(!read_io_pin(IO_PINB1)){
            set_io_pin_high(IO_PIND5);
        }
    }
}