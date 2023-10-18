//Ejercicio 1

#include "LPC17xx.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_timer.h"

#define CANT_DATA 20
#define SAMPLE_FREQ 200000

uint8_t current_sample = 0;

uint32_t array2[CANT_DATA];
uint32_t array4[CANT_DATA];


void configADC(void);
void configPIN(void);
void ADC_IRQHandler(void);

int main(void)
{
    configPIN();
    configADC();


    while(1){


    }

    return;
}


void configPIN()
{
    PINSEL_CFG_Type pin2cfg;
    /*
        Inicializacion ADC pin connect AD0.2 on 
    */
    pin2cfg.Portnum		=	0;
    pin2cfg.Pinnum		=	25;
    pin2cfg.Funcnum		=	1; //First alternate function, in this case ADC0.2 (PINSEL1, [18:19])
	pin2cfg.Pinmode		=	PINSEL_PINMODE_TRISTATE; //By request from the manufacturer
    PINSEL_ConfigPin(&pin2cfg);

    PINSEL_CFG_Type pin4cfg;
    /*
        Inicializacion ADC pin connect AD0.4 on 
    */
    pin4cfg.Portnum		=	1;
    pin4cfg.Pinnum		=	30;
    pin4cfg.Funcnum		=	3; //First alternate function, in this case ADC0.4
	pin4cfg.Pinmode		=	PINSEL_PINMODE_TRISTATE; //By request from the manufacturer
    PINSEL_ConfigPin(&pin4cfg);

}

void configADC(void)
{
    ADC_Init(LPC_ADC, SAMPLE_FREQ);
    ADC_BurstCmd(LPC_ADC, ENABLE);

	ADC_ChannelCmd(LPC_ADC, 2, ENABLE);
    ADC_ChannelCmd(LPC_ADC, 4, ENABLE);

	ADC_IntConfig(LPC_ADC, ADC_ADINTEN2, ENABLE);
    ADC_IntConfig(LPC_ADC, ADC_ADINTEN4, ENABLE);
	
    NVIC_EnableIRQ(ADC_IRQn);
}


void ADC_IRQHandler(void)
{ 
    
    if(ADC_ChannelGetStatus(LPC_ADC,2, ADC_DATA_DONE)){ //We need to ask if the channel 2 interrupted

  uint32_t adc_value	=	ADC_ChannelGetData(LPC_ADC,2);	//Store digitalized data into adc_value
            array2[current_sample]= adc_value;
            current_sample=(current_sample+1)
          
		NVIC_DisableIRQ(ADC_IRQn);	//Disable ints
	}

    if(ADC_ChannelGetStatus(LPC_ADC,4, ADC_DATA_DONE)){ //We need to ask if the channel 2 interrupted

uint32_t adc_value	=	ADC_ChannelGetData(LPC_ADC,4);	//Store digitalized data into adc_value
        array4[current_sample]= adc_value;
            current_sample=(current_sample+1)
		NVIC_DisableIRQ(ADC_IRQn);	//Disable ints
	}
}


