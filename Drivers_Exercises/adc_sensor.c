/*
* brief: Implement a sistem that reads a temperature sensor conected to the channel 0 of the ADC, configurated to generate a periodic  conversion
* with timer. The sistem have to interrupt when the conversion of the adc is finished. If the temperature si higher than an umbral, the sistem have to turn on a red led.
* If the temperature is lower than an umbral, the sistem have to turn on a green led.
* author: 
* 
*/

#include "LPC17xx.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_adc.h"

#define LED_PINR  ((uint32_t)(1 << 9)) /* P0.9 connected to LED */
#define LED_PING  ((uint32_t)(1 << 25)) /* P3.25 connected to LED */

#define OUTPUT 1
#define INPUT 0

#define PORT_0  0
#define PORT_3  3

#define Umbra 25

volatile adc_value = 0;


void config_gpio();
void config_timer();
void config_adc();
void TIMER0_IRQHandler(void);
void ADC_IRQHandler(void);

int main(){
    SystemInit();
    config_gpio();
    config_timer();
    config_adc();
    config_adc_interrupt();
    
    while (1)
    {
        // interrupt service routine
    }
    
}

void config_gpio(){

 //void GPIO_SetDir(uint8_t portNum, uint32_t bitValue, uint8_t dir)

    // Green LED
    PINSEL_CFG_Type ledG_PinCfg;
    ledG_PinCfg.Portnum = PINSEL_PORT_3;
    ledG_PinCfg.Pinnum = PINSEL_PIN_25;
    ledG_PinCfg.Funcnum = PINSEL_FUNC_0; //Gpio function
    ledG_PinCfg.Pinmode = PINSEL_PINMODE_NORMAL;

    PINSEL_ConfigPin(&ledG_PinCfg); //Configure pin

    GPIO_SetDir(PORT_3, LED_PING, OUTPUT ); //Set pin as output

    // Red LED
    PINSEL_CFG_Type ledR_PinCfg;
    ledR_PinCfg.Portnum = PINSEL_PORT_3;
    ledR_PinCfg.Pinnum = PINSEL_PIN_26;
    ledR_PinCfg.Funcnum = PINSEL_FUNC_0; //Gpio function
    ledR_PinCfg.Pinmode = PINSEL_PINMODE_NORMAL;

    PINSEL_ConfigPin(&ledR_PinCfg); //Configure pin

    GPIO_SetDir(PORT_0, LED_PINR, OUTPUT ); //Set pin as output
}

void config_timer(){
    // Timer configuration
    TIM_TIMERCFG_Type timer_config;
    TIM_MATCHCFG_Type timer_match_config;
    
    timer_config.PrescaleOption = TIM_PRESCALE_USVAL;
    timer_config.PrescaleValue = 1000; // 1ms

    TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &timer_config);

    // Timer match configuration
 
    timer_match_config.MatchChannel = 0;
    timer_match_config.IntOnMatch = ENABLE;
    timer_match_config.ResetOnMatch = ENABLE;
    timer_match_config.StopOnMatch = DISABLE;
    timer_match_config.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;
    timer_match_config.MatchValue = 1000; // 1s match and interrupt
    TIM_ConfigMatch(LPC_TIM0, &timer_match_config);

    // Enable timer and timer interrupt
    TIM_Cmd(LPC_TIM0, ENABLE);
    NVIC_EnableIRQ(TIMER0_IRQn);
}

void config_adc(){
    //Configure ADC pin AD0.0
    PINSEL_CFG_Type adc_pin;
    adc_pin.Portnum = PINSEL_PORT_0;
    adc_pin.Pinnum = PINSEL_PIN_23;
    adc_pin.Funcnum = PINSEL_FUNC_1; //ADC function
    adc_pin.Pinmode = PINSEL_PINMODE_TRISTATE;

    PINSEL_ConfigPin(&adc_pin);

    // ADC configuration
    ADC_Init(LPC_ADC, 200000); // 200KHz
    ADC_ChannelCmd(LPC_ADC, 0, ENABLE);
    ADC_BurstCmd(LPC_ADC, DISABLE);

    ADC_IntConfig(LPC_ADC, ADC_ADINTEN0, ENABLE);

    NVIC_EnableIRQ(ADC_IRQn);
}

void TIMER0_IRQHandler(void){
    if(TIM_GetIntStatus(LPC_TIM0, TIM_MR0_INT)){
        ADC_StartCmd(LPC_ADC, ADC_START_NOW);
    }

    TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);

}

void ADC_IRQHandler(void){
  adc_value = ADC_ChannelGetData(LPC_ADC, 0);

  float temp = (adc_value * 3.3 / 4096)*100;

  if(temp > Umbra){
    GPIO_SetValue(PORT_0, LED_PINR);
    GPIO_ClearValue(PORT_3, LED_PING);
    }else{
    GPIO_ClearValue(PORT_0, LED_PINR);
    GPIO_SetValue(PORT_3, LED_PING);
    } 
}

