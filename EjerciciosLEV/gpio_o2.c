/*
Ejercicio Lev GPIO salida_2

En los pines P2.0 a P2.7 se encuentra conectado un display de 7 segmentos. 
Utilizando la variable numDisplay [10] ={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67} 
que codifica los números del 0 a 9 para ser mostrados en el display 
realizar un programa que muestre indefinidamente la cuenta de 0 a 9 en dicho display.

Probar con placa
*/
#include "LPC17xx.h"


uint32_t numDisplay [10] ={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67} //common cathode

void configGPIO(void);
void delay(uint32_t times)

int main(void)
{
    configGPIO();
    while(1){
        for(i=0;i<10;i++){
            LPC_GPIO2->FIOPIN =numDisplay[i];
            delay(1000);
        }
    }
}

void configGPIO(void){
    
    /*PINSEL*/
    LPC_PINCON->PINSEL4 & ~(0xff<<0); //declaro gpio function

    /*FIODIR*/
    LPC_GPIO2->FIODIR  |=(0xff<<0); // declaro output

}

void delay(uint32_t times) {                   /* Implementarlo con systick */
	for(uint32_t i=0; i<times; i++)
		for(uint32_t j=0; j<times; j++); 
}