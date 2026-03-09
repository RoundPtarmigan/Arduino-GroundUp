#include <codes7SD.h>
#include <single7SD.h>

#define NUM_DIGITS 11
#define ERR_DIGIT 10
#define MAX_DIGIT  9
uint8_t digit[NUM_DIGITS] = {ZERO_7SD, ONE_7SD, TWO_7SD, THREE_7SD, FOUR_7SD,
                             FIVE_7SD, SIX_7SD, SEVEN_7SD, EIGHT_7SD, NINE_7SD, ERROR_7SD};

SegmentDigit config_single_7SD(SimpleShiftReg shift){
    SegmentDigit segD = {shift, 0};
    return segD;
}

void set_display_digit(SegmentDigit* SegmentDigit, uint8_t digit){
    if(digit > MAX_DIGIT){
        SegmentDigit->number = ERR_DIGIT;
    }
    else{
        SegmentDigit->number = digit;
    }
}

void display_digit(SegmentDigit* segmentInfo){
    simple_shift_to_parallel(segmentInfo->shiftReg, digit[segmentInfo->number]);
}