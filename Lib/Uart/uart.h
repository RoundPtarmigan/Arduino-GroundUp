#ifndef UART_H
#define UART_H
#include <inttypes.h>
void config_uart();

void writeUart(char* line);
uint8_t readUart(char* line);

#endif