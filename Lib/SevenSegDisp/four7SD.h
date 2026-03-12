#ifndef FOUR_7SD_H
#define FOUR_7SD_H
#include <shiftReg.h>

typedef struct FourDigitDisp{
    SimpleShiftReg shiftReg;
    IoPin   digitPins[4];  // Most Significant Digit at 0
    uint8_t digits[4];     // Most Significant Digit at 0
} FourDigitDisp;

// initialize and return a struct representing a Four Digit 7-segment display
FourDigitDisp config_four_7SD(SimpleShiftReg shift, IoPin ioDigit0, IoPin ioDigit1, IoPin ioDigit2, IoPin ioDigit3);

// set digits for 7SD
void set_digits_four_7SD(FourDigitDisp* disp, uint16_t number);

// display function using "delay"
void display_four_7SD(FourDigitDisp* disp);

#endif