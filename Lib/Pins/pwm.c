#include <inttypes.h>
#include "ioExtend.h"
#include "ioPort.h"
#include <pwm.h>

#define PWM_8BIT_PORTD_INTERRUPTS {TIMSK0_ADDR, TIFR0_ADDR}
#define PWM_8BIT_PORTX_INTERRUPTS {TIMSK2_ADDR, TIFR2_ADDR}
#define PWM_16BIT_PORTB_INTERRUPTS {TIMSK1_ADDR, TIFR1_ADDR}

#define PWM_8BIT_PORTD  {TCCR0A_ADDR, TCCR0B_ADDR, NO_ADDR, {TCNT0_ADDR}, {OCR0A_ADDR}, {OCR0B_ADDR}, \
                        NO_ADDR, PWM_8BIT_PORTD_INTERRUPTS, NO_ADDR, NO_ADDR} // pins D6 and D5
#define PWM_8BIT_PORTX  {TCCR2A_ADDR, TCCR2B_ADDR, NO_ADDR, {TCNT2_ADDR}, {OCR2A_ADDR}, {OCR2B_ADDR}, \
                        NO_ADDR, PWM_8BIT_PORTX_INTERRUPTS, ASSR_ADDR, GTCCR_ADDR} // pins B3 and D3
#define PWM_16BIT_PORTB  {TCCR1A_ADDR, TCCR1B_ADDR, TCCR1C_ADDR, {TCNT1L_ADDR}, {OCR1AL_ADDR}, {OCR1BL_ADDR}, \
                         (_ADDRW)ICR1L_ADDR, PWM_16BIT_PORTB_INTERRUPTS, NO_ADDR, NO_ADDR} // pins B1 and B2


// Map main modes to 8bit modes
// 0-3: Normal and Phase Correction
// 4-7: CTC and FAST
// 8-11: Phase+Frequence + Phase Correction compared
// 12-15: CTC (ICR) and FAST compared
Wgm8Mode mapToWgm8[NUM_WGM_MODES] = {WGM8_NORMAL, WGM8_PHASE_CORR, WGM8_INVALID, WGM8_INVALID, \
                                    WGM8_CTC, WGM8_FAST, WGM8_INVALID, WGM8_INVALID, \
                                    WGM8_INVALID, WGM8_INVALID, WGM8_INVALID, WGM8_PHASE_CORR_OCR, \
                                    WGM8_INVALID, WGM8_INVALID, WGM8_INVALID, WGM8_FAST_OCR};


const uint16_t mapClkDivToVal[NUM_CLK_DIVS] = {0, 1, 8, 32, 64, 128, 256, 1024, 0, 0};


// map general clock divs to clkdiv for ports D/X
ClkDivs01 mapToClkDivs01[NUM_CLK_DIVS] = {CLK01_STOP, CLK01_DIV_1, CLK01_DIV_8, CLK01_INVALID, \
                                         CLK01_DIV_64, CLK01_INVALID, CLK01_DIV_256, CLK01_DIV_1024, \
                                         CLK01_SRC_T0_FALL, CLK01_SRC_T0_RISE};

// map general clock divs to clkdiv for port B
ClkDivs2 mapToClkDivs2[NUM_CLK_DIVS] = {CLK2_STOP, CLK2_DIV_1, CLK2_DIV_8, CLK2_DIV_32, \
                                         CLK2_DIV_64, CLK2_DIV_128, CLK2_DIV_256, CLK2_DIV_1024, \
                                         CLK2_INVALID, CLK2_INVALID};

// Comparator bit shifts
#define COMA     0x6
#define COMB     0x4
#define COM_MASK  0b11 // mask for COM setting
// Force compar bit shifts
#define FOCA      0x7 
#define FOCB      0x6

// clock bit mask
#define CLK_MASK 0b111
// clock bit shift
#define CLK_SHIFT 0

#define WGM_MASKA 0b0011  // mask for Wave Generation Mode A
#define WGM_MASKB 0b1100  // mask for Wave Generation Mode B
#define WGMA_SHIFT 0      // bit shift for WGM_A
#define WGMB_SHIFT 3      // bit shift for WGM_B
#define WGMB_RELSHIFT (WGMB_SHIFT - 2) // relative shift for WGM_B TODO: This may just be unnecessary

#define PINS_PER_PORT 2
#define MAX_DUTY_8BIT 255

