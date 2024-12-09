/*  Por medio del adc leer una señal de 10kz de frecuencia y almacenarlo en un buffer de 4kbytes,
*   Se debe sacar el promedio de los datos transferidos, con el promedio modificar el periodo de la señal(tx)(separacion), 
*   sin afectar el ancho de la señal(10ms) . 
*   Generar la señal triangular por medio del dac sin usar interrupciones
*/

#include "LPC17xx.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_dac.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_gpdma.h"

uint16_t average;
uint16_t tx;

void config_adc_dma();
void Generate_Triangle(tx);
uint16_t Calculate_Average(void);



int main(void) {
    ADC_DMA_Config();

    while (1) {
        average = Calculate_Average();
        tx = Calculate_Tx(average); // Ajustar el período según el promedio
        Generate_Triangle(tx);
    }

    return 0;
}


void config_adc_dma(void) {
    // Configurar el ADC
    ADC_Init(LPC_ADC, 20000); // Frecuencia de muestreo: 20 kHz
    ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_0, ENABLE);

    // Configurar el DMA para transferir datos al buffer
    GPDMA_Init();
    GPDMA_Channel_CFG_Type DMAConfig;
    DMAConfig.ChannelNum = 0;
    DMAConfig.SrcAddr = (uint32_t)&LPC_ADC->ADGDR;
    DMAConfig.DstAddr = 0x2007C000; // Dirección base del buffer en SRAM
    DMAConfig.TransferSize = 2048; // Número de muestras
    DMAConfig.TransferType = GPDMA_TRANSFERTYPE_P2M;
    DMAConfig.SrcConn = GPDMA_CONN_ADC;
    DMAConfig.DstConn = 0;
    DMAConfig.DMALLI = 0; // Buffer circular
    GPDMA_Setup(&DMAConfig);

    // Iniciar transferencia
    GPDMA_ChannelCmd(0, ENABLE);
}

uint16_t Calculate_Average(void) {
    uint32_t sum = 0;
    uint16_t *buffer = (uint16_t *)0x2007C000;
    for (int i = 0; i < 2048; i++) {
        sum += buffer[i];
    }
    return (uint16_t)(sum / 2048);
}

///void Generate_Triangle(tx) {
    // Generar la tabla de la señal triangular
    //uint16_t triangle_table[500];
    //uint16_t max_val = 1023; // Máximo del DAC
    //for (int i = 0; i < 250; i++) {
    //    triangle_table[i] = (i * max_val) / 250; // Subida
   // }
   // for (int i = 250; i < 500; i++) {
   //     triangle_table[i] = max_val - ((i - 250) * max_val) / 250; // Bajada
   // }

   void Generate_Triangle(tx) {
    // Generar la tabla de la señal triangular
    uint16_t triangle_table[500];
    uint16_t min_val = 310; // Valor para 1V
    uint16_t max_val = 620; // Valor para 2V
    for (int i = 0; i < 250; i++) {
        // Subida de la señal
        triangle_table[i] = min_val + ((i * (max_val - min_val)) / 250); 
    }
    for (int i = 250; i < 500; i++) {
        // Bajada de la señal
        triangle_table[i] = max_val - (((i - 250) * (max_val - min_val)) / 250);
    }

    // Configurar el DMA para el DAC
    GPDMA_Channel_CFG_Type DMAConfig;
    DMAConfig.ChannelNum = 1;
    DMAConfig.SrcAddr = (uint32_t)triangle_table;
    DMAConfig.DstAddr = (uint32_t)&LPC_DAC->DACR;
    DMAConfig.TransferSize = 500;
    DMAConfig.TransferType = GPDMA_TRANSFERTYPE_M2P;
    DMAConfig.SrcConn = 0;
    DMAConfig.DstConn = GPDMA_CONN_DAC;
    DMAConfig.DMALLI = 0; // Repetir la tabla
    GPDMA_Setup(&DMAConfig);

    // Configurar temporización del DAC
    DAC_SetDMATimeOut(LPC_DAC, tx); // Ajustar el período tx

    // Iniciar transferencia
    GPDMA_ChannelCmd(1, ENABLE);
}



