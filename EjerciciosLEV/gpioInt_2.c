/*
Ejercicio Lev GPIO interrutp 2
Realizar un programa que configure el puerto P0.0 y P2.0 para que provoquen una interrupción por flanco de subida. 
Si la interrupción es por P0.0 guardar el valor binario 100111 en la variable "auxiliar", si es por P2.0 guardar el valor binario 111001011010110

PROBARLO
*/
#include "LPC17xx.h"


void configGPIO(void);
void configGpioInt(void);
void delay(uint32_t times);


int main(void){
    
    configGPIO();
    configGpioInt();

    while(1){
    //do nothing, wait for interrupt
    }
    return 0;
}

void EINT3_IRQHandler(void){
    if(LPC_GPIOINT->IO0IntStatR & (1<<0)){ //P0.0 rising
        auxiliar= 0b100111;
    } 

    if(LPC_GPIOINT->IO2IntStatF & (1<<0)) { //P2.0 falling
        auxiliar= 0b111001011010110;
    } 

    LPC_GPIOINT->IO0IntClr |=(1<<0)
    LPC_GPIOINT->IO2IntClr |=(1<<0)
}

configGPIO(void){
    LPC_PINCON->PINSEL0 &~(0x3<<0);
    LPC_PINCON->PINSEL4 &~(0x3<<0); // P0.0 y P2.0 GpioFunct

    LPC_GPIO0->FIODIR &~(1<<0);
    LPC_GPIO2->FIODIR &~(1<<0); // P0.0 y P2.0 input 

}

void configGpioInt(void){
  
LPC_GPIOINT->IO0IntEnR |= (1<<0); //P0.0 Rising edge interrupt
LPC_GPIOINT->IO2IntEnR |=(1<<0); //P2.0 Rising edge interrupt
NVIC_EnableIRQ(EINT3_IRQn); // comparte con eint3
  
}