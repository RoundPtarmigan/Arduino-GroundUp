#ifndef SHIFT_REG_H
#define SHIFT_REG_H
#include <ioPort.h>
typedef struct ShiftReg{
    IoPin masterReset;  // ACTIVE LOW
    IoPin shiftClk;
    IoPin storageClk;
    IoPin outputEnable; // ACTIVE LOW
    IoPin serialDataIn;
} ShiftReg;

typedef struct SimpleShiftReg{
    IoPin shiftClk;
    IoPin storageClk;
    IoPin serialDataIn;
} SimpleShiftReg;

ShiftReg shift_reg(IoPin masterReset, IoPin shiftClk, IoPin storageClk, IoPin outputEnable, IoPin serialDataIn);
SimpleShiftReg simple_shift_reg(IoPin shiftClk, IoPin storageClk, IoPin serialDataIn);
void reset_shiftReg(ShiftReg shift);
void shift_through(ShiftReg shift);
void xfer_to_storage(ShiftReg shift);

void shift_and_store(ShiftReg shift);

void enable_output(ShiftReg shift);
void disable_output(ShiftReg shift);

void shift_to_parallel_on(ShiftReg shift, uint8_t byte);
void simple_shift_to_parallel(SimpleShiftReg shift, uint8_t byte);

#endif