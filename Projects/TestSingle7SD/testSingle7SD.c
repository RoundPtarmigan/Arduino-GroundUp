#define __AVR_ATmega328P__
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <single7SD.h>

// simply make on-board led blink
int main(void){
    SegmentDigit segDig = config_single_7SD(simple_shift_reg(IO_PINB2, IO_PINB3, IO_PINB4));

    while(1){
        for(int i = 0; i<=10; i++){
            set_display_digit(&segDig, i);
            display_digit(&segDig);
            _delay_ms(1000);
        }
    }
}