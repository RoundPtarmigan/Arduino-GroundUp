#define __AVR_ATmega328P__
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <ioPort.h>
#include "pwm.h"

// USE PIND6
int main(void){
    IoPin tonePin = IO_PIND5;
    //IoPin tonePin = IO_PIND3;
    //IoPin tonePin = IO_PINB3;
    //IoPin tonePin = IO_PINB3;
    //IoPin tonePin = IO_PINB2;

    //sweep
    config_io_pin(IO_PINB5, IO_OUT_LO);
    config_io_pin(tonePin, IO_OUT_HI);
    //set_pwm_duty(tonePin, 255);
    set_pwm_mode(tonePin, COM_CLEAR);
    config_pwm_ctrl(pin_to_pwm_port(tonePin), WGM_FAST_8BIT, CLK_DIV_8);

    for(int i = 255; i > 10; i--){
        set_pwm_duty(tonePin, i);
        _delay_ms(10);
    }
    for(int i = 10; i < 255; i++){
        set_pwm_duty(tonePin, i);
        _delay_ms(10);
    }
    set_pwm_port_clk(pin_to_pwm_port(tonePin), CLK_STOP);
    while(1){
        //if(playNote(myScale[noteNum], 1000, tonePin, timerPin) && (noteNum < 16)){
           //noteNum++;
        //}
       set_pwm_port_clk(pin_to_pwm_port(tonePin), CLK_DIV_256);
    for(int i = 150; i > 10; i--){
        set_pwm_duty(tonePin, i);
        _delay_ms(10);
    }
    for(int i = 10; i < 150; i++){
        set_pwm_duty(tonePin, i);
        _delay_ms(10);
    }
        set_pwm_port_clk(pin_to_pwm_port(tonePin), CLK_STOP);
        toggle_io_pin(IO_PINB5);
    }
}