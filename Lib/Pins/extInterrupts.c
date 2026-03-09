#include <extInterrupts.h>
#include <avr/io.h>
#include <ioPort.h>

#define INT_MASK 0b11
// D2 is INT0
// D3 is INT1


// PINS D2 + D3
//
// EIFR ExtInt Flag Reg
// EICRA ExtInt Control
// EIMSK ExtInt Mask
void enable_ext_interrupt(IoPin pin, IntMode mode){
    switch(pin){
        case IO_PIND2:
            EIFR |= 1<<INT0; // clear flags
            EICRA &= ~(INT_MASK << ISC00); // clear last setting
            EICRA |= mode << ISC00;
            EIMSK |= 1 << INT0; // enable interrupt
            break;
        case IO_PIND3:
            EIFR |= 1<<INT1; // clear flags
            EICRA &= ~(INT_MASK << ISC10); // clear last setting
            EICRA |= mode << ISC10;
            EIMSK |= 1 << INT1;  // enable interrupt
            break;
        default:
            break;
    }
}

void disable_ext_interrupt(IoPin pin, IntMode mode){
    switch(pin){
        case IO_PIND2:
            EIMSK &= ~(1 << INT0);
            break;
        case IO_PIND3:
            EIMSK &= ~(1 << INT1);
            break;
        default:
            break;        
    }
}

// PC = PortChange interrupts
// PCICR Interrupt Control
// PCMASK Interrupt PIN Mask
// PCIFR  Interrupt FLAG
void enable_pc_interrupt(IoPin pin){
    // maybe check input?
    IoPortId port = port_for_pin(pin);
    uint8_t shift = shift_for_pin(pin);
    
    switch(port){
        case PORTID_B:
            PCMSK0 |= 1 << shift; break;
        case PORTID_C:
            PCMSK1 |= 1 << shift; break;
        case PORTID_D:
            PCMSK2 |= 1 << shift; break;
        default: break;
            
    }
    if((PCICR & (1 << port)) == 0){
        PCIFR |= 1 << port; // clear flag if we're toggling port on
    }
    PCICR |= 1 << port; // enable interrupts on port
}

void disable_pc_interrupt(IoPin pin){
    IoPortId port = port_for_pin(pin);
    uint8_t shift = shift_for_pin(pin);
    
    switch(port){
        case PORTID_B:
            PCMSK0 &= ~(1 << shift); break;
        case PORTID_C:
            PCMSK1 &= ~(1 << shift); break;
        case PORTID_D:
            PCMSK2 &= ~(1 << shift); break;
        default: break;            
    }
}

void disable_pc_port(IoPortId port){
    PCICR &= ~(1 << port); // disable pc interrupts on port
}
