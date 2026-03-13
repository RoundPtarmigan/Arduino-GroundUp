#include <avr/interrupt.h>
#include <timer.h>

// TODO: Pins should be abstracted away (as an exercise or just to simplify code)
// function pointers for ISRs associated with each timer
void (*TIMER_FUNCS[NUM_TIMERS])(void)= {0,0,0,0,0,0};

// each timer is associated to a pin
// we can use a map
IoPin timer_to_pin[NUM_TIMERS] = {IO_PIND6, IO_PIND5, IO_PINB1, IO_PINB2, IO_PINB3, IO_PIND3};

// each pin is associated to a timer
// handle the case where an invalid pin is given
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

// attach function to timer using pin
void attach_timer_function(IoPin timerPin, void (*func)(void)){
    TimerId timer = pin_to_timer(timerPin);
    if(timer != TIMER_INVALID){
        TIMER_FUNCS[timer] = func;
    }
}

// config timer using pin
void config_timer(IoPin timerPin){
    config_pwm_ctrl(pin_to_pwm_port(timerPin),WGM_CTC_OCR, CLK_STOP); // Counting mode stopped
    set_pwm_mode(timerPin, COM_DIS);
    clear_pwm_int_flag(timerPin);
    enable_pwm_int(timerPin);      // enable interrupt
}

// set timer parameters using pin
void set_timer_params(IoPin timerPin, uint16_t duty, ClkDivs clkDiv){
    set_pwm_duty(timerPin, duty);
    set_pwm_port_clk(pin_to_pwm_port(timerPin), clkDiv);
}

// disable timer using pin
void disable_timer(IoPin timerPin){
    disable_pwm_int(timerPin);
    clear_pwm_int_flag(timerPin);
}

// configure a basic running timer that resets at the top
// duty and clock are not needed
void configure_basic_timer(TimerId timer, ClkDivs clkDiv){
    config_pwm_ctrl(pin_to_pwm_port(timer_to_pin[timer]), WGM_NORMAL, clkDiv);
    set_pwm_mode(timer_to_pin[timer], COM_DIS);
}

// returns the current time on a timer
uint16_t get_curr_time(TimerId timer){
    PwmPort port = pin_to_pwm_port(timer_to_pin[timer]);
    switch(get_num_timer_bytes(port)){
        case 1:
            return *(get_time_reg(port).asByte);
        case 2:
            return *(get_time_reg(port).asWord);
        default:
            return 0;  // should not be possible given timer-to-pin map
    }
}

// special function to ensure adding two times together results in correct wrapping for timer
uint16_t add_times_and_wrap(TimerId timer, uint16_t base, uint16_t add){
    PwmPort port = pin_to_pwm_port(timer_to_pin[timer]);
    uint8_t smallResult;
    switch(get_num_timer_bytes(port)){
        case 1:
            smallResult = (uint8_t)base + (uint8_t)add; // force uint8_t wrapping
            return smallResult;
        case 2:
            return base+add; // nominal uint16_t wrapping
        default:
            return 0;  // should not be possible given timer-to-pin map
    }
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