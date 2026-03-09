#include <ioPort.h>

#define NUM_PORT_PINS 8
#define NUM_PIN_BITS 3
#define PIN_BIT_MASK  0b111

// default constant structs
#define IO_PORTB {PINB_ADDR, DDRB_ADDR, PORTB_ADDR}
#define IO_PORTC {PINC_ADDR, DDRC_ADDR, PORTC_ADDR}
#define IO_PORTD {PIND_ADDR, DDRD_ADDR, PORTD_ADDR}
const volatile IoPort IO_PORTS[NUM_IO_PORTS] = {IO_PORTB, IO_PORTC, IO_PORTD}; // Only 3 IO_PORT structs

// return port associated with pin
IoPortId port_for_pin(IoPin pin){
    return (IoPortId)(pin >> NUM_PIN_BITS); // get port bits
}
// returns bits dedicated for pin selection
uint8_t shift_for_pin(IoPin pin){
    return (pin & PIN_BIT_MASK); // get pin bits
}

// IO_PIN{label}{num}
void config_io_pin(IoPin pin, IoMode mode){
    IoPortId portNum = port_for_pin(pin);
    uint8_t shift = shift_for_pin(pin);
    // port[i]: 0-> output low / input pullup off
    //        : 1-> output high/ input pullup on
    // datadir[i]: 0-> in | 1-> out
    switch(mode){
        case IO_IN_NO_PULL:
            *(IO_PORTS[portNum].port) &= ~(1<<shift);
            *(IO_PORTS[portNum].dataDir) &= ~(1<<shift);
            break;
        case IO_IN_PULL:
            *(IO_PORTS[portNum].port) |= (1<<shift);
            *(IO_PORTS[portNum].dataDir) &= ~(1<<shift);
            break;
        case IO_OUT_LO:
            *(IO_PORTS[portNum].port) &= ~(1<<shift);
            *(IO_PORTS[portNum].dataDir) |= (1<<shift);
            break;
        case IO_OUT_HI:
            *(IO_PORTS[portNum].port) |= (1<<shift);
            *(IO_PORTS[portNum].dataDir) |= (1<<shift);
            break;
        default:
            break; // err
    }
}

// IO_PIN{label}{num}
void set_io_pin_high(IoPin pin){
    IoPortId port = port_for_pin(pin);
    uint8_t shift = shift_for_pin(pin);

    *(IO_PORTS[port].port) |= (1<<shift);
}

// IO_PIN{label}{num}
void set_io_pin_low(IoPin pin){
    IoPortId port = port_for_pin(pin);
    uint8_t shift = shift_for_pin(pin);

    *(IO_PORTS[port].port) &= ~(1<<shift);
}

// IO_PIN{label}{num}
void toggle_io_pin(IoPin pin){
    IoPortId port = port_for_pin(pin);
    uint8_t shift = shift_for_pin(pin);

    *(IO_PORTS[port].pin) = (1<<shift);
}

uint8_t read_io_pin(IoPin pin){
    IoPortId port = port_for_pin(pin);
    uint8_t shift = shift_for_pin(pin);

    uint8_t status;

    status = ((*(IO_PORTS[port].pin)) & (1 << shift));
    return status;
}