// shifts for pins on PWM port
const uint8_t COM_SHIFT[PINS_PER_PORT] = {COMA, COMB};
const uint8_t INT_SHIFT[PINS_PER_PORT] = {TC_OUTCOMPA_INT, TC_OUTCOMPB_INT};
const uint8_t FOC_SHIFT[PINS_PER_PORT] = {FOCA, FOCB};

// ports
const volatile PwmCtrl PWM_CTRLS[NUM_PWM_PORTS] = {PWM_8BIT_PORTD, PWM_8BIT_PORTX, PWM_16BIT_PORTB};
const volatile PwmCtrl* const get_port_obj(PwmPort port){
    if(port != PWM_NO_PORT){
        return &PWM_CTRLS[port];
    }
    else return 0;
}

#define INVALID -1
// given pin, return associated port
PwmPort pin_to_pwm_port(IoPin pin){
    switch(pin){
        case IO_PIND6:
        case IO_PIND5:
            return PWM_PORT_D;
        case IO_PINB3:
        case IO_PIND3:
            return PWM_PORT_X;
        case IO_PINB1:
        case IO_PINB2:
            return PWM_PORT_B;
        default:
            return PWM_NO_PORT;
    }
}

// given pin, return associated "register"
// each port has a pair of pin settings
PwmRegId pin_to_pwm_reg(IoPin pin){
        switch(pin){
        case IO_PIND6:
        case IO_PINB1:
        case IO_PINB3:
            return REG_A;
        case IO_PIND5:
        case IO_PINB2:
        case IO_PIND3:
            return REG_B;
        default:
            return INVALID_REG;
    }
}

// Translate Wave Generation Mode based on general input mode
// Port D and X have a smaller selection of modes
uint8_t map_port_wgm_mode(PwmPort pwm, WgmMode mode){
    switch(pwm){
        case PWM_PORT_D:
        case PWM_PORT_X:
            return mapToWgm8[mode];
        case PWM_PORT_B:
            return mode;
        default:
            return INVALID;
    }
}

// choose correct clk div settings based on port
uint8_t map_port_clk_div(PwmPort pwm, ClkDivs clkDiv){
    switch(pwm){
        case PWM_PORT_D:
        case PWM_PORT_B:
            return mapToClkDivs01[clkDiv];
        case PWM_PORT_X:
            return mapToClkDivs2[clkDiv];
        default:
            return INVALID;
    }
}

// Configure ANY pwm "Port" with mode and clkDiv
void config_pwm_ctrl(PwmPort pwm, WgmMode mode, ClkDivs clkDiv){
    uint8_t mappedMode = map_port_wgm_mode(pwm,mode);
    uint8_t mappedClk =  map_port_clk_div(pwm, clkDiv);
    if(mappedMode != INVALID && mappedClk != INVALID){
        *(PWM_CTRLS[pwm].tcCtrlA) &= ~(WGM_MASKA << WGMA_SHIFT);
        *(PWM_CTRLS[pwm].tcCtrlA) |= ((mappedMode & WGM_MASKA) << WGMA_SHIFT);
        *(PWM_CTRLS[pwm].tcCtrlB) &= ~((WGM_MASKB << WGMB_RELSHIFT) | (CLK_MASK << CLK_SHIFT));
        *(PWM_CTRLS[pwm].tcCtrlB) |= (((mappedMode & WGM_MASKB) << WGMB_RELSHIFT) | (mappedClk << CLK_SHIFT)); 
    }
}

// enable interrupts on given pin
void enable_pwm_int(IoPin pin){
        PwmPort port = pin_to_pwm_port(pin);
        PwmRegId regId = pin_to_pwm_reg(pin);
        if(regId != INVALID_REG && port != PWM_NO_PORT){
            *(PWM_CTRLS[port].intCtrl.intMask) |= 1 << INT_SHIFT[regId];
        }
}

// disable interrupts on given pin
void disable_pwm_int(IoPin pin){
        PwmPort port = pin_to_pwm_port(pin);
        PwmRegId regId = pin_to_pwm_reg(pin);
        if(regId != INVALID_REG && port != PWM_NO_PORT){
            *(PWM_CTRLS[port].intCtrl.intMask) &= ~(1 << INT_SHIFT[regId]);
        }
}

