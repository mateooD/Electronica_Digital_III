/*
1.- Configure el Systick Timer de modo que genere una forma de onda llamada PWM tal como la que se muestra en la figura adjunta. 
Esta señal debe ser sacada por el pin P0.22 para que controle la intensidad de brillo del led. 
El periodo de la señal debe ser de 10 mseg con un duty cycle de 10%. Configure la interrupción externa EINT0 de modo que cada vez que se entre en una rutina de interrupción externa el duty cycle incremente en un 10% (1 mseg). 
Esto se repite hasta llegar al 100%, luego, si se entra nuevamente a la interrupción externa, el duty cycle volverá al 10%.

2.- Modificar los niveles de prioridad para que la interrupción por systick tenga mayor prioridad que la interrupción externa.

*/


#include "LPC17xx.h"


void configGPIO(void);
void configExtInt(void);
void configSysTick(void);

uint32_t dutyCicle = 1 ;  //duty en 10%

int main(void){
    
    configGPIO();
    configepioInt();

    while(1){
    //do nothing, wait for interrupt
    }
    return 0;
}

void SysTick_Handler(void){
    //Programa 
    SysTick->CTRL &= SysTick->CTRL // Al leer programa limpio flag
}

configGPIO(void){
    LPC_PINCON->PINSEL &~ (0x3<<12);
   
    LPC_GPIO0->FIODIR  |= (1<<22);

}

configExtInt(void){
    
    LPC_PINCON->PINSEL4 |=(1<<20); //EINT0
    LPC_SC->EXTMODE |=(1<<0); //EINT0 edge sensitive
    LPC_SC->EXTPOLAR &~ (1<<0); //EINT0 flanco bajada


    NVIC_EnableIRQ(EINT1_IRQn);
    NVIC_EnableIRQ(EINT2_IRQn);

    NVIC_SetPriority(EINT1_IRQn,0);
    NVIC_SetPriority(EINT2_IRQn,1);
}

void EINT1_IRQHandler(void){
    SysTick->LOAD = 2499999;
    SysTick->VAL=0;
    SysTick->CTRL = (1<<0)|(1<<1)|(1<<2) // Activo systick bit0 ; Activo int bit1 ; CPU clock bit2

}

