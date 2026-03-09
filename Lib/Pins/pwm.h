#ifndef PWM_H
#define PWM_H
#include <inttypes.h>
#include "ioExtend.h"
#include "ioPort.h"
typedef union flexAddr{
    volatile uint8_t*  asByte;
    volatile uint16_t* asWord;
}flexAddr;

typedef struct PwmIntCtrl{
    _ADDR intMask;
    _ADDR intFlag;
}PwmIntCtrl;
#define TC_OVERFLOW_INT 0
#define TC_OUTCOMPA_INT 1
#define TC_OUTCOMPB_INT 2

#define NO_ADDR 0
typedef struct PwmCtrl{
    _ADDR    tcCtrlA;
    _ADDR    tcCtrlB;
    _ADDR    tcCtrlC;
    flexAddr tcCntr;
    flexAddr outCompA;
    flexAddr outCompB;
    _ADDRW   tcIcr;
    PwmIntCtrl intCtrl;
    _ADDR    tcAssr;
    _ADDR    tcGtccr;
} PwmCtrl;

typedef enum{
    PWM_NO_PORT = -1,
    PWM_PORT_D = 0,
    PWM_PORT_X,
    PWM_PORT_B,
    NUM_PWM_PORTS
}PwmPort;

typedef enum{
    INVALID_REG = -1,
    REG_A = 0,
    REG_B,
} PwmRegId;

typedef enum{
    WGM8_INVALID = -1,
    WGM8_NORMAL = 0,
    WGM8_PHASE_CORR, // TOP 0xFF
    WGM8_CTC,
    WGM8_FAST,               // TOP 0xFF
    WGM8_RESERVED0,
    WGM8_PHASE_CORR_OCR,   // TOP OCR
    WGM8_RESERVED1,
    WGM8_FAST_OCR,         // TOP OCR
    NUM_WGM8_MODES,
}Wgm8Mode;

typedef enum{
    WGM_NORMAL = 0,
    WGM_PHASE_CORR_8BIT,
    WGM_PHASE_CORR_9BIT,
    WGM_PHASE_CORR_10BIT,
    WGM_CTC_OCR,
    WGM_FAST_8BIT,
    WGM_FAST_9BIT,
    WGM_FAST_10BIT,
    WGM_PHASE_FREQ_CORR_ICR,
    WGM_PHASE_FREQ_CORR_OCR,
    WGM_PHASE_CORR_ICR,
    WGM_PHASE_CORR_OCR,
    WGM_CTC_ICR,
    WGM_RESERVED,
    WGM_FAST_ICR,
    WGM_FAST_OCR,
    NUM_WGM_MODES,
}WgmMode;

// Map main modes to 8bit modes
// 0-3: Normal and Phase Correction
// 4-7: CTC and FAST
// 8-11: Phase+Frequence + Phase Correction compared
// 12-15: CTC (ICR) and FAST compared
extern Wgm8Mode mapToWgm8[NUM_WGM_MODES];

typedef enum{
    CLK_STOP = 0,
    CLK_DIV_1,       
    CLK_DIV_8,
    CLK_DIV_32,       
    CLK_DIV_64,      
    CLK_DIV_128,     
    CLK_DIV_256,
    CLK_DIV_1024,    
    CLK_SRC_T0_FALL, 
    CLK_SRC_T0_RISE,
    NUM_CLK_DIVS,
}ClkDivs;
#define CLK_SHIFT 0

extern const uint16_t mapClkDivToVal[NUM_CLK_DIVS];

typedef enum{
    CLK01_INVALID = -1,
    CLK01_STOP = 0,
    CLK01_DIV_1,       
    CLK01_DIV_8,       
    CLK01_DIV_64,      
    CLK01_DIV_256,     
    CLK01_DIV_1024,    
    CLK01_SRC_T0_FALL, 
    CLK01_SRC_T0_RISE,
}ClkDivs01;

typedef enum{
    CLK2_INVALID = -1,
    CLK2_STOP = 0,
    CLK2_DIV_1,       
    CLK2_DIV_8,
    CLK2_DIV_32,       
    CLK2_DIV_64,      
    CLK2_DIV_128,     
    CLK2_DIV_256,
    CLK2_DIV_1024,  
}ClkDivs2;

extern ClkDivs01 mapToClkDivs01[NUM_CLK_DIVS];
extern ClkDivs2 mapToClkDivs2[NUM_CLK_DIVS];

#define CLK_MASK 0b111
#define CLK_DIVS_OFFS 1

typedef struct ClockDivs{
    uint16_t* clockDivs;
    uint8_t   numDivs;
}ClockDivs;
#define NUM_NORM_CLK_DIVS 5
#define NUM_EXT_CLK_DIVS  7


typedef enum{
    COM_DIS = 0,  // disconnected Output Comparator
    COM_TOGGLE,  // toggle if WGM2 == 1 // else disconnect
    COM_CLEAR,   // clear output comparator
    COM_SET,      // set output comparator
}ComMode;


const volatile PwmCtrl* const get_port_obj(PwmPort port);

#define INVALID -1
PwmPort pin_to_pwm_port(IoPin pin);

PwmRegId pin_to_pwm_reg(IoPin pin);

uint8_t map_port_wgm_mode(PwmPort pwm, WgmMode mode);

uint8_t map_port_clk_div(PwmPort pwm, ClkDivs clkDiv);
void config_pwm_ctrl(PwmPort pwm, WgmMode mode, ClkDivs clkDiv);

void enable_pwm_int(IoPin pin);
void disable_pwm_int(IoPin pin);
void clear_pwm_int_flag(IoPin pin);

void set_pwm_port_clk(PwmPort pwm, ClkDivs clkDiv);

const flexAddr get_comp_reg(PwmPort port, PwmRegId reg);
const flexAddr get_time_reg(PwmPort port);

uint8_t num_flex_bytes(PwmPort port);
void set_pwm_duty(IoPin pin, uint16_t duty);

void set_pwm_mode(IoPin pin, ComMode mode);
// IO PINS: D6, D5, B3, D3
void set_pwm_out(IoPin pin, ComMode mode, uint16_t duty);
void clear_pwm_counter(IoPin pin);
void force_pwm_compare(IoPin pin);
#endif

