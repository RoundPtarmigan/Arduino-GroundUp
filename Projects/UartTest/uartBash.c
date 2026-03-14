#include "uart.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
int main(){
    config_uart();
    sei();
    char local[40];
    while(1){
        _delay_ms(1000);
        readUart(local);
        sendUart(local);
    }
}