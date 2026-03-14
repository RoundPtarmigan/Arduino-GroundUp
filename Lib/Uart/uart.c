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
    uint8_t dataReady;
    uint8_t (*pushCh)(struct UartCircularBuffer*, char ch);
    uint8_t (*readBuff)(struct UartCircularBuffer*, char* ch);
} UartCircularBuffer;

uint8_t buff_pushCh(UartCircularBuffer* buffer, char ch){
    if(((buffer->writeIdx + 1) % REC_BUFF_LEN) != buffer->readIdx){
        if(ch == '\r'){
            buffer->dataReady = 1;
        }
        buffer->recBuffer[buffer->writeIdx] = ch;
        buffer->writeIdx = (buffer->writeIdx+1) % REC_BUFF_LEN;
        return 1;
    }
    else{
        buffer->dataReady = 1;
        return 0; // buffer is full
    }
}

uint8_t buff_readLine(UartCircularBuffer* buffer, char* line){
    uint8_t lineIdx = 0;
    if(buffer->dataReady){
        // continue reading the remaining entries
        while(buffer->readIdx != buffer->writeIdx){
            line[lineIdx] = buffer->recBuffer[buffer->readIdx];
            buffer->readIdx = (buffer->readIdx + 1) % REC_BUFF_LEN;
            lineIdx++;
        }
       buffer->dataReady = 0;
    }
    return lineIdx; // chars read into line
}

UartCircularBuffer localBuffer = {{0}, 0, 0, 0, // POD 
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

// write to Uart if provided non-empty string
void writeUart(char* line){
    uint8_t charsSent = 0;
    while(line[charsSent] != '\r' && charsSent < MAX_SENT){
        sendCh(line[charsSent]);
        charsSent++;
    }
    if(charsSent > 0){
        sendCh('\r');
        sendCh('\n');
    }
}

uint8_t readUart(char* line){
    return localBuffer.readBuff(&localBuffer, line); // return bytes read
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