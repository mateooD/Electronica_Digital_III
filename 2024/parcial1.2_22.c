/*
    Utilizando interrupcioines por systick y EINT realizar un programa que
    permita habilitar y desabilitar el temporizador por flanco ascendente en el pin p2.11
    El temporizador debe desbordar cada 10ms utilizando cclk=62Mhz.Por cada interrupcion del systick se debe mostrar por el puerto
    P0 el promedio de los valores guardados en la variabla uint8_t values[8].
    Detallar calculos realizados para obtener el valor a cargar en el resigstro reload y asegurar que la interrupcion por systick
    sea mayor prioridad que la prioridad de la interrupcion del evento externo.

*/
#include "LPC17xx.h"

#define BUFFER_SIZE 8
#define SYSTICK_RELOAD 620000

uint8_t values[BUFFER_SIZE];

void configPin();
void configSystick();
void configEINT();
void systickHandler();
void EINT3_IRQHandler();

int main(void){
    configPin();
    configSystick();
    configEINT();
    while(1){

    }
}

void configPin(){
    
    LPC_GPIO0->FIODIR |= (0xFF); // P0.0 a P0.7 como salida
    LPC_PINCON->PINSEL0 &= ~(0xFFFF); // P0.0 a P0.7 como GPIO


    LPC_GPIO2->FIODIR &= ~(1<<11); // P2.11 como entrada
    LPC_GPIOINT->IO2IntEnR |= (1<<11); // Interrupcion por flanco de subida
    
    LPC_GPIOINT->IO2IntClr |= (1<<11); // Limpiar interrupciones pendientes
    
    NVIC_SetPriority(EINT3_IRQn, 1); // Prioridad de la interrupcion
    NVIC_EnableIRQ(EINT3_IRQn); // Habilitar interrupcion
}

void configSystick(){
    SysTick->LOAD = SYSTICK_RELOAD; // Valor de recarga para obtener 10 ms
    SysTick->VAL = 0;                    // Limpiar el valor actual del contador
    SysTick->CTRL = (1) | (1<<1) | (1<<2); // Habilitar el contador y la interrupcion
    NVIC_SetPriority(SysTick_IRQn, 0);

}

void EINT3_IRQHandler(){
   if((LPC_GPIOINT->IO2IntStatR & (1<<11)) == (1<<11)){
       if(SysTick->CTRL & 1){
           SysTick->CTRL &= ~(1); // Deshabilitar el contador
       }else{
           SysTick->CTRL |= 1; // Habilitar el contador
       }
   }
    LPC_GPIOINT->IO2IntClr |= (1<<11); // Limpiar interrupciones pendientes
}

void systickHandler(){
   uint32_t sum = 0;
   uint8_t promedio;

    for(int i = 0; i < BUFFER_SIZE; i++){
         sum += values[i];
    }
    promedio = sum / BUFFER_SIZE;

    LPC_GPIO0->FIOPIN = (LPC_GPIO0->FIOPIN & 0xFFFFFF00) | promedio; // Mostrar el promedio en P0.0 a P0.7


}
    


