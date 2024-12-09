#include "LPC17xx.h"

void configPin();
void configSystick();
void systickHandler();

int main(void){
    configPin();
    configSystick();
    while(1){

    }
}

void configPin(){
    LPC_GPIO0->FIODIR0 ;
    LPC_PINCON->PINSEL0 ;
    LPC_PINCON->PINMODE0 ;
}

void configSystick(){
    SysTick_Config(SystemCoreClock/1000);
}

void systickHandler(){
    LPC_GPIO0->FIOPIN ;
}

void secuenciaA(){
    LPC_GPIO0->FIOPIN ;
}

void secuenciaB(){
    LPC_GPIO0->FIOPIN ;
}