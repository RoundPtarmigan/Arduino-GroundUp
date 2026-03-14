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

typedef struct UartCircularBuffer{
    char recBuffer[REC_BUFF_LEN];
    uint8_t readIdx;
    uint8_t writeIdx;
    void (*pushCh)(struct UartCircularBuffer*, char ch);
    void (*readBuff)(struct UartCircularBuffer*, char* ch);
} UartCircularBuffer;

void buff_pushCh(UartCircularBuffer* buffer, char ch){
    if(((buffer->writeIdx + 1) % REC_BUFF_LEN) != buffer->readIdx){
        buffer->recBuffer[buffer->writeIdx] = ch;
        buffer->writeIdx++;
    }
    else{
        // buffer is full
    }
}

void buff_readLine(UartCircularBuffer* buffer, char* line){
    uint8_t lineIdx = 0;
    while(buffer->readIdx != buffer->writeIdx){
        line[lineIdx] = buffer->recBuffer[buffer->readIdx];
        buffer->readIdx = (buffer->readIdx + 1) % REC_BUFF_LEN;
        lineIdx++;
    }
}

UartCircularBuffer localBuffer = {{0}, 0, 0, // POD 
                                   buff_pushCh, buff_readLine}; // function pointers

void config_uart(){
    UCSR0A = _BV(U2X0); // enable 2X mode
    UCSR0B = _BV(RXCIE0) | _BV(RXEN0) | _BV(TXEN0); // Interrupt for received on, receive and Xfer enabled
    UCSR0C = _BV(UCSZ00) | _BV(UCSZ01); // 8 bit mode, no parity check
    UBRR0L = UBRR_VALUE; // use setbaud calculated rate
}

void sendCh(char a){
    while(!(UCSR0A & _BV(UDRE0))); // busy wait for empty buffer
    UDR0 = a; // send 8bit char
}

void writeUart(char* line){
    uint8_t charsSent = 0;
    while(line[charsSent] != '\0' && charsSent < MAX_SENT){
        sendCh(line[charsSent]);
        charsSent++;
    }
    sendCh('\r');
    sendCh('\n');
}

void readUart(char* line){
    localBuffer.readBuff(&localBuffer, line);
}

char getCh(){
    while(!(UCSR0A & _BV(RXC0))); // busy wait for receiver finish
    return UDR0; // access and return
}

ISR(USART_RX_vect, ISR_BLOCK)
{
    char ch = UDR0;
    localBuffer.pushCh(&localBuffer, ch);
}