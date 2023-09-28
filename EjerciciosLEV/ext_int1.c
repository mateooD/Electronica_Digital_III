/*
Configurar la interrupción externa EINT1 para que interrumpa por flanco de bajada y la interrupción EINT2 para que interrumpa por flanco de subida. 
En la interrupción por flanco de bajada configurar el systick para desbordar cada 25 mseg, mientras que en la interrupción por flanco de subida configurarlo para que desborde cada 60 mseg. 
Considerar que EINT1 tiene mayor prioridad que EINT2.
*/
#include "LPC17xx.h"


void configGPIO(void);
void configeInt(void);


int main(void){
    
    configGPIO();
    configepioInt();

    while(1){
    //do nothing, wait for interrupt
    }
    return 0;
}

void SysTick_Handler(void){
    //Programa 
    SysTick->CTRL &= SysTick->CTRL // Al leer programa limpio flag
}

configeInt(void){
    LPC_PINCON->PINSEL4 |=(1<<22); //EINT1
    LPC_PINCON->PINSEL4 |=(1<<24); //EINT2

    LPC_SC->EXTMODE |=(1<<1); //EINT1 edge sensitive
    LPC_SC->EXTMODE |=(1<<2); //EINT2 edge sensitive

    LPC_SC->EXTPOLAR &~ (1<<1); //EINT1 flanco bajada
    LPC_SC->EXTPOLAR |= (1<<2); //EINT2 flanco subida

    NVIC_EnableIRQ(EINT1_IRQn);
    NVIC_EnableIRQ(EINT2_IRQn);

    NVIC_SetPriority(EINT1_IRQn,0);
    NVIC_SetPriority(EINT2_IRQn,1);
}

void EINT1_IRQHandler(void){
    SysTick->LOAD = 2499999;
    SysTick->VAL=0;
    SysTick->CTRL = (1<<0)|(1<<1)|(1<<2) // Activo systick bit0 ; Activo int bit1 ; CPU clock bit2

}

void EINT2_IRQHandler(void){
    SysTick->LOAD = 5999999;
    SysTick->VAL=0;
    SysTick->CTRL = (1<<0)|(1<<1)|(1<<2) // Activo systick bit0 ; Activo int bit1 ; CPU clock bit2

}