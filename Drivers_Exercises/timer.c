/*
* timer.c
* Repaso teorico
* Calculo match value
* match value = (PCLK / (prescaler * desired frequency)) - 1
* 
*
*/

#include "LPC17xx.h"
#include "lpc17xx_timer.h"

void config_timer();

void config_timer(){
    TIM_TIMERCFG_Type tcfg;
    TIM_MATCHCFG_Type mcfg;

    tcfg.PrescaleOption = TIM_PRESCALE_USVAL;
    tcfg.PrescaleValue = 100;
    TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &tcfg);

    mcfg.MatchChannel = 0;
    mcfg.IntOnMatch = ENABLE;
    mcfg.StopOnMatch = DISABLE;
    mcfg.ResetOnMatch = ENABLE;
    mcfg.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;
    mcfg.MatchValue = 1000000; // 1 segundo 
    TIM_ConfigMatch(LPC_TIM0, &mcfg);

    TIM_Cmd(LPC_TIM0, ENABLE);
    NVIC_EnableIRQ(TIMER0_IRQn);
    
    
}