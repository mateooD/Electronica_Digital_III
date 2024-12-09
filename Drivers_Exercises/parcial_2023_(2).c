/*
*/

#include "LPC17xx.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_dac.h"
#include "lpc17xx_exti.h"
#include "lpc17xx_gpdma.h"
#include "lpc17xx_pinsel.h"



void config_adc();
void config_dac();
void config_dma();
void config_exti();


int main(){
    SystemInit();
    config_adc();
    config_dac();
    config_dma();
    config_exti();
    while(1){
        //Do nothing
    }
    return 0;
}

void config_adc(){
    
}
