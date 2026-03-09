#include <avr/interrupt.h>
#include "pwm.h"
typedef enum {
    TIMER_PORT_INVALID = -1,
    TIMER_PORT0,
    TIMER_PORT1,
    TIMER_PORT2,
    NUM_TIMER_PORTS
}TimerPort;

typedef enum {
    TIMER_INVALID = -1,
    TIMER0A = 0,
    TIMER0B,
    TIMER1A,
    TIMER1B,
    TIMER2A,
    TIMER2B,
    NUM_TIMERS
} TimerId;

void (*TIMER_FUNCS[NUM_TIMERS])(void)= {0,0,0,0,0,0};

TimerId pin_to_timer(IoPin pin){
    switch(pin){
        case IO_PIND6:
            return TIMER0A;
        case IO_PIND5:
            return TIMER0B;
        case IO_PINB1:
            return TIMER1A;
        case IO_PINB2:
            return TIMER1B;
        case IO_PINB3:
            return TIMER2A;
        case IO_PIND3:
            return TIMER2B;
        default:
            return TIMER_INVALID;
    }
}

void attach_timer_function(IoPin timerPin, void (*func)(void)){
    TimerId timer = pin_to_timer(timerPin);
    if(timer != TIMER_INVALID){
        TIMER_FUNCS[timer] = func;
    }
}
void config_timer(IoPin timerPin){
    config_pwm_ctrl(pin_to_pwm_port(timerPin),WGM_CTC_OCR, CLK_STOP); // Counting mode stopped
    set_pwm_mode(timerPin, COM_DIS);
    clear_pwm_int_flag(timerPin);
    enable_pwm_int(timerPin);      // enable interrupt
}

void set_timer_params(IoPin timerPin, uint16_t duty, ClkDivs clkDiv){
    set_pwm_duty(timerPin, duty);
    set_pwm_port_clk(pin_to_pwm_port(timerPin), clkDiv);
}

void disable_timer(IoPin timerPin){
    disable_pwm_int(timerPin);
    clear_pwm_int_flag(timerPin);
}

ISR(TIMER0_COMPA_vect){
    if(TIMER_FUNCS[TIMER0A]!=0){
        TIMER_FUNCS[TIMER0A]();
    }
}
// PIN D5 Timer
ISR(TIMER0_COMPB_vect){
    if(TIMER_FUNCS[TIMER0B]!=0){
        TIMER_FUNCS[TIMER0B]();
    }
}
// PIN B6 Timer
ISR(TIMER1_COMPA_vect){
    if(TIMER_FUNCS[TIMER1A]!=0){
        TIMER_FUNCS[TIMER1A]();
    }
}
// PIN B5 Timer
ISR(TIMER1_COMPB_vect){
    if(TIMER_FUNCS[TIMER1B]!=0){
        TIMER_FUNCS[TIMER1B]();
    }
}
// PIN B3 Timer
ISR(TIMER2_COMPA_vect){
    if(TIMER_FUNCS[TIMER2A]!=0){
        TIMER_FUNCS[TIMER2A]();
    }
}
// PIN D3 Timer
ISR(TIMER2_COMPB_vect){
    if(TIMER_FUNCS[TIMER2B]!=0){
        TIMER_FUNCS[TIMER2B]();
    }
}