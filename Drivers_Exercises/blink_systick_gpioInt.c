/*
* brief: Blink a LED with systick timer with gpio interrupt
* author:
*
*/

#include "LPC17xx.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"

#include "lpc17xx_systick.h"

#define LED_PIN   ((uint32_t)(1 << 26)) /* P3.26 connected to LED */
#define LED_PINR  ((uint32_t)(1 << 9)) /* P0.9 connected to LED */
#define LED_PING  ((uint32_t)(1 << 25)) /* P3.25 connected to LED */
#define BUTTON_PIN ((uint32_t)(1 << 0)) /* P0.0 connected to button */

#define OUTPUT 1
#define INPUT 0

#define PORT_0  0
#define PORT_3  3


volatile uint32_t counter = 0;
volatile uint8_t flag = 0;


void config_gpio();
void config_systick();
void SysTick_Handler(void);
void config_eint3();
void EINT3_IRQHandler();
void delay_ms(uint32_t ms);
void handle_flag();

int main(void){
    config_gpio();
    config_systick();
    config_eint3();

 while (1) {
    handle_flag(); // Manejar bandera de interrupción
    }

    return 0;
}

void config_gpio(){

 //void GPIO_SetDir(uint8_t portNum, uint32_t bitValue, uint8_t dir)

    // Blue LED
    PINSEL_CFG_Type led_PinCfg;
    led_PinCfg.Portnum = PINSEL_PORT_3;
    led_PinCfg.Pinnum = PINSEL_PIN_26;
    led_PinCfg.Funcnum = PINSEL_FUNC_0; //Gpio function
    led_PinCfg.Pinmode = PINSEL_PINMODE_NORMAL;

    PINSEL_ConfigPin(&led_PinCfg); //Configure pin

    GPIO_SetDir(PORT_3, LED_PIN, OUTPUT ); //Set pin as output
    GPIO_SetValue(PORT_3, LED_PIN);       // Encender LED azul inicialmente


    // Red LED
    PINSEL_CFG_Type ledR_PinCfg;
    ledR_PinCfg.Portnum = PINSEL_PORT_0;
    ledR_PinCfg.Pinnum = PINSEL_PIN_9;
    ledR_PinCfg.Funcnum = PINSEL_FUNC_0; //Gpio function
    ledR_PinCfg.Pinmode = PINSEL_PINMODE_NORMAL;

    PINSEL_ConfigPin(&ledR_PinCfg); //Configure pin

    GPIO_SetDir(PORT_0, LED_PINR, OUTPUT); //Set pin as output}
    GPIO_SetValue(PORT_0, LED_PINR);       // Encender LED rojo inicialmente

    // Green LED
    PINSEL_CFG_Type ledG_PinCfg;
    ledG_PinCfg.Portnum = PINSEL_PORT_3;
    ledG_PinCfg.Pinnum = PINSEL_PIN_25;
    ledG_PinCfg.Funcnum = PINSEL_FUNC_0; //Gpio function
    ledG_PinCfg.Pinmode = PINSEL_PINMODE_NORMAL;

    PINSEL_ConfigPin(&ledG_PinCfg); //Configure pin

    GPIO_SetDir(PORT_3, LED_PING, OUTPUT); //Set pin as output}
   // GPIO_ClearValue(PORT_3, LED_PING); // Apagar LED verde
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

void config_eint3(){

    //P0.0 como entrada boton e interrupcion por GPIO

    PINSEL_CFG_Type eint3_PinCfg;
    eint3_PinCfg.Portnum = PINSEL_PORT_0;
    eint3_PinCfg.Pinnum = PINSEL_PIN_0;
    eint3_PinCfg.Funcnum = PINSEL_FUNC_0;
    eint3_PinCfg.Pinmode = PINSEL_PINMODE_PULLDOWN;

    PINSEL_ConfigPin(&eint3_PinCfg); //Configure pin
    GPIO_SetDir(PORT_0, BUTTON_PIN, INPUT); //Set pin as input

    LPC_GPIOINT->IO0IntEnR |= BUTTON_PIN; //Enable rising edge interrupt
    NVIC_EnableIRQ(EINT3_IRQn); //Enable EINT3 interrupt
}

void EINT3_IRQHandler(){
 if (LPC_GPIOINT->IO0IntStatR & BUTTON_PIN) {
        flag = 1; // Activar bandera de interrupción
        LPC_GPIOINT->IO0IntClr = BUTTON_PIN; // Limpiar bandera de interrupción
    }
}

void handle_flag() {
    if(flag){
        flag = 0; // Desactivar bandera de interrupción
        
        SYSTICK_Cmd(DISABLE); // Deshabilitar systick timer

        GPIO_ClearValue(PORT_0, LED_PINR); // Apagar LED rojo
        GPIO_ClearValue(PORT_3, LED_PIN); // Apagar LED azul
        GPIO_SetValue(PORT_3, LED_PING); // Encender LED verde

        delay_ms(10000); // Retardo

        GPIO_ClearValue(PORT_3, LED_PING); // Apagar LED verde
        GPIO_SetValue(PORT_3, LED_PIN); // Encender LED azul
        GPIO_SetValue(PORT_0, LED_PINR); // Encender LED rojo
        
        SYSTICK_Cmd(ENABLE); // Volver a habilitar SysTick

    }
}

void delay_ms(uint32_t ms) {
    for (uint32_t i = 0; i < ms * 1000; i++) {
        __NOP(); // No Operation (espera activa)
    }
}

