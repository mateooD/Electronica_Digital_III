/*
* brief: Generate a sine wave using the DAC and DMA. The sine wave is stored in a buffer. The DMA will transfer the data from the buffer to the DAC.
*        The DAC will convert the digital data to an analog signal. The analog signal will be outputted to a pin(P0.26). 
* author:
* 
*/

#include "LPC17xx.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_dac.h"
#include "lpc17xx_gpdma.h"

#define SINE_TABLE_SIZE 32

uint32_t sine_table[SINE_TABLE_SIZE] = {
    512, 634, 744, 839, 915, 969, 1000, 1007, 990, 950, 
    887, 803, 701, 584, 455, 319, 178,  37,   0,  37, 
    178, 319, 455, 584, 701, 803, 887, 950, 990, 1007, 
    1000, 969
};

void config_dac();
void config_dma();

int main(void){
    SystemInit();
    config_dac();
    config_dma();

    while(1){
        //Do nothing
    }
    return 0;
}

void config_dac(){
    PINSEL_CFG_Type dac_PinCfg;
    dac_PinCfg.Portnum = PINSEL_PORT_0;
    dac_PinCfg.Pinnum = PINSEL_PIN_26;
    dac_PinCfg.Funcnum = PINSEL_FUNC_2; //DAC function
    dac_PinCfg.Pinmode = PINSEL_PINMODE_TRISTATE;
    PINSEL_ConfigPin(&dac_PinCfg);

    //initialize DAC
    DAC_Init(LPC_DAC);
    DAC_SetBias(LPC_DAC,1);
}

void config_dma(){
    //configure channel GPDMA to send data from sine_table to DAC
    GPDMA_Channel_CFG_Type DMACfg;

    DMACfg.ChannelNum = 0;                      //Channel 0
    DMACfg.SrcAddr = (uint32_t)sine_table;      //Source address
    DMACfg.DstAddr = (uint32_t)&LPC_DAC->DACR;  //Destination address
    DMACfg.TransferSize = SINE_TABLE_SIZE;      //Transfer size
    DMACfg.TransferWidth = 0;                   //Transfer width
    DMACfg.SrcConn = GPDMA_CONN_DAC;            //Source connection
    DMACfg.DstConn = 0;                         //Destination connection
    DMACfg.DMALLI = 0;                          //Linker list item structure data address

    //initialize GPDMA
    GPDMA_Init();
    GPDMA_Setup(&DMACfg);

    //enable GPDMA channel
    GPDMA_ChannelCmd(0,ENABLE);

}

void config_dma_LLI(){
    GPDMA_LLI_Type DMA_LLI_Struct;	
    //Prepare DMA link list item structure   //Configre DMA list

    DMA_LLI_Struct.SrcAddr= (uint32_t)sine_table; //Source of data(array of data)}
    DMA_LLI_Struct.DstAddr= (uint32_t)&(LPC_DAC->DACR); //Destination: It can be M or P
    DMA_LLI_Struct.NextLLI= (uint32_t)&DMA_LLI_Struct;  //Next list, in this case it is the same list
    DMA_LLI_Struct.Control= DMA_SIZE					//Data transfer size
            | (2<<18) //source width 32 bit
            | (2<<21) //dest. width 32 bit
            | (1<<26) //source increment 			Page 614 / Table 564
            ;
    /* GPDMA block section -------------------------------------------- */
	
	/* Initialize GPDMA controller */
	GPDMA_Init();

    /* Setup GPDMA channel -------------------------------------------- */
    GPDMA_Channel_CFG_Type GPDMACfg;
    GPDMACfg.ChannelNum = 0; // channel 0 
    GPDMACfg.SrcMemAddr = (uint32_t)(sine_table);// Source memory
    GPDMACfg.DstMemAddr = 0; 	// Destination memory - unused - PERIFERICO
    GPDMACfg.TransferSize = SINE_TABLE_SIZE;// Transfer size
    GPDMACfg.TransferWidth = 0; // Transfer width - unused	
	GPDMACfg.TransferType = GPDMA_TRANSFERTYPE_M2P; // Transfer type M2P
	GPDMACfg.SrcConn = 0;// Source connection - unused
	GPDMACfg.DstConn = GPDMA_CONN_DAC;	// Destination connection 
	GPDMACfg.DMALLI = (uint32_t)&DMA_LLI_Struct;// Linker List Item - unused - Se recorre la misma lista

	// Setup channel with given parameter
	GPDMA_Setup(&GPDMACfg);

}

void_config_dac_LLI(){
    uint32_t tmp;							    	/*Initialization DAC to work together with DMA*/
    
    DAC_CONVERTER_CFG_Type DAC_ConverterConfigStruct;  //Asociate DAC with the timer that organizes the transfer time
    DAC_ConverterConfigStruct.CNT_ENA =SET;			// Enable counter config time of M2DAC
    DAC_ConverterConfigStruct.DMA_ENA = SET;		//Asociate DAC
    DAC_Init(LPC_DAC);		//initialize DAC ->set bias at higher DAC conversion frequency (1mhz)
    
    /* set time out for DAC*/
    tmp = (PCLK_DAC_IN_MHZ*1000000)/(SINE_FREQ_IN_HZ*NUM_SINE_SAMPLE); //Define timer value associated with DAC (own DAC)
    DAC_SetDMATimeOut(LPC_DAC,tmp); //time out for DAC
	DAC_ConfigDAConverterControl(LPC_DAC, &DAC_ConverterConfigStruct);

}