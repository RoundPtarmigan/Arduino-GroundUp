#ifndef UART_H
#define UART_H

void config_uart();
void sendCh(char a);

void sendLine(char* line);

char getCh();

void flushRecBuffer();

#endif