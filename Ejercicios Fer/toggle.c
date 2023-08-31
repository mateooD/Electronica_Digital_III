#include "LPC17xx.h"

void configGPIO(void); 
void delay(uint32_t_times);
void SecuenciaA(void)
void SecuenciaB(void)


int main(void){

    configGPIO();

while(1){
    SecuenciaA();
    SecuenciaB();
    delay(1000)
    return 0;
}
}
 
configGPIO(void){
    LPC_PINCON->PINSEL1 &= ~(0xFFFFFFFF)
    LPC_GPIO0->PINMODE0 &= ~(0xFFFFFFFF) 
    LPC_GPIO0->FIODIR |=0x3FF
}

void SecuenciaA(void){
    for(int i=0) // falta terminar
}

void SecuenciaB(void){
// terminar
}

void delay(uint32_t times){
    for(uint32_t i=0; i<times ; i++)
        for(uint32_t j=0; j<times ; j++)
}