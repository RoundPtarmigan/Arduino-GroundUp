#define __AVR_ATmega328P__
#define F_CPU 16000000UL
#include <util/atomic.h>
#include <avr/io.h>
#include <util/delay.h>
#include <ioExtend.h>
#include "pwm.h"


// configure D3, D5, D6 to enable RGB LED control...go through colors
int main(void){
    config_io_pin(IO_PIND6, IO_OUT_HI);
    config_io_pin(IO_PIND5, IO_OUT_HI);
    config_io_pin(IO_PIND3, IO_OUT_HI);

    config_io_pin(IO_PINB5, IO_OUT_HI);
    
    //config_pmw_ctrl(PWM_PORT_D, WGM_FAST_8BIT, CLK_DIV_1024);
    config_pwm_ctrl(PWM_PORT_X, WGM_FAST_8BIT, CLK2_DIV_32);

    set_pwm_out(IO_PIND5, COM_CLEAR, 0);
    set_pwm_out(IO_PIND3, COM_CLEAR, 0);
    set_pwm_out(IO_PIND6, COM_CLEAR, 0);
    /*
    for(uint8_t red = 0; red < 0xFF-21; red+=1 ){
        set_pwm_out(IO_PIND6, COM_CLEAR, red);
        _delay_ms(10);
    }
    set_pwm_out(IO_PIND6, COM_CLEAR, 0);
    for(uint8_t gre = 0; gre < 0xFF-21; gre+=1 ){
        set_pwm_out(IO_PIND5, COM_CLEAR, gre);
        _delay_ms(10);
    }
    set_pwm_out(IO_PIND5, COM_CLEAR, 0);
    for(uint8_t blu = 0; blu < 0xFF-21; blu+=1 ){
        set_pwm_out(IO_PIND3, COM_CLEAR, blu);
        _delay_ms(10);
    }
    set_pwm_out(IO_PIND3, COM_CLEAR, 0);
    set_pwm_out(IO_PIND6, COM_CLEAR, 0);
    set_pwm_out(IO_PIND5, COM_CLEAR, 0);
    for(uint8_t blu = 0; blu < 0xFF-21; blu+=1 ){
        set_pwm_out(IO_PIND5, COM_CLEAR, blu);
        set_pwm_out(IO_PIND6, COM_CLEAR, blu);
        _delay_ms(10);
    }

    set_pwm_out(IO_PIND6, COM_CLEAR, 0);
    set_pwm_out(IO_PIND5, COM_CLEAR, 0);
    for(uint8_t blu = 0; blu < 0xFF-21; blu+=1 ){
        set_pwm_out(IO_PIND3, COM_CLEAR, blu);
        set_pwm_out(IO_PIND6, COM_CLEAR, blu);
        _delay_ms(10);
    }

    set_pwm_out(IO_PIND6, COM_CLEAR, 0);
    set_pwm_out(IO_PIND3, COM_CLEAR, 0);
    for(uint8_t blu = 0; blu < 0xFF-21; blu+=1 ){
        set_pwm_out(IO_PIND3, COM_CLEAR, blu);
        set_pwm_out(IO_PIND5, COM_CLEAR, blu);
        _delay_ms(10);
    }*/
    while(1){
        //set_io_pin_high(IO_PIND6);
        set_io_pin_high(IO_PINB5);
        
        _delay_ms(2000);
        //set_io_pin_low(IO_PIND6);
        set_io_pin_low(IO_PINB5);
        
        _delay_ms(2000);  
    }
}