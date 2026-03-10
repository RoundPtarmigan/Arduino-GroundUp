#include <four7SD.h>
#include <codes7SD.h>
#include <util/delay.h>  // TODO: update display refresh and remove

// TODO: Consider moving these into "codes" which should not be exposed anyway
#define NUM_DIGITS 11
#define ERR_DIGIT 10
#define MAX_DIGIT  9
#define MAX_NUMBER 9999

uint8_t digit[NUM_DIGITS] = {ZERO_7SD, ONE_7SD, TWO_7SD, THREE_7SD, FOUR_7SD,
                             FIVE_7SD, SIX_7SD, SEVEN_7SD, EIGHT_7SD, NINE_7SD, ERROR_7SD};
// end TODO


// initialize and return a struct representing a Four Digit 7-segment display
// Common cathode, set pins to HIGH = OFF
FourDigitDisp config_four_7SD(SimpleShiftReg shift, IoPin ioDigit0, IoPin ioDigit1, IoPin ioDigit2, IoPin ioDigit3){
    FourDigitDisp segD = {shift, 
                          {ioDigit0, ioDigit1, ioDigit2, ioDigit3},
                          {0,0,0,0}};

    // turn off all display segments
    for(uint8_t i = 0; i < 4; i++){
        config_io_pin(segD.digitPins[i], IO_OUT_HI);
    }
    return segD;
}

// set digits for 7SD
void set_digits_four_7SD(FourDigitDisp* disp, uint16_t number){
    // number cannot be represented
    if(number > MAX_NUMBER){
        for(uint8_t i = 0; i < 4; i++){
            disp->digits[i] = ERR_DIGIT;
        }
    }
    else{
        uint16_t divisor = 1000;
        // move down the 10s places, removing most significant digits along the way
        for(uint8_t i = 0; i < 4; i++){
            disp->digits[i] = number / divisor;
            number = number % divisor;
            divisor /= 10;
        }
    }
}

// simple display strobe
// TODO: This should include a way to keep track of time so it can be called in a loop without blocking (i.e. remove call to delay)
//       For current purposes, this will do
void display_four_7SD(FourDigitDisp* disp){
    uint8_t numStart = 0;
    for(uint8_t i = 0; i < 4; i++){
        numStart |= disp->digits[i];
        if(numStart){
            simple_shift_to_parallel(disp->shiftReg, disp->digits[i]);
            set_io_pin_low(disp->digitPins[i]);
            _delay_ms(20);
            set_io_pin_high(disp->digitPins[i]);
        }
    }
}