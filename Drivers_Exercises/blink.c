/*
* brief: Blink a LED when a button is pressed
* author:
* 
*/

#include "LPC17xx.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"

#define LED_PIN   ((uint32_t)(1 << 26)) /* P3.26 connected to LED */
#define OUTPUT_PIN ((uint8_t)(1 << 1)) /* P0.1 connected to output */
#define PORT_3  3

#define BUTTON_PIN ((uint32_t)(1 << 0)) /* P0.0 connected to button */
#define INPUT_PIN ((uint8_t)(0 << 0)) /* P0.0 connected to input */
#define PORT_0  0

#define LED_PIN_R   ((uint32_t)(1 << 22)) /* P0.22 connected to LED */
#define OUTPUT_PIN_R ((uint8_t)(1 << 1)) /* P0.1 connected to output */
#define PORT_0_R  0 

void config_gpio();


int main(void){
    SystemInit();
    config_gpio();
    GPIO_SetValue(PORT_3, LED_PIN);

    while(1){
        if(GPIO_ReadValue(PORT_0) & BUTTON_PIN){
            GPIO_SetValue(PORT_0, LED_PIN_R);
            GPIO_ClearValue(PORT_3, LED_PIN);
        }else{
            GPIO_ClearValue(PORT_0, LED_PIN_R);
            GPIO_SetValue(PORT_3, LED_PIN);
        }
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
    GPIO_SetDir(PORT_3, LED_PIN, OUTPUT_PIN); //Set pin as output

     PINSEL_CFG_Type button_PinCfg;
    button_PinCfg.Portnum = PINSEL_PORT_0;
    button_PinCfg.Pinnum = PINSEL_PIN_0; 
    button_PinCfg.Funcnum = PINSEL_FUNC_0; //Gpio function
    button_PinCfg.Pinmode = PINSEL_PINMODE_PULLDOWN;

    PINSEL_ConfigPin(&button_PinCfg); //Configure pin
    GPIO_SetDir(PORT_0, BUTTON_PIN, INPUT_PIN); //Set pin as input

    PINSEL_CFG_Type ledr_PinCfg;
    ledr_PinCfg.Portnum = PINSEL_PORT_0;
    ledr_PinCfg.Pinnum = PINSEL_PIN_22; 
    ledr_PinCfg.Funcnum = PINSEL_FUNC_0; //Gpio function
    ledr_PinCfg.Pinmode = PINSEL_PINMODE_NORMAL;

    PINSEL_ConfigPin(&ledr_PinCfg); //Configure pin
    GPIO_SetDir(PORT_0, LED_PIN_R, OUTPUT_PIN); //Set pin as output
}
