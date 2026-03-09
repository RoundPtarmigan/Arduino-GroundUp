#ifndef IO_PORT_H
#define IO_PORT_H
#include <avr/io.h>
#include <ioExtend.h>

typedef enum{
    IO_PIN_NONE = -1,
    IO_PINB0 = 0,
    IO_PINB1,
    IO_PINB2,
    IO_PINB3,
    IO_PINB4,
    IO_PINB5,
    IO_PINB6,
    IO_PINB7,
    IO_PINC0,
    IO_PINC1,
    IO_PINC2,
    IO_PINC3,
    IO_PINC4,
    IO_PINC5,
    IO_PINC6,
    // NO PIN C7
    IO_PIND0 = IO_PINC6 + 2,
    IO_PIND1,
    IO_PIND2,
    IO_PIND3,
    IO_PIND4,
    IO_PIND5,
    IO_PIND6,
    IO_PIND7,
}IoPin;

typedef enum{
    PORTID_B = 0,
    PORTID_C,
    PORTID_D,
    NUM_IO_PORTS,
}IoPortId;

typedef enum{
    IO_IN_PULL = 0,
    IO_IN_NO_PULL,
    IO_OUT_LO,
    IO_OUT_HI,
}IoMode;


// struct grouping port pins together
typedef struct IoPort{
    _ADDR pin;
    _ADDR dataDir;
    _ADDR port;
} IoPort;

IoPortId port_for_pin(IoPin pin);
// returns bits dedicated for pin selection
uint8_t shift_for_pin(IoPin pin);
// IO_PIN{label}{num}
void config_io_pin(IoPin pin, IoMode mode);
// IO_PIN{label}{num}
void set_io_pin_high(IoPin pin);
// IO_PIN{label}{num}
void set_io_pin_low(IoPin pin);
// IO_PIN{label}{num}
void toggle_io_pin(IoPin pin);
// return hi or lo
uint8_t read_io_pin(IoPin pin);

#endif