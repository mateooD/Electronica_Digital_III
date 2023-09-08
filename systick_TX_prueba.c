#include "LPC17xx.h"

void delay();

int main(void){

	pinConfig();

	while(1){


    delay(30);
    LPC_GPIO0->FIOPIN  &= ~ (0x1<<9);
    delay(30);
    LPC_GPIO0->FIOPIN  |= (0x1<<9);
    delay(30);
    LPC_GPIO0->FIOPIN  &= ~ (0x1<<9);
    delay(30);
}
}



void delay (uint32_t milisegundos){


	SysTick->CTRL = (1) | (1<<2);

    uint32_t Nc;
    Nc= milisegundos*SystemCoreClock;
    SysTick->LOAD = ((SystemCoreClock/Nc)-1);

	SysTick->VAL = 0;
    while(SysTick->VAL > 0){
    }


}

void pinConfig(void){
    LPC_PINCON->PINSEL0 &= ~(0x3<<18); 	//P0.9 as GPIO
	LPC_GPIO0->FIODIR |= (1<<9); 		//P0.9 as output
}
