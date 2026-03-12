#define __AVR_ATmega328P__
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <four7SD.h>

// simply make on-board led blink
int main(void){
    FourDigitDisp disp = config_four_7SD(simple_shift_reg(IO_PINB0, IO_PINB1, IO_PINB2),
                                    IO_PIND7, IO_PIND6, IO_PIND5, IO_PIND4);

    while(1){
        for(int i = 0; i<=9999; i++){
            set_digits_four_7SD(&disp, i);
            display_four_7SD(&disp);
        }
    }
}