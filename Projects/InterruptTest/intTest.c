#define __AVR_ATmega328P__
#define F_CPU 16000000UL
#include <util/atomic.h>
#include <avr/io.h>
#include <util/delay.h>
#include <extInterrupts.h>
#include <ioPort.h>

// handle interrupt to interpret button change level
// use atomic
// this will control an LED on board

volatile uint8_t ledflag0 = 0;
volatile uint8_t ledflag1 = 0;
ISR(INT0_vect){
    ledflag0 = 1;
}

ISR(INT1_vect){
    ledflag1 = 1;
}

ISR(PCINT1_vect){
    ledflag0 = 0;
    ledflag1 = 0;
}
int main(void){
    config_io_pin(IO_PINB5, IO_OUT_HI);
    config_io_pin(IO_PIND4, IO_OUT_HI);
    config_io_pin(IO_PIND5, IO_OUT_HI);
    config_io_pin(IO_PIND2, IO_OUT_HI);
    config_io_pin(IO_PIND3, IO_OUT_HI);

    config_io_pin(IO_PINC0, IO_OUT_HI);
    enable_pc_interrupt(IO_PINC0);


    enable_ext_interrupt(IO_PIND2, INT_CHNG);
    enable_ext_interrupt(IO_PIND3, INT_CHNG);

    uint8_t counter = 0;
    while(1){
        toggle_io_pin(IO_PINB5);
        //toggle_io_pin(IO_PIND4);
        //toggle_io_pin(IO_PIND5);
        ATOMIC_BLOCK(ATOMIC_FORCEON){
            if(ledflag0){
                set_io_pin_high(IO_PIND4);
            } else{
                set_io_pin_low(IO_PIND4);
            }
            if(ledflag1){
                set_io_pin_high(IO_PIND5);
            } else{
                set_io_pin_low(IO_PIND5);
            }
        }
        if(counter ==5){
            set_io_pin_high(IO_PIND2);
        }
        if(counter ==10){
            set_io_pin_high(IO_PIND3);
        }
        if(counter == 15){
            set_io_pin_high(IO_PINC0);
        }
        counter++;
        _delay_ms(500);
    }
}