#include "uart.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
int main(){
    config_uart();
    sei();
    uint8_t toggle = 0;
    while(1){
        _delay_ms(1000);
        //sendLine(recBuffer);
    }
}