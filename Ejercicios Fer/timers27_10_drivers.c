/*Ejercicio: Generar una señal de periodo T2.
 
 Con T1 = T2/n , y n es un número que ingresa por 4 pines del GPIO. Cuando n=0 , 
 la señal es cero y cuando n=15 T1 = T2. (T2=50ms). 
 Cuando se ingresa una señal externa por algún pin de interrupción sacamos la secuencia
 0xA0A3 con la característica que los unos son 10ms y los ceros 5 ms.*/

 #include "LPC17xx.h"



 void configGPIO(void);
 void configGPIOint(void)
 void configEint(void);
 void configTimer0(void);
 // void configTimer1(void); //capture
 void pulseWidth()

 uint32_t n;


 int main(void)
 {
    configGPIO();
    configGPIOint
    configEint();
    configTimer0();

    while(1)
    {
    }
    return 0;
 }

    void configGPIO(void)
    {
        //LPC_PINCON->PINSEL0 & = ~ (0x1F << 6) ; //bit P0.0 ,bit P0.6 - P0.9 gpio **DEFAULT GPIO**
        
        LPC_GPIO0->FIODIR   & = ~ (1<<6) | (1<<7) | (1<<8) | (1<<9) ; //P0.6 - P0.9 as input 
        // Puede ser LPC_GPIO0->FIODIR &=~(0xF<<0)? //
        LPC_GPIO0->FIODIR   |= (1<<0); //P0.0 as output 
    }

    void configGPIOint(void)
    {

    }

    void configEint(void)
    {
      

    }

    void configTimer0(void)
    {
        /* Calculo TIMER
        * 
        */

       //match 0
       //match 1
    }

    void pulseWidth()
    {
        
    }