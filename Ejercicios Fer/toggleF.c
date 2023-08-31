/*
 * Copyright 2022 NXP
 * NXP confidential.
 * This software is owned or controlled by NXP and may only be used strictly
 * in accordance with the applicable license terms.  By expressly accepting
 * such terms or by downloading, installing, activating and/or otherwise using
 * the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to
 * be bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software.
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

void configGPIO();
void delay(uint32_t tiempo);
void secuenciaA();
void secuenciaB();

int main(void) {


    void configGPIO();
    void secuenciaA();

    while (1)
    {
        /* code */
    }


    return 0;
}


void configGPIO(){

    /*Elijo puerto 0 y 1*/
    LPC_PINCON-> PINSEL0 &= ~(0xffffffff);
    LPC_PINCON-> PINSEL1 &= ~(0xffffffff);

    LPC_PINCON-> PINMODE0 &= ~(0xffffffff);

    /*Puerto 0 como salida y puerto 1 como entrada*/
    LPC_GPIO0-> FIODIR0 |= (0x3);
    LPC_GPIO1-> FIODIR1 &= (0x0);

}

void secuenciaA(){
    while (LPC_GPIO1-> FIOPIN1 == 0x00)
    {

        LPC_GPIO0->FIOSET |= (0x1);
        delay(1000);
        LPC_GPIO0->FIOSET &= (0x0);
        delay(1000);

    }
    secuenciaB();
}

void secuenciaB(){
    while (LPC_GPIO1-> FIOPIN1 == 0x01)
    {

        LPC_GPIO0->FIOSET |= (0x1);
        delay(1000);
        delay(1000);
        LPC_GPIO0->FIOSET &= (0x0);
        delay(1000);

        LPC_GPIO0->FIOSET |= (0x1);
        delay(1000);

        LPC_GPIO0->FIOSET &= (0x0);
        delay(1000);
        delay(1000);

    }
    secuenciaA();
}

void delay(uint32_t tiempo){
    for (uint32_t i = 0; i < tiempo; i++)
        for(uint32_t j=0; j<tiempo; j++);

}



