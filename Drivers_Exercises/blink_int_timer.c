/*
* brief: Blink a LED using a timer
* author: 
* 
*/

#include "LPC17xx.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_timer.h"

#define LED_PIN   ((uint32_t)(1 << 26)) /* P3.26 connected to LED */
#define LED_PINR  ((uint32_t)(1 << 9)) /* P0.9 connected to LED */
#define LED_PING  ((uint32_t)(1 << 25)) /* P3.25 connected to LED */
#define BUTTON_PIN ((uint32_t)(1 << 0)) /* P0.0 connected to button */

#define OUTPUT 1
#define INPUT 0

#define PORT_0  0
#define PORT_3  3

void config_gpio();
void config_timer();

int main(){
    SystemInit();
    config_gpio();
    config_timer();
    
    while (1)
    {
        // interrupt service routine
    }
    
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
    GPIO_SetValue(PORT_3, LED_PIN);       // Turn on blue LED
}

void config_timer(){
    TIM_TIMERCFG_Type tcfg;
    TIM_MATCHCFG_Type mcfg;

    // Timer configuration
    tcfg.PrescaleOption = TIM_PRESCALE_USVAL; // Prescale in microseconds
    tcfg.PrescaleValue = 1000; //1ms
    TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &tcfg);

    // Match configuration
    mcfg.MatchChannel = 0;
    mcfg.IntOnMatch = ENABLE;
    mcfg.ResetOnMatch = ENABLE;
    mcfg.StopOnMatch = DISABLE;
    mcfg.MatchValue = 1000; // 1s    
    TIM_ConfigMatch(LPC_TIM0, &mcfg);

    // Enable interrupt
    NVIC_EnableIRQ(TIMER0_IRQn);

    // Enable timer
    TIM_Cmd(LPC_TIM0, ENABLE);
 
}

void TIMER0_IRQHandler(){
    if (TIM_GetIntStatus(LPC_TIM0, TIM_MR0_INT)){
        TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
        if (GPIO_ReadValue(PORT_3) & LED_PIN) {
            GPIO_ClearValue(PORT_3, LED_PIN); // turn off blue LED
        } else {
            GPIO_SetValue(PORT_3, LED_PIN);   // turn on blue LED
        }
    }
}

