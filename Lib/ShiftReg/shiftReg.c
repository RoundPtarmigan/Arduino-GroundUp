#include <shiftReg.h>

ShiftReg shift_reg(IoPin masterReset, IoPin shiftClk, IoPin storageClk, IoPin outputEnable, IoPin serialDataIn){
    ShiftReg created = {masterReset, shiftClk, storageClk, outputEnable, serialDataIn};
    config_io_pin(masterReset, IO_OUT_LO);
    config_io_pin(shiftClk, IO_OUT_LO);
    config_io_pin(storageClk, IO_OUT_LO);
    config_io_pin(outputEnable, IO_OUT_HI);
    config_io_pin(serialDataIn, IO_OUT_LO);
    return created;
}

SimpleShiftReg simple_shift_reg(IoPin shiftClk, IoPin storageClk, IoPin serialDataIn){
    SimpleShiftReg simple = {shiftClk, storageClk, serialDataIn};
    config_io_pin(shiftClk, IO_OUT_LO);
    config_io_pin(storageClk, IO_OUT_LO);
    config_io_pin(serialDataIn, IO_OUT_LO);
    return simple;
}

void reset_shiftReg(ShiftReg shift){
    set_io_pin_high(shift.outputEnable);
    set_io_pin_low(shift.masterReset);
    set_io_pin_high(shift.masterReset);  
    set_io_pin_high(shift.storageClk);
    set_io_pin_low(shift.storageClk);
    // back to normal
    set_io_pin_low(shift.outputEnable);
}

void xfer_to_storage(ShiftReg shift){
    // send clock tick to push to storage
    set_io_pin_high(shift.storageClk);
    set_io_pin_low(shift.storageClk);
}

void enable_output(ShiftReg shift){
    set_io_pin_low(shift.outputEnable);
}
void disable_output(ShiftReg shift){
    set_io_pin_high(shift.outputEnable);
}

void shift_to_parallel_on(ShiftReg shift, uint8_t byte){
    reset_shiftReg(shift);
    for(uint8_t mask = 1, bit = 0; bit < 8; bit++){
        // set serial line high or low for bit
        if(byte & (mask << bit)){
            set_io_pin_high(shift.serialDataIn);
        }
        else{
            set_io_pin_low(shift.serialDataIn);
        }
        // toggle clock to shift
        set_io_pin_high(shift.shiftClk);
        set_io_pin_low(shift.shiftClk);
    }
    set_io_pin_low(shift.serialDataIn); // set low on end
    xfer_to_storage(shift);
}

void simple_shift_to_parallel(SimpleShiftReg shift, uint8_t byte){
    for(uint8_t mask = 1, bit = 0; bit < 8; bit++){
        // set serial line high or low for bit
        if(byte & (mask << bit)){
            set_io_pin_high(shift.serialDataIn);
        }
        else{
            set_io_pin_low(shift.serialDataIn);
        }
        // toggle clock to shift
        set_io_pin_high(shift.shiftClk);
        set_io_pin_low(shift.shiftClk);
    }
    set_io_pin_low(shift.serialDataIn);
    set_io_pin_high(shift.storageClk);
    set_io_pin_low(shift.storageClk);
}