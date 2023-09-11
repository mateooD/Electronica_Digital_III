/*
Ejercicio Lev GPIO entrada_1

Configurar el pin P0.4 como entrada digital con resistencia de pull down y utilizarlo 
para decidir si el valor representado por los pines P0.0 al P0.3 van a ser sumados o restados 
al valor guardado en la variable "acumulador".El valor inicial de "acumulador" es 0.

*/
#include "LPC17xx.h"


uint32_t acumulador=0;
int main(void){
    configGPIO();
    while(1){
    //COMPLETAR decision
    }
}

void configGPIO(void){
    LPC_PINCON->PINSEL0 &~(0x3<<8);
    LPC_PINCON->PINMODE0 &~(0x3<<8);
    LPC_PINCON->PINSEL0

    LPC_GPIO->FIODIR |=(1<<)  // otr forma de declarar fiodir
    //LPC_GPIO->FIO0DIR0 
    //PC_GPIO->FIO0DIRL
}