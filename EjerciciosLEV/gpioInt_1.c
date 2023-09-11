/*
Ejercicio Lev GPIO interrutp 1

Realizar un programa que configure el puerto P2.0 y P2.1 para que provoquen una interrupción por flanco de subida para el primer pin y por flanco de bajada para el segundo. 
Cuando la interrupción sea por P2.0 se enviará por el pin P0.0 la secuencia de bits 010011010. 
Si la interrupción es por P2.1 se enviará por el pin P0.1 la secuencia 011100110. 
Las secuencias se envían únicamente cuando se produce una interrupción, en caso contrario la salida de los pines tienen valores 1 lógicos. 
¿que prioridad tienen configuradas por defecto estas interrupciones? 

PROBARLO
*/
#include "LPC17xx.h"

#define INPUT1 = (1<<0)
#define INPUT2 = (1<<1)

uint32_t secuencia1 []={0,1,0,0,1,1,0,1,0};
uint32_t secuencia2 []={0,1,1,1,0,0,1,1,0};

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
    if(LPC_GPIOINT->IO2IntStatR & INPUT1){ //P2.0 rising
         LPC_GPIO0->FIOPIN = secuencia1[];
         delay(1000)
    } 

    if(LPC_GPIOINT->IO2IntStatF & INPUT1){ //P2.1 falling
         LPC_GPIO0->FIOPIN = secuencia2[];
         delay(1000)
    } 

    LPC_GPIOINT->IO2IntClr |=(1<<0)
    LPC_GPIOINT->IO2IntClr |=(1<<1)     //clean interrupt
}

void configGPIO(void){
  
  LPC_PINCON->PINSEL4 &~(0xf<<0); //P2.0 y P2.1 as GPIO
  LPC_PINCON->PINSEL0 &~(0xf<<0); //P0.0 y P0.1 as GPIO

  LPC_GPIO0->FIODIR |=(0x3<<0); //P0.0 y P0.1 as output
  LPC_GPIO2->FIODIR &~(INPUT1); //P2.0 as input
  LPC_GPIO2->FIODIR &~(INPUT2); //P2.1 as input

  
}

void configGpioInt(void){
  
LPC_GPIOINT->IO2IntEnR |= INPUT1; //P2.0 Rising edge interrupt
LPC_GPIOINT->IO2IntEnF |=INPUT2; //P2.1 Falling edge interrupt
NVIC_EnableIRQ(EINT3_IRQn); // comparte con eint3
  
}

void delay(uint32_t times) {                   /* Implementarlo con systick */ 
	for(uint32_t i=0; i<times; i++)
		for(uint32_t j=0; j<times; j++); 
}