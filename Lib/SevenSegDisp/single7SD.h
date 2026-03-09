#ifndef SINGLE_7SD_H
#define SINGLE_7SD_H
#include <shiftReg.h>

typedef struct SegmentDigit{
    SimpleShiftReg shiftReg;
    uint8_t  number;
} SegmentDigit;

SegmentDigit config_single_7SD(SimpleShiftReg shift);
void set_display_digit(SegmentDigit* SegmentDigit, uint8_t digit);
void display_digit(SegmentDigit* segmentInfo);

#endif