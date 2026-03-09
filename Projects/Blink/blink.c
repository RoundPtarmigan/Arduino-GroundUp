#define __AVR_ATmega328P__
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <ioPort.h>

// simply make on-board led blink
int main(void){
    config_io_pin(IO_PINB5, IO_OUT_LO);
    config_io_pin(IO_PINB4, IO_OUT_LO);
    while(1){
        toggle_io_pin(IO_PINB5);
        toggle_io_pin(IO_PINB4);
        _delay_ms(1000);
    }
}