
#include "lpc17xx_dac.h"    	//hago llamado a librerias de drivers
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpdma.h"
#include "lpc17xx_gpio.h"

#define DMA_SIZE 60			// tamaño de region de memoria que se quiere transf a DAC 
#define NUM_SINE_SAMPLE 60	// cantidad datos onda senoidal
#define SINE_FREQ_IN_HZ 50  // salida 50hz (20 ms)
#define PCLK_DAC_IN_MHZ 25  //CCLK divided by 4 -> "Timer asociado"

void confPin(void);
void confDMA(void);
void confDac(void);
GPDMA_Channel_CFG_Type GPDMACfg; //variable (de libreria) que configura DMA

uint32_t dac_sine_lut[NUM_SINE_SAMPLE]; //array que define los datos
int main(void)
{
	uint32_t i;
	uint32_t sin_0_to_90_16_samples[16]={\
			0,1045,2079,3090,4067,\					//datos que muestra 1/4 de onda senoidal
			5000,5877,6691,7431,8090,\
			8660,9135,9510,9781,9945,10000\
	};
	confPin();
	confDac();
	
	//Prepare DAC sine look up table (formacion de la onda completa)
	for(i=0;i<NUM_SINE_SAMPLE;i++)
	{
		if(i<=15)
		{
			dac_sine_lut[i] = 512 + 512*sin_0_to_90_16_samples[i]/10000;
			if(i==15) dac_sine_lut[i]= 1023;
		}
		else if(i<=30)
		{
			dac_sine_lut[i] = 512 + 512*sin_0_to_90_16_samples[30-i]/10000;
		}
		else if(i<=45)
		{
			dac_sine_lut[i] = 512 - 512*sin_0_to_90_16_samples[i-30]/10000;
		}
		else
		{
			dac_sine_lut[i] = 512 - 512*sin_0_to_90_16_samples[60-i]/10000;
		}
		dac_sine_lut[i] = (dac_sine_lut[i]<<6);
	}
	confDMA();
	// Enable GPDMA channel 0
	GPDMA_ChannelCmd(0, ENABLE);
	while (1);
	return 0;
}
void confPin(void){
	
	PINSEL_CFG_Type PinCfg;			//struct variable

	/*
	 * Init DAC pin connect							
	 * AOUT on P0.26         PIN SALIDA DAC
	 */

		/*El fabircante define struct que despues son argumentos a las funciones del driver
		para que esa funcion modifique al periferico */


	PinCfg.Funcnum = 2; 	//cargo valores a modificar  -> Por eso variable.miembroStruct
	PinCfg.OpenDrain = 0;   //Ponemos solo el valor ya que en el .h estan definidas las macros
	PinCfg.Pinmode = 0;
	PinCfg.Pinnum = 26;		// en esta seccion solo se cargan valores, NO ESTA CONFIG AUN
	PinCfg.Portnum = 0;  	//por ejemplo aca seria PinCfg.Portnum=PINSEL_PORT_0

	PINSEL_ConfigPin(&PinCfg); /*funcion propia del driver que pide como argumento un puntero del tipo de struct de arriba
								 esas funciones permiten modificar el registro del micro,*/


	return;
}
void confDMA(void){							//Cfg de DMA
	GPDMA_LLI_Type DMA_LLI_Struct;		
	//Prepare DMA link list item structure   //CONFIGURO LA LISTA
	DMA_LLI_Struct.SrcAddr= (uint32_t)dac_sine_lut; //Fuente de los datos(array de datos)
	DMA_LLI_Struct.DstAddr= (uint32_t)&(LPC_DAC->DACR); //Destino:Puede ser M o P
	DMA_LLI_Struct.NextLLI= (uint32_t)&DMA_LLI_Struct;  //Prox lista, en este caso es la misma lista
	DMA_LLI_Struct.Control= DMA_SIZE					//Tamaño de transf de datos
			| (2<<18) //source width 32 bit
			| (2<<21) //dest. width 32 bit
			| (1<<26) //source increment 			Pagina 614 / Table 564
			;

			
	/* GPDMA block section -------------------------------------------- */
	
	/* Initialize GPDMA controller */
	GPDMA_Init();
	// Setup GPDMA channel --------------------------------
	
	GPDMACfg.ChannelNum = 0; // channel 0   //mayor prioridad
	
	GPDMACfg.SrcMemAddr = (uint32_t)(dac_sine_lut);// Source memory

	GPDMACfg.DstMemAddr = 0; 	// Destination memory - unused - PERIFERICO
	
	GPDMACfg.TransferSize = DMA_SIZE;// Transfer size
	
	GPDMACfg.TransferWidth = 0; // Transfer width - unused
	
	GPDMACfg.TransferType = GPDMA_TRANSFERTYPE_M2P; // Transfer type M2P
	
	GPDMACfg.SrcConn = 0;// Source connection - unused

	GPDMACfg.DstConn = GPDMA_CONN_DAC;	// Destination connection 
	
	GPDMACfg.DMALLI = (uint32_t)&DMA_LLI_Struct;// Linker List Item - unused - Se recorre la misma lista

	// Setup channel with given parametercada 20 ms[SINE_FREQ_HZ=50Hz]
	// Cada cuanto tiempo se envia una muestra? 
	GPDMA_Setup(&GPDMACfg);
	return;
}
void confDac(void){
	uint32_t tmp;							    	/*Inicializacion DAC para que trabaje junto DMA*/
	
	DAC_CONVERTER_CFG_Type DAC_ConverterConfigStruct;  //asociar dac el timer que organiza el time de transferencia
	DAC_ConverterConfigStruct.CNT_ENA =SET;			// habilita contador config tiempo de M2DAC
	DAC_ConverterConfigStruct.DMA_ENA = SET;		//asocia el dac
	DAC_Init(LPC_DAC);		//inicializa DAC ->setea el bias en mayor frecuencia de conversion de DAC (1mhz)
	
	/* set time out for DAC*/
	tmp = (PCLK_DAC_IN_MHZ*1000000)/(SINE_FREQ_IN_HZ*NUM_SINE_SAMPLE); //define valor timer asoc al dac (propioDAC)
	
	// Regla de 3, si 60 muestras[NUM_SINE_SAMPLE] se envian cada 20 ms[SINE_FREQ_HZ=50Hz]
	// Cada cuanto tiempo se envia una muestra? 
	// tmp =1*20ms/60 = 0,333ms

	//El DMA debe interrumpir(pedir muestras) cada tmp

	DAC_SetDMATimeOut(LPC_DAC,tmp); //tiempo al cual el timer desborda, para que el dma sepa cuando mandar nueva muestra al DAC
	DAC_ConfigDAConverterControl(LPC_DAC, &DAC_ConverterConfigStruct);
	return;
}