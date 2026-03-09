#define __AVR_ATmega328P__
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "ioPort.h"

// handle interrupt to interpret button change level
// use atomic
// this will control an LED on board
int main(void){

    config_io_pin(IO_PINB5, IO_OUT_LO);
    config_io_pin(IO_PIND2, IO_IN_PULL);
    while(1){
        if(read_io_pin(IO_PIND2)){
            config_io_pin(IO_PINB5, IO_OUT_LO);
        } else if(!read_io_pin(IO_PIND2)){
            config_io_pin(IO_PINB5, IO_OUT_HI);
        }
    }
}