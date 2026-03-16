#define __AVR_ATmega328P__
#define F_CPU 16000000UL
#include <avr/io.h>
#include <clocks.h>
#include <uart.h>
#include <util/delay.h>
// simply make on-board led blink
int main(void){
    config_uart();
    CircularCompClock clock = config_circular_comp_clock(TIMER1A, CLK_DIV_1024);
    uint16_t oneSec = F_CPU / 1024;
    char* word = "hello it's me\0";
    
    while(1){
        if(wait_circular_comp_clock(&clock)){
            set_circular_comp_clock(&clock, oneSec);
            writeUart(word);
        }
    }
}