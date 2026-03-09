#ifndef IO_EXT
#define IO_EXT

#include <avr/io.h>
// Add support for address poiters


// Raw Volatile Pointers to IO Addresses for use in groupings
#define IO_ADDR(io_addr) (volatile uint8_t*)(io_addr + __SFR_OFFSET)
#define HW_ADDR(hw_addr) (volatile uint8_t*)(hw_addr)
#define _ADDR volatile uint8_t*
#define _ADDRW volatile uint16_t*

// Port B
#define PINB_ADDR IO_ADDR(0x3)
#define DDRB_ADDR IO_ADDR(0x4)
#define PORTB_ADDR IO_ADDR(0x5)
// Port C // PWM supported on 1,2,3
#define PINC_ADDR IO_ADDR(0x6)
#define DDRC_ADDR IO_ADDR(0x7)
#define PORTC_ADDR IO_ADDR(0x8)
// Port D // PWM supported on 3,5,6
#define PIND_ADDR IO_ADDR(0x9)
#define DDRD_ADDR IO_ADDR(0xA)
#define PORTD_ADDR IO_ADDR(0xB)

// Timer/Counter Cntrl // PORT D pin 5/6
#define TCCR0A_ADDR IO_ADDR(0x24) // compare modes and wgm modes
#define TCCR0B_ADDR IO_ADDR(0x25) // force comp, wgm, and clock source
#define TCNT0_ADDR IO_ADDR(0x26)  // counter
// PWM PORT D // 8 BIT
#define OCR0A_ADDR IO_ADDR(0x27)  // PORT D: PIN 6
#define OCR0B_ADDR IO_ADDR(0x28)  // PORT D: PIN 5
// Timer interrupts
#define TIMSK0_ADDR HW_ADDR(0x6E) // interrupt mask
#define TIFR0_ADDR IO_ADDR(0x15)  // interrupt flag

// PWM and Timers // PORT C // 16 BIT
#define TCCR1A_ADDR HW_ADDR(0x80)  // compare modes, wgm
#define TCCR1B_ADDR HW_ADDR(0x81)  // input capture noise, wgm, clock select
#define TCCR1C_ADDR HW_ADDR(0x82)  // force control
#define TCNT1L_ADDR HW_ADDR(0x84)
#define TCNT1H_ADDR HW_ADDR(0x85)
#define OCR1AL_ADDR HW_ADDR(0x88)  // PORT B: PIN x
#define OCR1AH_ADDR HW_ADDR(0x89)  // PORT B: PIN y
#define OCR1BL_ADDR HW_ADDR(0x8A)  // PORT B: PIN x
#define OCR1BH_ADDR HW_ADDR(0x8B)  // PORT B: PIN y
#define ICR1L_ADDR  HW_ADDR(0x86)
#define ICR1H_ADDR  HW_ADDR(0x87)
// Timer interrupts
#define TIMSK1_ADDR HW_ADDR(0x6F) // interrupt mask
#define TIFR1_ADDR IO_ADDR(0x16)  // interrupt flag


// Timer/Counter Cntrl // PORT D/C pin 5/6
#define TCCR2A_ADDR HW_ADDR(0xB0) // compare modes and wgm modes
#define TCCR2B_ADDR HW_ADDR(0xB1) // force comp, wgm, and clock source
#define TCNT2_ADDR HW_ADDR(0xB2)  // counter
// PWM and Timers // PORT D // 8 BIT
#define OCR2A_ADDR HW_ADDR(0xB3)  // PORT D: PIN 6
#define OCR2B_ADDR HW_ADDR(0xB4)  // PORT D: PIN 5
// Timer Interrupts
#define TIMSK2_ADDR HW_ADDR(0x70) // interrupt mask
#define TIFR2_ADDR IO_ADDR(0x17)  // interrupt flag
// Async
#define ASSR_ADDR HW_ADDR(0xB6)
#define GTCCR_ADDR IO_ADDR(0x23)
#endif