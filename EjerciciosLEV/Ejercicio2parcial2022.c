


#include "LPC17xx.h"

void confEINT1();
void confSystick();
int main(){

    uint8_t values[8];
    int estado = 0;
    LPC_GPIO-> FIODIR |= (0x1); //salida del puerto 0
    confEINT1();
    confSystick();

    while(1){

    }

    return 0;
}

void confEINT1(){
    LPC_PINCON-> PINSEL4 |= (1<<22); //Se selecciona para trabajar el P2.11
    LPC_SC-> EXTMODE |= (1<<1);// rissing edge
    LPC_SC-> EXTINT |= (1<<1); // limpi bandera

    NVIC_EnableIRQ(EINT1_IRQn);// habilito las interrupciones
}

void confSystick(){
    /* para cargar el valor calculo
    tiempo de desboradamiento y frecuencia de clock
    10e-3 y frecuencia 62MHz
    Numero de cargas = 10e-3*62MHz - 1*/
    SysTick-> LOAD |= 61999;
    SysTick-> CTRL |= (1) | (1<<1) | (1<<2);
    estado = 1;
    NVIC_SetPriority(Systick_IRQn,5);
}

void EINT1_IRQHandler(void){
    if(estado){
        Systick-> CTRL &= ~(0x1<<1);
        SysTick-> CTRL &= ~(1<<16);
        estado = 0;
    }
    
    else{
        SysTick-> CTRL |= (1<<1);
        SysTick-> CTRL &= ~(1<<16);
        estado = 1;
    }
}

void Systick_Handler(void){
    int promedio = 0;
    for(int i=0; i<sizeof(array);i++)
        promedio += array[i];      
    
    promedio = promedio/sizeof(array);
    

    LPC_GPIO0-> FIOPIN |= (promedio<<0);
}