// clear flag for given pin
void clear_pwm_int_flag(IoPin pin){
        PwmPort port = pin_to_pwm_port(pin);
        PwmRegId regId = pin_to_pwm_reg(pin);
        if(regId != INVALID_REG && port != PWM_NO_PORT){
            *(PWM_CTRLS[port].intCtrl.intFlag) &= ~(1 << INT_SHIFT[regId]);
        }
}

// set clk div on given port
void set_pwm_port_clk(PwmPort pwm, ClkDivs clkDiv){
    uint8_t mappedClk = map_port_clk_div(pwm, clkDiv);
    if(mappedClk != INVALID){
        *(PWM_CTRLS[pwm].tcCtrlB) &= ~(CLK_MASK << CLK_SHIFT);
        *(PWM_CTRLS[pwm].tcCtrlB) |= (mappedClk << CLK_SHIFT);
    }
}

// Get the comparator register address as flexAddr (can be interpretted as 8bit byte or
// 16 bit word)
const flexAddr get_comp_reg(PwmPort port, PwmRegId reg){
    flexAddr ret;
        switch(reg){
            case REG_A:
                ret.asByte = PWM_CTRLS[port].outCompA.asByte;  // .asByte is pointer... just initialize with address
                break;
            case REG_B:
                ret.asByte = PWM_CTRLS[port].outCompB.asByte;
                break;
            default:
                ret.asByte = 0; // handle this as error
                break;
    }
    return ret;
}

// get the timer register address as flexAddr
const flexAddr get_time_reg(PwmPort port){
    flexAddr ret;
    if(port != PWM_NO_PORT){
       ret.asByte = PWM_CTRLS[port].tcCntr.asByte;
    }
    else{
       ret.asByte = 0;
    }
    return ret;
}

// TODO: do I use this?
uint8_t num_flex_bytes(PwmPort port){
    switch(port){
            case PWM_PORT_D:
            case PWM_PORT_X:
                return 1;
            case PWM_PORT_B:
                return 2;
            default:
                return 0;
    }
}
// set duty for given ioPin
void set_pwm_duty(IoPin pin, uint16_t duty){
    PwmPort port = pin_to_pwm_port(pin);
    PwmRegId regId = pin_to_pwm_reg(pin);
    uint8_t adjDuty; 
    if(regId != INVALID_REG && port != PWM_NO_PORT){
        switch(port){
            case PWM_PORT_D:
            case PWM_PORT_X:
                adjDuty = (duty < MAX_DUTY_8BIT)? duty : MAX_DUTY_8BIT;
                *(get_comp_reg(port, regId).asByte) = adjDuty;
                break;
            case PWM_PORT_B:
                *(get_comp_reg(port, regId).asWord) = duty;
                break;
            default:
                break;
        }
    }
}

// set pwm mode for given pin
void set_pwm_mode(IoPin pin, ComMode mode){
    PwmPort port = pin_to_pwm_port(pin);
    PwmRegId regId = pin_to_pwm_reg(pin);

    if(regId != INVALID_REG && port != PWM_NO_PORT){
        *(PWM_CTRLS[port].tcCtrlA) &= ~(COM_MASK << COM_SHIFT[regId]);
        *(PWM_CTRLS[port].tcCtrlA) |= (mode << COM_SHIFT[regId]);
    }
}
// set pwm output for given pin
void set_pwm_out(IoPin pin, ComMode mode, uint16_t duty){
    set_pwm_duty(pin, duty);
    set_pwm_mode(pin, mode);
}

// clear counter associated with given pin
// TODO: change pin to port
void clear_pwm_counter(IoPin pin){
    PwmPort port = pin_to_pwm_port(pin);
    switch(port){
        case PWM_PORT_D:
        case PWM_PORT_X:
            *(PWM_CTRLS[port].tcCntr.asByte) = 0;
            break;
        case PWM_PORT_B:
            *(PWM_CTRLS[port].tcCntr.asWord) = 0;
            break;
        default:
            break;
    }
}

// force compare on given pin
void force_pwm_compare(IoPin pin){
    PwmPort port = pin_to_pwm_port(pin);
    PwmRegId regId = pin_to_pwm_reg(pin);
    switch(port){
        case PWM_PORT_D:
        case PWM_PORT_X:
            *(PWM_CTRLS[port].tcCtrlB) |= 1 << FOC_SHIFT[regId];
            break;
        case PWM_PORT_B:
            *(PWM_CTRLS[port].tcCtrlC) |= 1 << FOC_SHIFT[regId];
            break;
        default:
            break;
    }
}

