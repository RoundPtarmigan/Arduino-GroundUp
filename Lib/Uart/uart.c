#define BAUD 115200
#define USE_2X
// Use setbaud.h (I understand what it's doing and agree)
#include <util/setbaud.h>
#include <avr/io.h>  // io regs
#include <inttypes.h>
#include <avr/interrupt.h>
#include <string.h>

#define MAX_SENT 40
#define REC_BUFF_LEN 40
uint8_t buffIdx = 0;
char recBuffer[REC_BUFF_LEN];

void config_uart(){
    UCSR0A = _BV(U2X0); // enable 2X mode
    UCSR0B = _BV(RXCIE0) | _BV(RXEN0) | _BV(TXEN0); // Interrupt for recieved on, recieve and Xfere enabled
    UCSR0C = _BV(UCSZ00) | _BV(UCSZ01); // 8 bit mode, no parity check
    UBRR0L = UBRR_VALUE; // use setbaud calculated rate
}

void sendCh(char a){
    while(!(UCSR0A & _BV(UDRE0))); // busy wait for empty buffer
    UDR0 = a; // send 8bit char
}

void sendLine(char* line){
    uint8_t charsSent = 0;
    while(line[charsSent] != '\0' && charsSent < MAX_SENT){
        sendCh(line[charsSent]);
        charsSent++;
    }
    sendCh('\r');
    sendCh('\n');
}

char getCh(){
    while(!(UCSR0A & _BV(RXC0))); // busy wait for receiver finish
    return UDR0; // access and return
}

void flushRecBuffer(){
    memset(recBuffer, 0, REC_BUFF_LEN);
}

ISR(USART_RX_vect, ISR_BLOCK)
{
    char ch = UDR0;

    if(buffIdx < REC_BUFF_LEN){
        recBuffer[buffIdx] = ch;
        buffIdx++;
    }
}