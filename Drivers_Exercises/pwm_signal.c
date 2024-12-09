/*
* brief: Generate a PWM signal and capture in other pin. Calculate the duty cycle of the signal and then use it to control the intensity of a led.
* Signal is generated
* author:
*
*/

#include "LPC17xx.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_timer.h"

#define OUTPUT 1
#define INPUT 0

#define CAPTURE_PIN ((uint32_t)(1 << 23)) /* P0.23 connected to capture pin */
#define PWM_PIN ((uint32_t)(1 << 0)) /* P2.0 connected to PWM pin */
#define SIGNAL_PIN ((uint32_t)(1 << 0)) /* P0.0 connected to signal pin */
#define TEST_PIN ((uint32_t)(1 << 22)) /* P0.22 connected to test pin */
#define BUTTON_PIN ((uint32_t)(1 << 21)) /* P0.21 connected to button */

#define PORT_0  0
#define PORT_1  1
#define PORT_2  2
#define PORT_3  3

volatile uint32_t current_match_value = 1000;

void config_gpio();
void config_pwm();
void config_capture();
void config_timer();
void config_eint3();

void TIMER0_IRQHandler();
void EINT0_IRQHandler();





int main(){

    SystemInit();
    config_gpio();
    config_timer();
    config_pwm();
    config_capture();
    config_eint3();


    while (1)
    {
        // interrupt service routine
    }

}

void config_gpio(){
 // Signal generate on 0.22
    PINSEL_CFG_Type signal_PinCfg;
    signal_PinCfg.Portnum = PINSEL_PORT_0;
    signal_PinCfg.Pinnum = PINSEL_PIN_22;
    signal_PinCfg.Funcnum = PINSEL_FUNC_0;
    signal_PinCfg.Pinmode = PINSEL_PINMODE_NORMAL;

    PINSEL_ConfigPin(&signal_PinCfg); //Configure pin
    GPIO_SetDir(PORT_0, TEST_PIN, OUTPUT); //Set pin as output
}

void config_timer(){
    //Configuracion del timer
    // Timer configuration Signal Generator

    TIM_TIMERCFG_Type tcfg;
    TIM_MATCHCFG_Type mcfg;

    // Timer configuration
    tcfg.PrescaleOption = TIM_PRESCALE_USVAL; // Prescale in microseconds
    tcfg.PrescaleValue = 1000; //
    TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &tcfg);

    // Match configuration
    mcfg.MatchChannel = 0;
    mcfg.IntOnMatch = ENABLE;
    mcfg.ResetOnMatch = ENABLE;
    mcfg.StopOnMatch = DISABLE;
    mcfg.MatchValue = current_match_value;
    TIM_ConfigMatch(LPC_TIM0, &mcfg);

    // Enable interrupt
    NVIC_EnableIRQ(TIMER0_IRQn);

    // Enable timer
    TIM_Cmd(LPC_TIM0, ENABLE);
}

void TIMER0_IRQHandler(){
  if (TIM_GetIntStatus(LPC_TIM0, TIM_MR0_INT)) {
        TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
        // Alternar estado del pin
        if (GPIO_ReadValue(PORT_0) & TEST_PIN) {
            GPIO_ClearValue(PORT_0, TEST_PIN); // Apagar pin
        } else {
            GPIO_SetValue(PORT_0, TEST_PIN);   // Encender pin
        }
    }
}

void config_eint3(){

    // config external interrupt (gpio INTERRUPT)
    PINSEL_CFG_Type eint3_PinCfg;
    eint3_PinCfg.Portnum = PINSEL_PORT_0;
    eint3_PinCfg.Pinnum = PINSEL_PIN_21;
    eint3_PinCfg.Funcnum = PINSEL_FUNC_0;
    eint3_PinCfg.Pinmode = PINSEL_PINMODE_PULLDOWN;

   PINSEL_ConfigPin(&eint3_PinCfg); //Configure pin
    GPIO_SetDir(PORT_0, BUTTON_PIN, INPUT); //Set pin as input

    LPC_GPIOINT->IO0IntEnR |= BUTTON_PIN; //Enable rising edge interrupt
    NVIC_EnableIRQ(EINT3_IRQn); //Enable EINT3 interrupt
}

void EINT3_IRQHandler(){
   // when button is pressed , change the frequency of the signal
    if(LPC_GPIOINT->IO0IntStatR & BUTTON_PIN){
        LPC_GPIOINT->IO0IntClr |= BUTTON_PIN; // Clear interrupt

        if(current_match_value == 1000){
            current_match_value = 500;
        } else if(current_match_value == 500){
            current_match_value = 200;
        } else {
            current_match_value = 1000;
        }
        // Update match value
        TIM_UpdateMatchValue(LPC_TIM0, 0, current_match_value);

        //Reset timer
        TIM_ResetCounter(LPC_TIM0);
        TIM_Cmd(LPC_TIM0, ENABLE);
        }
    }

void config_pwm(){
//

}

void config_capture(){
//

}