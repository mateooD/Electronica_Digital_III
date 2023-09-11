/*
Ejercicio Lev GPIO entrada_2

Considerando pulsadores normalmente abiertos conectados en un extremo a masa y en el otro directamente a las entradas P0.0 y p0.1. 
Realizar un programa que identifique en una variable cual o cuales pulsadores han sido presionados. 
Las identificaciones posibles a implementar en esta variable van a ser "ninguno", "pulsador 1", "pulsador 2", "pulsador 1 y 2".

*/
#include "LPC17xx.h"


uint32_t acumulador=0;
int main(void){
    
    configGPIO();
    while(1){
    
    }
}

void configGPIO(void){
 
}

//Terminar