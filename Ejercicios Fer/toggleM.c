#include "LPC17xx.h"

#define REDLED 		(1<<22)
#define GREENLED 	(1<<25)
uint32_t=0;

void configGPIO(void); 
void delay(uint32_t_times);
void waveForm(void);



int main(void){

    configGPIO();

while(1){
    if(LPC_GPIO2->FIOPIN2 ){  /// FALTA CORREFIR ESTO ULTIMO Y ANDA
    waveFormA();
    }
    waveFormB();
}
}
 
configGPIO(void){

    LPC_PINCON->PINSEL1 &= ~(0x3<<12); //led rojo - gpio
    LPC_PINCON->PINSEL3 &= ~(0x3<<28); //boton placa - gpio
    LPC_PINCON->PINSEL7 &= ~(0x3<<18); //led verde - gpio

    LPC_PINCON->PINSEL4 &= ~(0x3<<20); //boton como input de la plca
    LPC_GPIO2->FIODIR1 &=~(1<2)//
    LPC_GPIO0->FIODIR |=REDLED; //red led
    LPC_GPIO3->FIODIR |= GREENLED; //red 
}

void waveFormA(void){
    LPC_GPIO0->FIOSET |=REDLED ;
    delay(1000);
    LPC_GPIO0->FIOCLR |=REDLED ;
    delay(1000);
    LPC_GPIO0->FIOSET |=REDLED ;
    delay(1000);
    LPC_GPIO0->FIOCLR |=REDLED ;
    delay(1000);
}
void waveFormB(void){
    LPC_GPIO0->FIOSET |=GREENLED ;
    delay(1000);
    LPC_GPIO0->FIOCLR |=GREENLED ;
    delay(1000);
    LPC_GPIO0->FIOSET |=GREENLED ;
    delay(1000);
    LPC_GPIO0->FIOCLR |=GREENLED ;
    delay(1000);
}


void delay(uint32_t times){
    for(uint32_t i=0; i<times ; i++)
        for(uint32_t j=0; j<times ; j++);
}