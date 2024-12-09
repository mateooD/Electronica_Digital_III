/*
* Some theoric considerations:
*   - 10bit
*   - 2N resistors -> Kelvin-Varley divider
*   - DMA 
*   - Resistence 
*   - 1Mhz max conversion rate
*   - DAC output: (Vref*InputValue)/MaxValue
*   -           = (3.3*InputValue)/1024:
*   -           = InputValue*3.22mV
*   - Value : Digital value to be converted to analog (10bits)
*   - Bias : 0(Fast mode), 1us conversion time, more power consumption, hig frequency signals or sensitive applications time
*   -        1(Slow mode), 2.5us conversion time, less power consumption, low frequency signals
*
*   - Tmp : Time between samples = (PCLK_DAC_IN_MHZ * 1000000) / (SINE_FREQ_IN_HZ * NUM_SINE_SAMPLE);
*   -     : 1*20ms/60 = 0.333ms
*   
*   - Num_sine_sample ---- Sine_freq_hz
*         1------------------- x
*
*    - Num_sine_sample ---- Sine_period
*         1------------------- x
*
*   -// Regla de 3, si 60 muestras[NUM_SINE_SAMPLE] se envian cada 20 ms[SINE_FREQ_HZ=50Hz]
*	// Cada cuanto tiempo se envia una muestra? 
*	// tmp =1*20ms/60 = 0,333ms
*
*
*   Calculate number of points signal -> 
*   N°= (Frecuencia de muestreo * Periodo de la señal)/Numero de muestras
*   N°= )Periodo de la señal) / (Periodo de muestreo)
*   Tener en cuenta cantidad de memoria disponible
*
*/