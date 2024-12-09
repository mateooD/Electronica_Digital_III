/*
* brief: Generate a wave using the DAC
* author:
* 
*/

#include "LPC17xx.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_dac.h"



int main(void){
    SystemInit();
    config_gpio();
    config_dac();

    while(1){
        for(int i = 0; i < 1024; i++){
            DAC_UpdateValue(LPC_DAC, i);
        }
    }
    return 0;
}

void config_gpio(){
    PINSEL_CFG_Type dac_PinCfg;
    dac_PinCfg.Portnum = PINSEL_PORT_0;
    dac_PinCfg.Pinnum = PINSEL_PIN_26; 
    dac_PinCfg.Funcnum = PINSEL_FUNC_2; //DAC function
    dac_PinCfg.Pinmode = PINSEL_PINMODE_NORMAL;

    PINSEL_ConfigPin(&dac_PinCfg); //Configure pin
}

void config_dac(){
    DAC_Init(LPC_DAC);
    DAC_ConfigDAConverterControl(LPC_DAC, &DAC_ConfigStruct);


}