/*Ejercicio: Generar una señal de periodo T2.
 
 Con T1 = T2/n , y n es un número que ingresa por 4 pines del GPIO. Cuando n=0 , 
 la señal es cero y cuando n=15 T1 = T2. (T2=50ms). 
 Cuando se ingresa una señal externa por algún pin de interrupción sacamos la secuencia
 0xA0A3 con la característica que los unos son 10ms y los ceros 5 ms.*/

 #include "LPC17xx.h"

 #define SET_PR =

 void configGPIO(void);
 void configEint(void);
 void configTimer0(void);
 // void configTimer1(void); //capture
 void pulseWidth()

 int main(void)
 {
    configEint();
    configTimer0();

    while(1)
    {
    }
    return 0;
 }

    void configGPIO(void)
    {
        LPC_PINCON->PINSEL0 & = ~ (0x1F << 0) ; //bit P0.0 - P0.5 GPIO function
        LPC_GPIO0->FIODIR   & = ~ (1<<0) | (1<<1) | (1<<2) | (1<<3) ; //P0.0 - P0.4 as input 
        // Puede ser LPC_GPIO0->FIODIR &=~(0xF<<0)? //

        LPC_GPIO0->FIODIR   |= (1<<4); //P0.5 as output 
    }

    void configEint(void)
    {
       LPC_PINCON->PINSEL4 |=(1 << 20);
       LPC_SC->EXTMODE  |=(1<<20); // Edge
       LPC_SC->EXTPOLAR &= ~(1<<20); // Falling
       LPC_SC->EXTINT   |=(1<<20); //clear flag

       NVIC_EnableIRQ(EINT0_IRQn);


    }

    void configTimer0(void)
    {
        LPC_PINCON->PINSEL3 |=(3 << 24); //P1.28 MAT0.0
        LPC_PINCON->PINSEL3 |=(3 << 26); //P1.29 MAT0.1

        LPC_SC->PCONP
        LPC_SC->PCLKSEL0

        LPC_TIM0->PR = SET_PR

        /* Calculo TIMER
        * 
        */
    }

    pulseWidth(){
     
    }