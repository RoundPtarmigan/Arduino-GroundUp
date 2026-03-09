#define __AVR_ATmega328P__
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <ioPort.h>
#include <shiftReg.h>

// simply make on-board led blink
int main(void){
    ShiftReg shiftReg = shift_reg(IO_PINB0, IO_PINB1, IO_PINB2, IO_PINB3, IO_PINB4);
    reset_shiftReg(shiftReg);
    while(1){
        for(int i = 0; i< 8; i++){
            shift_to_parallel_on(shiftReg, 1<<i);
            _delay_ms(500);
        }
    }
    //for(uint8_t i = 0; i < 8; i++){
     //   uint8_t cntrlByte = 1 << i;
      //  shift_to_parallel_on(shiftReg, cntrlByte);
       // _delay_ms(500);
    //}
    //while(1);
}