#ifndef EXT_INTERRUPTS
#define EXT_INTERRUPTS

#include <avr/io.h>
#include <ioPort.h>

// use base interface for External interrupts
typedef enum{
    INT_LOW  = 0,
    INT_CHNG,
    INT_FALL, 
    INT_RISE  
}IntMode;

// PINS D2 + D3
//
// EIFR ExtInt Flag Reg
// EICRA ExtInt Control
// EIMSK ExtInt Mask
void enable_ext_interrupt(IoPin pin, IntMode mode);
void disable_ext_interrupt(IoPin pin, IntMode mode);

// PCICR Interrupt Control
// PCMASK Interrupt PIN Mask
// PCIFR  Interrupt FLAG
void enable_pc_interrupt(IoPin pin);
void disable_pc_interrupt(IoPin pin);
void disable_pc_port(IoPortId port);

#endif