/*
* brief: Generate a variable signal using a timer0. Using capture mode measure the period of the signal. 
        Turn on leds like a vumeter according to the frequency of the signal. With a button you can change the frequency of the signal.
* author: 
* 
*/


#include "LPC17xx.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_timer.h"

int main(){
    SystemInit();
    config_gpio();
    config_timer();
    
    while (1)
    {
        // interrupt service routine
    }
    
}

