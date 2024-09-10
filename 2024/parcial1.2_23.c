/*
Utilizando interrupciones por GPIO realizar un código en C que permita, mediante 4 pines de
entrada GPIO, leer y guardar un número compuesto por 4 bits. Dicho número puede ser
cambiado por un usuario mediante 4 switches, los cuales cuentan con sus respectivas
resistencias de pull up externas. El almacenamiento debe realizarse en una variable del tipo
array de forma tal que se asegure tener disponible siempre los últimos 10 números elegidos
por el usuario, garantizando además que el número ingresado más antiguo, de este conjunto
de 10, se encuentre en el elemento 9 y el número actual en el elemento 0 de dicho array. La
interrupción por GPIO empezará teniendo la máxima prioridad de interrupción posible y cada
200 números ingresados deberá disminuir en 1 su prioridad hasta alcanzar la mínima posible.
Llegado este momento, el programa deshabilitará todo tipo de interrupciones producidas por
las entradas GPIO. Tener en cuenta que el código debe estar debidamente comentado
*/

#include "LPC17xx.h"

#define arraySize 10
#define GPIO0 (0xFF<<0)


uint8_t array[arraySize];
uint8_t index = 0;
uint8_t count = 0;


void configGpio();
void configInterrupcion();


int main(void){
    configGpio();
    configInterrupcion();
    
    while(1){
      
    }
}

void configGpio(){
    /*Function*/
    LPC_PINCON->PINSEL0 &=~(GPIO0); // gpio function
    
    /*Direction*/
    LPC_GPIO0->FIODIR0 &=~(0x0F);// ENTRADA

    /*Pull-up and Pull-down*/
    // SON EXTERNAS
}

void configInterrupcion(){
   LPC_GPIOINT->IO0IntEnF |= (0xFF); /// Interrupcion por flanco de bajada(POR SER PULL UP)
    NVIC_SetPriority(EINT3_IRQn, 0);
    NVIC_EnableIRQ(EINT3_IRQn);
}

void EINT3_IRQHandler(void){
  if(LPC_GPIOINT->IO0IntStatF & (0x0F)){
    array[index] = LPC_GPIO0->FIOPIN0 & 0x0F;
    index = (index+1) % arraySize; // circular buffer y se asegura que el indice no sobrepase el tamaño del array
    count++;
        if(count == 200){
            count = 0;
            NVIC_SetPriority(EINT3_IRQn, NVIC_GetPriority(EINT3_IRQn) + 1);
            if(NVIC_GetPriority(EINT3_IRQn) == 31){
                NVIC_DisableIRQ(EINT3_IRQn);    
            }
        }
        LPC_GPIOINT->IO0IntClr = (0xFF);   
    }   
}

