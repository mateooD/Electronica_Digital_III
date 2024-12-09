/*
Utilizando Systick e interrupciones externas escribir un código en C que cuente indefinidamente de 0
a 9. Un pulsador conectado a Eint0 reiniciará la cuenta a 0 y se mantendrá en ese valor mientras el
pulsador se encuentre presionado. Un pulsador conectado a Eint1 permitirá detener o continuar la
cuenta cada vez que sea presionado. Un pulsador conectado a Eint2 permitirá modificar la velocidad
de incremento del contador. En este sentido, cada vez que se presione ese pulsador el contador pasará
a incrementar su cuenta de cada 1 segundo a cada 1 milisegundo y viceversa. Considerar que el
microcontrolador se encuentra funcionando con un reloj (cclk) de 16 Mhz. El código debe estar
debidamente comentado y los cálculos realizados claramente expresados. En la siguiente figura se
muestra una tabla que codifica el display y el esquema del hardware sobre el que funcionará el
programa.
*/

#include "LPC17xx.h"

#define LOAD_VALUE_1S 15999999
#define LOAD_VALUE_1MS 15999
#define EINT0 (2<<20)
#define EINT1 (2<<22)
#define EINT2 (2<<24)
#define DISPLAY (0x3FFF<0)


uint8_t display[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
uint8_t count = 0;

void configGpio();
void configSystick();
void configEint();


int main(void){
    configGpio();
    configSystick();
    configEint();
    
    while(1){
      
    }
}

void configGpio(){
    /*Function*/
    LPC_PINCON->PINSEL0 &=~(DISPLAY);

    /*Direction*/
    LPC_GPIO0->FIODIR0 |=(0xEF);// DISPLAY SALIDA
    LPC_GPIO2->FIODIR2 &=~(0x07<<10);// EINT0, EINT1, EINT2 ENTRADA
    
    /*Pull-up and Pull-down*/
    LPC_PINCON->PINMODE4 |= (3<<20); //P2.10 EINT0 PULL DOWN
    //P2.11 EINT1 PULL UP (defecto)
    //P2.12 EINT2 PULL UP (defecto)
}

void configSystick(){
    SysTick->LOAD = LOAD_VALUE_1S;
    SysTick->VAL = 0;
    SysTick->CTRL = (1) | (1<<1) | (1<<2);
}

void configEint(){
    
    /*Function*/
    LPC_PINCON->PINSEL4 &=~(EINT0);
    LPC_PINCON->PINSEL4 &=~(EINT1);
    LPC_PINCON->PINSEL4 &=~(EINT2);
    
    /*Mode*/
    LPC_SC->EXTMODE |= (1<<0); //EINT0 por nivel
    LPC_SC->EXTMODE &=~(3<<1); //EINT1 y EINT2 por flanco

    /*Polarity*/
    LPC_SC->EXTPOLAR |= (1<<0); //EINT0 por nivel alto
    LPC_SC->EXTPOLAR &=~(3<<1); //EINT1 y EINT2 por flanco de subida

    /*clear flag*/
    LPC_SC->EXTINT |= (1<<0); //EINT0 habilitado
    LPC_SC->EXTINT |= (1<<1); //EINT1 habilitado
    LPC_SC->EXTINT |= (1<<2); //EINT2 habilitado

    /*NVIC*/
    NVIC_EnableIRQ(EINT0_IRQn);
    NVIC_EnableIRQ(EINT1_IRQn);
    NVIC_EnableIRQ(EINT2_IRQn);
}

void SysTick_Handler(void){
    count++;
    if(count == 10){
        count = 0;
    }
    LPC_GPIO0->FIODIR0 = display[count];
}

void EINT0_IRQHandler(void){
  if ((LPC_SC->EXTINT & (1 << 0))){    //si el pulsador esta presionado
    count = 0;
  }
  LPC_SC->EXTINT |= (1<<0); // clear flag

}

void EINT1_IRQHandler(void){
  if ((LPC_SC->EXTINT & (1 << 1))){    //si el pulsador esta presionado
    if(SysTick->CTRL & (1<<0)){
      SysTick->CTRL &=~(1<<0);
    }else{
      SysTick->CTRL |=(1<<0);
    }
  }
    LPC_SC->EXTINT |= (1<<1); // clear flag
}

void EINT2_IRQHandler(void){
  if((LPC_SC->EXTINT & (1<<2))){   //si el pulsador esta presionado
    if(SysTick->LOAD == LOAD_VALUE_1S){ 
      SysTick->LOAD = LOAD_VALUE_1MS;
    }else{
        SysTick->LOAD = LOAD_VALUE_1S;
        }
}
    LPC_SC->EXTINT |= (1<<2); // clear flag
}
