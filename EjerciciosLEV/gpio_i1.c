/*
Ejercicio Lev GPIO salida_2

Configurar el pin P0.4 como entrada digital con resistencia de pull down y utilizarlo 
para decidir si el valor representado por los pines P0.0 al P0.3 van a ser sumados o restados 
al valor guardado en la variable "acumulador".El valor inicial de "acumulador" es 0.

*/
#include "LPC17xx.h"


int main(void){
    configGPIO();
    while(1){

    }
}

void configGPIO(void){
    LPC_PINCON->PINSEL0 &~(0x3<<8);
    LPC_PINCON->PINMODE0 &~(0x3<<8);
}