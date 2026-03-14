#include "uart.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

int main(){
    config_uart();
    sei();
    char local[40];
    memset((void*)local, 0, 40*sizeof(char));
    while(1){
        if(readUart(local)){
            writeUart(local);
            memset((void*)local, 0, 40*sizeof(char));
        }
    }
}
