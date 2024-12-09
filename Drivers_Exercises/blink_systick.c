/*
* brief: Blink a LED with systick timer
* author:
* 
*/

#include "LPC17xx.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"

#include "lpc17xx_systick.h"

#define LED_PIN   ((uint32_t)(1 << 26)) /* P3.26 connected to LED */
#define LED_PINR  ((uint32_t)(1 << 9)) /* P0.9 connected to LED */
#define OUTPUT 1
#define INPUT 0
#define PORT_0  0
#define PORT_3  3


volatile uint32_t counter = 0;


void config_gpio();
void config_systick();
void SysTick_Handler(void);


int main(void){
    SystemInit();
    config_gpio();
    config_systick();
    while(1){
        //Do nothing
    }
    return 0;
}
void config_gpio(){
    PINSEL_CFG_Type led_PinCfg;
    led_PinCfg.Portnum = PINSEL_PORT_3;
    led_PinCfg.Pinnum = PINSEL_PIN_26; 
    led_PinCfg.Funcnum = PINSEL_FUNC_0; //Gpio function
    led_PinCfg.Pinmode = PINSEL_PINMODE_NORMAL;

    PINSEL_ConfigPin(&led_PinCfg); //Configure pin

    //void GPIO_SetDir(uint8_t portNum, uint32_t bitValue, uint8_t dir)
    
    GPIO_SetDir(PORT_3, LED_PIN, OUTPUT ); //Set pin as output


    // Red LED
    PINSEL_CFG_Type ledR_PinCfg;
    ledR_PinCfg.Portnum = PINSEL_PORT_0;
    ledR_PinCfg.Pinnum = PINSEL_PIN_9; 
    ledR_PinCfg.Funcnum = PINSEL_FUNC_0; //Gpio function
    ledR_PinCfg.Pinmode = PINSEL_PINMODE_NORMAL;

    PINSEL_ConfigPin(&ledR_PinCfg); //Configure pin

    //void GPIO_SetDir(uint8_t portNum, uint32_t bitValue, uint8_t dir)
    
    GPIO_SetDir(PORT_0, LED_PINR, OUTPUT ); //Set pin as output
}

void config_systick (){
    SYSTICK_InternalInit(100); //Initialize systick timer with 1ms interval
    SYSTICK_Cmd(ENABLE); //Enable systick timer
    SYSTICK_IntCmd(ENABLE); //Enable systick interrupt
}

void SysTick_Handler(void) {
    // Alternar LED azul
    if (GPIO_ReadValue(PORT_3) & LED_PIN) {
        GPIO_ClearValue(PORT_3, LED_PIN); // Apagar LED azul
    } else {
        GPIO_SetValue(PORT_3, LED_PIN);   // Encender LED azul
    }

    // Incrementar contador
    counter++;
    if (counter >= 10) {
        counter = 0; // Reiniciar contador
        // Alternar LED rojo
        if (GPIO_ReadValue(PORT_0) & LED_PINR) {
            GPIO_ClearValue(PORT_0, LED_PINR); // Apagar LED rojo
        } else {
            GPIO_SetValue(PORT_0, LED_PINR);   // Encender LED rojo
        }
    }
}
