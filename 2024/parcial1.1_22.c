/*
Realizar un programa que guarde mediante una interrupcion el dato presente en los pines de entrada 
p2.0 a p2.7 cada vez que cambie su valor. 
Cada dato nuevo debe guardarse de forma consecutiva en una region de memoira que permita 
tener disponible siempre de los ultimos 16 datos guardados.
*/

#include "LPC17xx.h"

#define BUFFER_SIZE 16

uint8_t buffer[BUFFER_SIZE];
uint8_t index = 0;

void configPin();

int main(void){
    configPin();
    while(1){

    }
}

void configPin(){
   LPC_GPIO2->FIODIR &= ~(0xFF); // P2.0 a P2.7 como entrada
   LPC_PINCON->PINSEL4 &= ~(0xFFFF); // P2.0 a P2.7 como GPIO
   LPC_GPIOINT->IO2IntEnR |= (0xFF); // Interrupcion por flanco de subida
   LPC_GPIOINT->IO2IntEnF |= (0xFF); // Interrupcion por flanco de bajada
   LPC_GPIOINT->IO2IntClr |= (0xFF); // Limpiar interrupciones pendientes
   NVIC_EnableIRQ(EINT3_IRQn); // Habilitar interrupcion
}

void EINT3_IRQHandler(){
    if((LPC_GPIOINT->IO2IntStatR & 0xFF) == 0xFF) || ((LPC_GPIOINT->IO2IntStatF) & 0xFF){
        buffer[index] = LPC_GPIO2->FIOPIN & 0xFF;
        index = (index + 1) % BUFFER_SIZE;
    }
}





